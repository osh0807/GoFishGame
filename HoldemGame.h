//HoldemGame.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for HoldemGame class derived from Game base class
//also declarations for an enum class HoldemState, representing type of HoldemGame
#pragma once
#include "HoldemDeck.h"
#include "Game.h"

enum class HoldemState{
    preflop,
    flop,
    turn,
    river,
    undefined
};

enum class HoldEmHandRank {
     xhigh, 
     pair, twopair, threeofakind, straight, 
     flush, fullhouse, fourofakind, straightflush, 
     undefined
};

class HoldemGame: public Game {
    private:
        HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldemRank, Suit>& playerCards);
        ///helper functions for holdem_hand_evaluation()
        bool isFlush(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isStraight(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isFourOfAKind(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isFullHouse(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isThreeOfAKind(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isTwoPair(const std::vector<Card<HoldemRank, Suit> > &cards);
        bool isPair(const std::vector<Card<HoldemRank, Suit> > &cards);
    protected:
        HoldemState state;
        HoldemDeck hDeck;
        std::vector< CardSet<HoldemRank, Suit> > hands;
        CardSet<HoldemRank, Suit> sharedCards;

        const size_t HAND_SIZE = 2;
        const int FLOP_BOARD_SIZE = 3;
        const int TURN_BOARD_SIZE = 4;
        const int RIVER_BOARD_SIZE = 5;
        const size_t FINAL_HAND_SIZE = 5;

        virtual void deal();
        void printHands();
        void printBoard(size_t num);
        void collect();
    
    public:
        struct HoldemGameStruct {
            CardSet<HoldemRank, Suit> hand;
            std::string playerName;
            HoldEmHandRank handRank;

            HoldemGameStruct(CardSet<HoldemRank, Suit> cardsParam, 
            std::string playerNameParam, HoldEmHandRank handRankParam): 
            hand(cardsParam),
            playerName(playerNameParam),
            handRank(handRankParam) 
            {}
        };
        HoldemGame(int argc, const char *argv[]);
        virtual int play();

};

std::ostream& operator<<(std::ostream & ost, const HoldEmHandRank & handRanks);
bool operator<(const HoldemGame::HoldemGameStruct &param1, const HoldemGame::HoldemGameStruct &param2);
