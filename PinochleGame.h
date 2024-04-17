//PinochleGame.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for PinochleGame class derived from Game base class
//also declarations for an enum class HoldemState, representing type of HoldemGame
#pragma once
#include "Game.h"
#include "PinochleDeck.h"
#include <map>

enum class PinochleMelds {
    dix, 
    offsuitmarriage, 
    fortyjacks, 
    pinochle, 
    insuitmarriage, 
    sixtyqueens, 
    eightykings, 
    hundredaces, 
    insuitrun, 
    doublepinochle, 
    fourhundredjacks, 
    sixhundredqueens, 
    eighthundredkings, 
    thousandaces, 
    insuitdoublerun
};

std::ostream& operator<<(std::ostream & ost, const PinochleMelds & meld);

class PinochleGame : public Game {
    private:
        void suit_independent_evaluation(const CardSet<PinochleRank, Suit> & playerCards , vector<PinochleMelds>& melds);
        int hasSets(const std::vector< Card<PinochleRank, Suit> >& cards, PinochleRank rank);

    protected:
        PinochleDeck pDeck;
        vector< CardSet <PinochleRank, Suit> > hands;
        virtual void deal(); 

    const size_t HAND_SIZE = 3;

    public:
        PinochleGame(int argc, const char *argv[]);
        virtual int play();
        ///fixed print() function for usabillity
        void print(int i);
        void collect();
        static std::map<PinochleMelds, int> meldMap;

};