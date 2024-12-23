#include "table/deck.h"

Deck::Deck() {
    cards.reserve(52);
    reset();
}

void Deck::shuffle() {
    static std::mt19937 rng { std::random_device{}()};
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::deal() {
    if(cards.empty()) {
        reset();
    }
    Card dealtCard = std::move(cards.back());
    cards.pop_back();
    return dealtCard;
}

void Deck::reset() {
    cards.clear();
    cards.reserve(52);
    for (int suit = (int) Suit::HEARTS; suit <= (int) Suit::SPADES; suit++) {
        for (int rank = (int) Rank::ACE; rank <= (int) Rank::KING; rank++) {
            cards.emplace_back((Suit) suit, (Rank) rank);
        }
    }
   
}