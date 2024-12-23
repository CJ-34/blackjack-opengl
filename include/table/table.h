#pragma once

#include "deck.h"
#include "player.h"
#include "dealer.h"

#include <string>

struct GameResult {
    std::string result;
    bool playerWin;
};

class Table {
public:
    Table(const Player &player);

    void startGame();
    void playerTurn();
    void dealerTurn();
    void resetTable();  
    GameResult determineWinner();

    Player &getPlayer();
    Dealer &getDealer();


private:
    Deck deck;
    Dealer dealer;
    Player player;
};


