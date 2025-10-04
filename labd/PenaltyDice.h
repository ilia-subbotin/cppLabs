#ifndef PENALTY_DICE_H
#define PENALTY_DICE_H

#include "Dice.h"
#include <algorithm>

class PenaltyDice {
public:
    PenaltyDice(Dice& dice) : baseDice(dice) {}

    unsigned roll() {
        unsigned roll1 = baseDice.roll();
        unsigned roll2 = baseDice.roll();
        return std::min(roll1, roll2);
    }

    Dice& baseDice;
};

#endif
