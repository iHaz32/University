#pragma once
#include "Player.h"
#include <string>

class BasketballPlayer : public Player {
    private:
        std::string position;
    public:
        BasketballPlayer(std::string firstName, std::string lastName, std::string position);
        std::string getPosition();
        std::string getPlayerDescription();
};