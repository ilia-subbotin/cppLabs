#ifndef THREE_DICE_POOL_H
#define THREE_DICE_POOL_H

#include <random>

class ThreeDicePool {
public:
    ThreeDicePool(unsigned max,
        unsigned seed_1, unsigned seed_2, unsigned seed_3) :
        max(max),
        dstr_1(1, max), dstr_2(1, max), dstr_3(1, max),
        reng_1(seed_1), reng_2(seed_2), reng_3(seed_3) {
    }

    unsigned roll() {
        return dstr_1(reng_1) + dstr_2(reng_2) + dstr_3(reng_3);
    }

    unsigned max;
    std::uniform_int_distribution<unsigned> dstr_1, dstr_2, dstr_3;
    std::default_random_engine reng_1, reng_2, reng_3;
};

#endif
