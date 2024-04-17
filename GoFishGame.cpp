//GoFishGame.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the constructor and member functions of GoFishGame class
#include "GoFishGame.h"

using namespace std;

static const int REQUIRED_NUM_CARDS = 4;
static const int FOUR_KIND_NUM = 4;
static const int NUM_DECK_TYPE = 3;

///created a string array of instructions
static const string instructions[NUM_DECK_TYPE] = {
    "ranks are integers 2~10, J, O, K, A;\nand their rank ids are 0~12",
    "ranks are integers 9, J, O, K, 10, A;\nand their rank ids are 0~5",
    "ranks are integers 0~9, skip, reverse, drawtwo, drawfour, wild, blank;\nand their rank ids are 0~15"
};

///template constructor specializations for holdemdeck
template <>
GoFishGame<Suit, HoldemRank, HoldemDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc -1, argv){
    numPlayers = players.size();
    GoFishDeck = HoldemDeck();
    deckNum = 0;
    hands.resize(numPlayers);
    books.resize(numPlayers);
    numBooks.resize(numPlayers);
    for (auto currRank = HoldemRank::two; currRank < HoldemRank::undefined; ++currRank){
        int count = count_if(GoFishDeck.begin(), GoFishDeck.end(),
            [currRank](const auto & card){return card.rank == currRank;});
        if (count < REQUIRED_NUM_CARDS){
            throw std::invalid_argument("INVALID_DECK: there must be at least 4 cards per each rank");
        }
    }
}

///template constructor specializations for pinochledeck
template <>
GoFishGame<Suit, PinochleRank, PinochleDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc -1, argv){
    numPlayers = players.size();
    GoFishDeck = PinochleDeck();
    deckNum = 1;
    hands.resize(numPlayers);
    books.resize(numPlayers);
    numBooks.resize(numPlayers);
    for (auto currRank = PinochleRank::nine; currRank < PinochleRank::undefined; ++currRank){
        int count = count_if(GoFishDeck.begin(), GoFishDeck.end(),
            [currRank](const auto & card){return card.rank == currRank;});
        if (count < REQUIRED_NUM_CARDS){
            throw std::invalid_argument("INVALID_DECK: there must be at least 4 cards per each rank");
        }
    }
}

///template constructor specializations for Unodeck
template <>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc -1, argv){
    numPlayers = players.size();
    GoFishDeck = UnoDeck();
    deckNum = 2;
    hands.resize(numPlayers);
    books.resize(numPlayers);
    numBooks.resize(numPlayers);
    for (auto currRank = UnoRank::zero; currRank < UnoRank::undefined; ++currRank){
        int count = count_if(GoFishDeck.begin(), GoFishDeck.end(),
            [currRank](const auto & card){return card.rank == currRank;});
        if (count < REQUIRED_NUM_CARDS){
            throw std::invalid_argument("INVALID_DECK: there must be at least 4 cards per each rank");
        }
    }
}


template <typename S, typename R , typename D>
bool GoFishGame<S, R, D>::collect_books(int playerNum){
    auto & handCopy = hands[playerNum - 1];
    for (R rank_it = static_cast<R>(0); rank_it < R:: undefined; ++rank_it){
        int count = count_if(handCopy.begin(), handCopy.end(), [rank_it](Card<R, S> &card){return card.rank == rank_it;});
        ///checking if there is a four-of-a-kind for a rank
        if(count == FOUR_KIND_NUM){
            auto predicate = [rank_it](Card <R, S> &card){return card.rank == rank_it;};
            books[playerNum-1].collect_if(handCopy, predicate);
            numBooks[playerNum -1]++;
            return true;
        }
    }
    return false;
}

