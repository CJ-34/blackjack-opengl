#include "table/hand.h"

Hand::Hand() {
    cards.reserve(10);
}

void Hand::addCard(const Card &card) {
    cards.emplace_back(card);
}

void Hand::clear() {
    cards.clear();
}

int Hand::getHandValue() const {
    int totalValue = 0;
    int aceCount = 0;
    for (const auto &card : cards) {
        totalValue += card.getValue();
        if (card.getRank() == Rank::ACE) {
            aceCount++;
        }
    }

    while (aceCount > 0 && totalValue > 21) {
        totalValue -= 10;
        aceCount--;
    }

    return totalValue;
}

bool Hand::isBlackjack() const {
   return cards.size() == 2 && getHandValue() == 21; 
}

bool Hand::isBusted() const {
    return getHandValue() > 21;
}                       

std::vector<Card> Hand::getCards() const {
    return cards;
}