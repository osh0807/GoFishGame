//PinochleGame.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the constructor and member functions of PinochleGame class
#include "PinochleGame.h"
using namespace std;

std::map<PinochleMelds, int> PinochleGame::meldMap = {
    {PinochleMelds::dix, 10},
    {PinochleMelds::offsuitmarriage, 20},
    {PinochleMelds::fortyjacks,40},
    {PinochleMelds::pinochle,40},
    {PinochleMelds::insuitmarriage,40},
    {PinochleMelds::sixtyqueens,60},
    {PinochleMelds::eightykings,80},
    {PinochleMelds::hundredaces,100},
    {PinochleMelds::insuitrun,150},
    {PinochleMelds::doublepinochle,300},
    {PinochleMelds::fourhundredjacks,400},
    {PinochleMelds::sixhundredqueens,600},
    {PinochleMelds::eighthundredkings,800},
    {PinochleMelds::thousandaces,1000},
};

ostream& operator<<(std::ostream & ost, const PinochleMelds & meld){
    switch(meld){
        case PinochleMelds::dix:
            ost << "dix ";
            break;
        case PinochleMelds::offsuitmarriage:
            ost << "offsuitmarriage ";
            break;
        case PinochleMelds::fortyjacks:
            ost << "fortyjacks ";
            break;
        case PinochleMelds::pinochle:
            ost << "pinochle ";
            break;
        case PinochleMelds::insuitmarriage:
            ost << "insuitmarriage ";
            break;
        case PinochleMelds::sixtyqueens:
            ost << "sixtyqueens ";
            break;
        case PinochleMelds::eightykings:
            ost << "eightykings ";
            break;
        case PinochleMelds::hundredaces:
            ost << "hundredaces ";
            break;
        case PinochleMelds::insuitrun:
            ost << "insuitrun ";
            break;
        case PinochleMelds::doublepinochle:
            ost << "doublepinochle ";
            break;
        case PinochleMelds::fourhundredjacks:
            ost << "fourhundredjacks ";
            break;
        case PinochleMelds::sixhundredqueens:
            ost << "sixhundredqueens ";
            break;
        case PinochleMelds::eighthundredkings:
            ost << "eighthundredkings ";
            break;
        case PinochleMelds::thousandaces:
            ost << "thousandaces ";
            break;
        case PinochleMelds::insuitdoublerun:
            ost << "insuitdoublerun ";
            break;
        default:
            break;
    }
    ost << PinochleGame::meldMap[meld] << endl;
    return ost;
}

PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv){
    for(int i=Game::FIRST_PLAYER; i <argc; i++){
        hands.push_back(CardSet <PinochleRank, Suit>());
    }
}

void PinochleGame::deal(){
    int player = 0;
    size_t cardsInHands = 0;
    while(!pDeck.is_empty()){
        pDeck >> hands[player];
        cardsInHands++;
        if(cardsInHands == HAND_SIZE){
            cardsInHands = 0;
            player = (player + 1) % hands.size();
            // use modular computation to go back to the first player
        }
    }
}

void PinochleGame::print(int i){
         cout << players[i] << "'s hand:" << endl;
         hands[i].print(cout, HAND_SIZE);
         cout << endl;
}

void PinochleGame::collect(){
    for (size_t i = 0; i < hands.size(); i++) {
         pDeck.collect(hands[i]);
    }
}

int PinochleGame::play(){
    while(true){
    pDeck.shuffle();
    deal();

    std::vector<PinochleMelds> melds;
    for (size_t i = 0; i < hands.size(); i++) {
    suit_independent_evaluation(hands[i], melds);
    print(i);
    std::cout << "player" << (i+1) << "'s Possible Melds:" << std::endl;
    for (auto meld : melds) {
        std::cout << meld;
    }
        std::cout << std::endl;
    }
    collect();
    if(endGame()){
        break;
    }
    }
    return SUCCESS;
}

int PinochleGame::hasSets(const vector< Card<PinochleRank, Suit> >& cards,PinochleRank rank) {
    vector<int> suitCount(4);
    for (const Card<PinochleRank, Suit> & card : cards) {
        if (card.rank == rank) {
            suitCount[static_cast<int>(card.suit)]++;
        }
    }
    //check if all of the certain rank appear, in which case it will result 2
    return *min_element(suitCount.begin(), suitCount.end());
}


void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit> & playerCards, vector<PinochleMelds> & melds){
    CardSet<PinochleRank, Suit> playerHand(playerCards);

    playerHand.sort();
    vector< Card<PinochleRank, Suit> > handCopy(playerHand.begin(), playerHand.end());
    
    // checking thousandaces & hundredaces
    switch (hasSets(handCopy, PinochleRank::ace)) {
        case 2:
            melds.push_back(PinochleMelds::thousandaces);
            break;
        case 1:
            melds.push_back(PinochleMelds::hundredaces);
            break;
    }

    // checking if eighthundredkings & eightykings
    switch (hasSets(handCopy, PinochleRank::king)) {
        case 2:
            melds.push_back(PinochleMelds::eighthundredkings);
            break;
        case 1:
            melds.push_back(PinochleMelds::eightykings);
            break;
    }


    // checking if sixhundredqueens & sixtyqueens
    switch (hasSets(handCopy, PinochleRank::queen)) {
        case 2:
            melds.push_back(PinochleMelds::sixhundredqueens);
            break;
        case 1:
            melds.push_back(PinochleMelds::sixtyqueens);
            break;
    }


    // checking fourhundredjacks & fortyjacks
    switch (hasSets(handCopy, PinochleRank::jack)) {
        case 2:
            melds.push_back(PinochleMelds::fourhundredjacks);
            break;
        case 1:
            melds.push_back(PinochleMelds::fortyjacks);
            break;
    }


    // checking doublepinochle & pinochle
    int JDiamonds = 0, QSpades = 0;
    for (const Card<PinochleRank, Suit>& card : handCopy) {
        if (card.rank == PinochleRank::jack && card.suit == Suit::diamonds) {
            JDiamonds++;
        } else if (card.rank == PinochleRank::queen &&
                   card.suit == Suit::spades) {
            QSpades++;
        }
    }

    switch (min(JDiamonds, QSpades)) {
        case 2:
            melds.push_back(PinochleMelds::doublepinochle);
            break;
        case 1:
            melds.push_back(PinochleMelds::pinochle);
            break;
    }
}
