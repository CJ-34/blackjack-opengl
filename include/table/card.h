#pragma once

#include <string>

enum class Suit {
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES,
};

enum class Rank {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };

class Card {
public:
    Card(Suit suit = Suit::HEARTS, Rank rank = Rank::ACE) 
    : suit(suit), rank(rank) {}

    Suit getSuit() const;

    Rank getRank() const;

    int getValue() const;

    std::string getPhotoName() const;

    std::string getImagePath() const;

private:
    Suit suit;
    Rank rank;

    std::string suitToChar() const;

    std::string rankToChar() const;
    
};

