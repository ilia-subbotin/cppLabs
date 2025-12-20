#include <iostream>
#include <utility>

template<typename T>
class ScopePtr {
private:
    T* m_ptr;
public:
    ScopePtr() : m_ptr{nullptr} {}
    explicit ScopePtr(T* ptr) : m_ptr{ptr} {}
    ScopePtr(const ScopePtr&) = delete;
    ScopePtr& operator=(const ScopePtr&) = delete;
    ScopePtr(ScopePtr&& other) noexcept : m_ptr{std::exchange(other.m_ptr, nullptr)} {}
    ScopePtr& operator=(ScopePtr&& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    explicit operator bool() const { return m_ptr != nullptr; }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }
    void reset(T* new_ptr) {
        delete m_ptr;
        m_ptr = new_ptr;
    }
    ~ScopePtr() { delete m_ptr; }
};

template<typename T>
class ScopePtr<T[]> {
private:
    T* m_ptr;
public:
    ScopePtr() : m_ptr{nullptr} {}
    explicit ScopePtr(T* ptr) : m_ptr{ptr} {}
    ScopePtr(const ScopePtr&) = delete;
    ScopePtr& operator=(const ScopePtr&) = delete;
    ScopePtr(ScopePtr&& other) noexcept : m_ptr{std::exchange(other.m_ptr, nullptr)} {}
    ScopePtr& operator=(ScopePtr&& other) noexcept {
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    T& operator[](size_t index) const { return m_ptr[index]; }
    T* get() const { return m_ptr; }
    void reset(T* new_ptr) {
        delete[] m_ptr;
        m_ptr = new_ptr;
    }
    ~ScopePtr() { delete[] m_ptr; }
};

int main() {
    ScopePtr<int[]> arr(new int[3]{10, 20, 30});
    std::cout << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;
    return 0;
}