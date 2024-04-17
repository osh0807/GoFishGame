//Game.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the constructor and member functions of Game class
#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(int argc, const char *argv[]){
    for (int i = FIRST_PLAYER; i < argc; i++ ){
        players.push_back(argv[i]);
    }
}

bool Game::endGame(){
    cout << "Do you want to end the game? (yes/no) " << endl;
    string ans;
    cin >> ans;
    return (ans == "yes");
}