template <typename S, typename R , typename D>
bool GoFishGame<S, R, D>::turn(int playerNum){
    ///printing out hands and books
    for (int i = 0; i < numPlayers; i++){
        cout <<"player " << i + 1 <<": " << players[i] << "'s hand: " << endl;
        for (auto it = hands[i].begin(); it != hands[i].end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
        cout << "book: " << endl;
        if (numBooks[i] == 0){
            cout << "no books collected yet" << endl;
        } else {
            R currentRank = (*(books[i].begin())).rank;
            for (auto it = books[i].begin(); it != books[i].end(); ++it){
                if ((*it).rank != currentRank){
                    cout << endl;
                    currentRank = (*it).rank;
                }
            cout << (*it).rank << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
///player turn promts
    cout << endl << "Player " << playerNum << " " << players[playerNum -1] << "'s turn " << endl;
    cout << instructions[deckNum] << endl;

    bool condition = false;
    bool rankCondition = false;
    int whichPlayer;
    int whichRank;
    while (!condition){
        cout << "what is the rank number you want to ask for?" << endl;
        while (!(cin >> whichRank)){
            cout <<  "please enter again, " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "What is the player number you want to ask from?" << endl;
        while (!(cin >> whichPlayer)){
            cout <<  "please enter again, " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    ///check if the rank id and target player id is correct
        rankCondition = false;
        for (auto card = hands[playerNum -1].begin(); card != hands[playerNum-1].end(); ++card){
            if ((*card).rank == static_cast<R>(whichRank)){
                rankCondition = true;
                break;
            }
        }
        if (!rankCondition){
            cout << "invalid rank id" << endl;
        }
        else{
            if(whichPlayer<= numPlayers){
                condition = true;
            }
        }
        if (whichPlayer < 1 || whichPlayer > numPlayers || whichPlayer == playerNum){
            cout << "invalid player id" << endl;
            condition = false;
        }
    }
    
///check if the target player has the card
    bool targetExist = false;
    if(!hands[playerNum -1].is_empty()){
    targetExist = hands[playerNum -1].request(hands[whichPlayer-1], static_cast<R>(whichRank));
    }
    if (targetExist){
        cout << "Player " << players[whichPlayer-1] << "has the rank" << endl;
        while (collect_books(playerNum)) {}
        cout <<endl;
            return true;
    }else {
        if (!GoFishDeck.is_empty()){
            cout << "Go Fish! Draw a card" << endl;
            GoFishDeck >> hands[playerNum -1];
            cout << endl;
            while (collect_books(playerNum)){}
            return (*(hands[playerNum-1].end())).rank == static_cast<R>(whichRank);
            
        }else{
            cout << "Go Fish! but the deck is empty" << endl;
            cout << "Player " << playerNum-1 << " " << players[playerNum-1] << " is out!";
            GoFishDeck.collect(hands[playerNum-1]);
            outPlayers.push_back(playerNum);
            cout << endl;
            return false;
        }
    }
}

static const int SMALL_DEAL_NUM = 7;
static const int LARGE_DEAL_NUM = 5;


template <typename S, typename R , typename D>
void GoFishGame<S, R, D>::deal(){
    GoFishDeck.shuffle();
    int num_card = SMALL_DEAL_NUM;
    if (numPlayers > 2){
        num_card = LARGE_DEAL_NUM;
    }
    for (int i = 0; i < num_card; i++){
        for (auto& hand : hands){
            if (!GoFishDeck.is_empty()){
                GoFishDeck >> hand;
            }
        }
    }
}

template <typename S, typename R , typename D>
int GoFishGame<S, R, D>::play(){
    deal();
    for (int i = 0; i < numPlayers; i++){
        while (collect_books(i)){}
    }
    bool endGame = false;
    int roundNum = 0;
    ///if the game has not ended, iterate the rounds
    while (!endGame){
        for (int i=0; i < numPlayers; ++i){
            if(find(outPlayers.begin(), outPlayers.end(), i)!= outPlayers.end()){
                continue;
            }
            while (turn(i+1)){}
        }
        cout << "Round " << ++roundNum << " result" << endl;
        for (int i = 0; i < numPlayers; i++){
            cout << "Player " << i + 1 << " " << players[i] << endl;
            cout << "Number of books collected: " << numBooks[i] << endl;
        }
        cout << endl;
        bool allEmpty = true;
        for (int i = 0; i < numPlayers; i++){
            if(!hands[i].is_empty()){
                allEmpty = false;
                break;
            }
        ///conditions for ending the game
            if ((GoFishDeck.is_empty() && allEmpty)||numPlayers - outPlayers.size() < 2){
                endGame = true;
            }
        }
    }
    cout << "Game Ended!" << endl;
    ///printing out the game results
        int bookMax = *max_element(numBooks.begin(), numBooks.end());
        vector<int> maxPlayerNums;
        for (int i= 0 ; i < numPlayers; i++){
            if (numBooks[i] == bookMax){
                maxPlayerNums.push_back(i);
            }
        }
        for (int ind : maxPlayerNums){
            cout << players[ind] << " ";
        }
        cout << endl;
        cout << " were the players who collected the most books" << endl;
        return 0;
}  