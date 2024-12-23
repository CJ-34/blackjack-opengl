#include "table/card.h"

Suit Card::getSuit() const
{
    return Suit();
}

Rank Card::getRank() const {
    return rank;
} 

int Card::getValue() const {
    if (rank == Rank::JACK || rank == Rank::QUEEN || rank == Rank::KING) {
        return 10;
    } else if (rank == Rank::ACE) {
        return 11;
    }       

    return static_cast<int>(rank);
}

std::string Card::getPhotoName() const {
    return rankToChar() + "-" + suitToChar();
}

std::string Card::getImagePath() const
{
    std::string imagePath = "resources/cards/" + getPhotoName() + ".png";
    return imagePath.c_str();
}

std::string Card::suitToChar() const {
    switch (suit) {
        case Suit::HEARTS: return "H";
        case Suit::DIAMONDS: return "D";
        case Suit::CLUBS: return "C";
        case Suit::SPADES: return "S";
    }
}

std::string Card::rankToChar() const {
    switch(rank) {
        case Rank::TWO: return "2";
        case Rank::THREE: return "3";
        case Rank::FOUR: return "4";
        case Rank::FIVE: return "5";
        case Rank::SIX: return "6";
        case Rank::SEVEN: return "7";
        case Rank::EIGHT: return "8";
        case Rank::NINE: return "9";
        case Rank::TEN: return "10";
        case Rank::JACK: return "J";
        case Rank::QUEEN: return "Q";
        case Rank::KING: return "K";
        case Rank::ACE: return "A";
    }
}



