#ifndef DOUBLE_DICE_H
#define DOUBLE_DICE_H

#include "Dice.h"
#include "PenaltyDice.h"
#include "BonusDice.h"

class DoubleDiceMI : public PenaltyDice, public BonusDice {
public:
    DoubleDiceMI(Dice& dice) : PenaltyDice(dice), BonusDice(dice) {}

    unsigned roll() {
        usePenaltyNext = !usePenaltyNext;
        return usePenaltyNext ? PenaltyDice::roll() : BonusDice::roll();
    }

    bool usePenaltyNext = true;
};

class DoubleDice {
public:
    DoubleDice(Dice& dice) : penaltyDice(dice), bonusDice(dice) {}

    unsigned roll() {
        usePenaltyNext = !usePenaltyNext;
        return usePenaltyNext ? penaltyDice.roll() : bonusDice.roll();
    }

    PenaltyDice penaltyDice;
    BonusDice bonusDice;
    bool usePenaltyNext = true;
};

#endif
