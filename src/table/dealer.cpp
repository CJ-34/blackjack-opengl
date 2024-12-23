#include "table/dealer.h"

Dealer::Dealer() : Player("Dealer") {}

Dealer::~Dealer()
{
    hand.clear();
}

bool Dealer::shouldHit() const {
    return hand.getHandValue() < 17;
}
