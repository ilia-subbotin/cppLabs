#ifndef DICE_H
#define DICE_H

#include <random>

class Dice {
public:
    Dice(unsigned max, unsigned seed) :
        max(max), dstr(1, max), reng(seed) {
    }

    unsigned roll() {
        return dstr(reng);
    }

    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

#endif
