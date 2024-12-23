#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

#include "card.h"
#include "graphics/resourceManager.h"

class Deck {
public:
    Deck();

    void shuffle();

    Card deal();

    void reset();

    std::vector<Card>& getCards(){
        return cards;
    }

private:
    std::vector<Card> cards;
    bool startDeck;
};