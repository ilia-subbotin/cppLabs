#include <iostream>
#include <string>
#include <utility>

struct ControlBlock {
    size_t shared_count;
    size_t weak_count;

    ControlBlock() : shared_count(1), weak_count(0) {}
};

template <typename T>
class SharedPtr {
public:
    SharedPtr() : ptr_(nullptr), cb_(nullptr) {}

    explicit SharedPtr(T* ptr) : ptr_(ptr) {
        if (ptr_) {
            cb_ = new ControlBlock();
        } else {
            cb_ = nullptr;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), cb_(other.cb_) {
        if (cb_) {
            cb_->shared_count++;
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), cb_(other.cb_) {
        other.ptr_ = nullptr;
        other.cb_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_ = other.cb_;
            if (cb_) {
                cb_->shared_count++;
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            cb_ = other.cb_;
            other.ptr_ = nullptr;
            other.cb_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }
    size_t use_count() const { return cb_ ? cb_->shared_count : 0; }

    template <typename U, typename... Args>
    friend SharedPtr<U> make_shared(Args&&... args);

private:
    T* ptr_;
    ControlBlock* cb_;

    void release() {
        if (cb_) {
            if (--cb_->shared_count == 0) {
                delete ptr_;
                if (cb_->weak_count == 0) {
                    delete cb_;
                }
            }
        }
    }
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    SharedPtr<T> sp;
    sp.ptr_ = new T(std::forward<Args>(args)...);
    sp.cb_ = new ControlBlock();
    return sp;
}

int main() {
    SharedPtr<int> p1 = make_shared<int>(100);
    std::cout << "p1 count: " << p1.use_count() << " value: " << *p1 << std::endl;

    {
        SharedPtr<int> p2 = p1;
        std::cout << "p1 count: " << p1.use_count() << std::endl;
        std::cout << "p2 count: " << p2.use_count() << std::endl;
    }

    std::cout << "p1 count after p2 destroyed: " << p1.use_count() << std::endl;

    return 0;
}