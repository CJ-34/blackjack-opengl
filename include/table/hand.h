#pragma once

#include <vector>
#include "card.h"

class Hand {
public:
    Hand();

    void addCard(const Card& card);

    void clear();

    int getHandValue() const;

    bool isBlackjack() const;

    bool isBusted() const;

    std::vector<Card> getCards() const;

private:
    std::vector<Card> cards;
};
