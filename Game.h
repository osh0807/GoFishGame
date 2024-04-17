//Game.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for Game class
#pragma once
#include <string>
#include <vector>
class Game {
    protected:
        std::vector<std::string> players;
        const int SUCCESS = 0;
        //including this integer for the return value of play()
    public:
        const int FIRST_PLAYER = 2;
        // represent index of the name of the first player among arguments
        //public so derived classes can access.
        Game(int argc, const char *argv[]);
        virtual int play() = 0;
        bool endGame();
};