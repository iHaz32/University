#pragma once

#include <string>

class Player {
    protected:
        std::string name;
        std::string surname;
    public:
        Player(){ };
        Player(std::string name, std::string surname);
        std::string getName();
        std::string getSurname();
};