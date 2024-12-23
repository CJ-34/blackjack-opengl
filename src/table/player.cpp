#include "table/player.h"

Player::Player(const std::string &name) : name(name) {
    Player::hand;
}

Player::~Player() {
    hand.clear();
}

void Player::addCard(const Card &card)
{
    hand.addCard(card);
}

bool Player::isBusted() const {
   return hand.isBusted(); 
}

bool Player::isBlackjack() const {
    return hand.isBlackjack();
}

Hand &Player::getHand(){
    return hand;
}



