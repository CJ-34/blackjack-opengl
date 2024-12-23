#include "table/table.h"

Table::Table(const Player &player) : player(std::move(player)), dealer(), deck() {}

void Table::startGame() {
    deck.shuffle();
    for (int i = 0; i < 2; i++) {
        player.addCard(deck.deal());
        dealer.addCard(deck.deal());
    }
}

void Table::playerTurn() {
    player.addCard(deck.deal());
}

void Table::dealerTurn() {
   while (dealer.shouldHit()) {
       dealer.addCard(deck.deal());
   }
}

GameResult Table::determineWinner() {
    std::string result;
    bool playerWin;

    if (player.isBlackjack()) {
        if (dealer.isBlackjack()) {
            result = "Oba igralec in delivec imata blackjack! Ni zmagovalca.";
            playerWin = false;  // It's a tie, no one wins
        } else {
            result = "Igralec ima blackjack! Igralec zmaga!";
            playerWin = true;
        }
    } else if (dealer.isBlackjack()) {
        result = "Delivec ima blackjack! Delivec zmaga!";
        playerWin = false;
    } else {
        int playerValue = player.getHand().getHandValue();
        int dealerValue = dealer.getHand().getHandValue();

        if (player.isBusted()) {
            result = "Igralec je presegel 21! Delivec zmaga.";
            playerWin = false;
        } else if (dealer.isBusted()) {
            result = "Delivec je presegel 21! Igralec zmaga.";
            playerWin = true;
        } else if (playerValue > dealerValue) {
            result = "Igralec zmaga!";
            playerWin = true;
        } else if (playerValue < dealerValue) {
            result = "Delivec zmaga!";
            playerWin = false;
        } else { // It's a tie in case of equal values
            result = "Izenačeno! Ni zmagovalca.";
            playerWin = false; // Tie is a draw, not a win for the player
        }
    }
    return {result, playerWin};
}

void Table::resetTable() {
    player.getHand().clear();
    dealer.getHand().clear();
    deck.reset();
}

Player &Table::getPlayer() {
    return player;
};
Dealer &Table::getDealer() {
    return dealer;
};