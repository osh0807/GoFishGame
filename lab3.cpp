//lab3.cpp
//soohoon oh; soohoonoh@wustl.edu
//include main()functions that operate program and return int value representing result
//also include non-zero integer values representing error cases and useful numbers for game construction
//and a helper function create() that returns a pointer to whichever game called by command
#include "HoldemGame.h"
#include "PinochleGame.h"
#include "GoFishGame.h"
#include <memory>
#include <cstring>

using namespace std;

const int GAME_NAME_INDEX = 1;
const int DECK_NAME = 2;

const int NUM_ARG = 2;
const int GOFISH_NUM_ARG = 3;

const int WRONG_NUM_ARG = 1;
const int WRONG_GAME_NAME = 2;
const int WRONG_NUM_PLAYER = 3;
const int WRONG_GAME_CREATE = 4;

const int PINOCHLE_NUM_PLAYER = 4;
const int HOLDEM_NUM_PLAYER_MIN = 2;
const int HOLDEM_NUM_PLAYER_MAX = 9;
const int GOFISH_NUM_PLAYER_MIN = 2;
const int GOFISH_NUM_PLAYER_MAX = 5;

shared_ptr<Game> create(int argc, const char *argv[]){
    shared_ptr<Game> game;
    string gameType = "";
    gameType = argv[GAME_NAME_INDEX];
    if(gameType == "Pinochle"){
       game = make_shared<PinochleGame>(argc, argv);
    }else if (gameType == "HoldEm"){
       game = make_shared<HoldemGame>(argc, argv);
    }
    else if (gameType == "GoFish"){
        try{
            ///constructed a new argv for gofish game because it includes another element of the deck name
            const char ** new_argv = new const char *[argc];
            for (int i =0; i < argc -1; i++){
                if(i < NUM_ARG){
                    new_argv[i] = argv[i];
                }
                else if (i >= NUM_ARG){
                    new_argv[i] = argv[i+1];
                }
            }
            new_argv[argc-1] = NULL;

            if (strcmp(argv[DECK_NAME], "HoldEm") == 0){
                game = make_shared<GoFishGame<Suit, HoldemRank, HoldemDeck> >(argc, new_argv);
            }else if (strcmp(argv[DECK_NAME], "Pinochle")== 0){
                game = make_shared<GoFishGame<Suit, PinochleRank, PinochleDeck> >(argc, new_argv);
            }else if (strcmp(argv[DECK_NAME], "Uno")== 0){
                game = make_shared<GoFishGame<Color, UnoRank, UnoDeck> >(argc, new_argv);
            }else {
                throw std::invalid_argument("Name valid deck for gofishgame (HoldEm, Pinochle, or Uno)");
            }

        }
        catch (std::exception &e){
            throw e;
        }

    }
    return game;
}


int main(int argc, const char * argv[]){
    string gameType = "";
    if (argc < NUM_ARG){
        cout << "wrong usage" << endl;
        cout << "Usage: ./lab1 Pinochle/HoldEm/GoFish [DeckType] player1 player2 ..." << endl;
        return WRONG_NUM_ARG;
    }
    gameType = argv[GAME_NAME_INDEX];

    if (argc == NUM_ARG){
        cout << "wrong usage" << endl;
        cout << "Usage: ./lab1 Pinochle/HoldEm/GoFish [DeckType] player1 player2 ..." << endl;
        return WRONG_NUM_ARG;
    }
    if(gameType != "Pinochle" && gameType != "HoldEm" && gameType != "GoFish"){
        cout << "wrong game name" << endl;
        cout << "Usage: ./lab1 Pinochle/HoldEm/GoFish [DeckType] player1 player2 ..." << endl;
        return WRONG_GAME_NAME;
    }   
    if(((gameType == "Pinochle" ) && (argc == NUM_ARG + PINOCHLE_NUM_PLAYER ) )|| 
    ((gameType == "HoldEm") && (argc >= NUM_ARG + HOLDEM_NUM_PLAYER_MIN && 
    argc <= NUM_ARG + HOLDEM_NUM_PLAYER_MAX )) ||
    ((gameType == "GoFish") && (argc >= GOFISH_NUM_ARG + GOFISH_NUM_PLAYER_MIN && 
    argc <= GOFISH_NUM_ARG + GOFISH_NUM_PLAYER_MAX ))){
        try{
            shared_ptr<Game> newGame = create(argc, argv);
            return newGame -> play();
        }
        catch (std::exception &e){
            cerr << e.what() << endl;
            return WRONG_GAME_CREATE;
        }
        
    }
    cout << "Wrong number of players!" << endl;
    cout << "Usage: ./lab1 Pinochle/HoldEm/GoFish [DeckType] player1 player2 ..." << endl;
    cout << "for Pinochle, there must be 4 players" << endl;
    cout << "for HoldEm, there must be 2-9 players" << endl;
    cout << "for GoFish, there must be 2-5 players" << endl;
    return WRONG_NUM_PLAYER;

}
