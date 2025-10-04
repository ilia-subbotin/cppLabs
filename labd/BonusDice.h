#ifndef BONUS_DICE_H
#define BONUS_DICE_H

#include "Dice.h"
#include <algorithm>

class BonusDice {
public:
    BonusDice(Dice& dice) : baseDice(dice) {}

    unsigned roll() {
        unsigned roll1 = baseDice.roll();
        unsigned roll2 = baseDice.roll();
        return std::max(roll1, roll2);
    }

    Dice& baseDice;
};

#endif
