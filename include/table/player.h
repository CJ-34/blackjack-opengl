#pragma once

#include <string>

#include "hand.h"

class Player {
public:
    Player(const std::string &name);

    ~Player();

    void addCard(const Card &card);

    bool isBusted() const;

    bool isBlackjack() const;

    Hand &getHand();

protected:
    std::string name;
    Hand hand;
};