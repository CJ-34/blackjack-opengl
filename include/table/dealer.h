#pragma once

#include "player.h"

class Dealer : public Player {
public:
    Dealer();

    ~Dealer();

    bool shouldHit() const;
};