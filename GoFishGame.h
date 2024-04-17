//HoldemGame.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for GoFishGame class template derived from Game base class

#pragma once
#include "Game.h"
#include "HoldemDeck.h"
#include "UnoDeck.h"
#include "PinochleDeck.h"
#include <type_traits>

template <typename S = Suit, typename R = HoldemRank, typename D=HoldemDeck>
class GoFishGame: public Game {
    static_assert(std::is_base_of< CardSet<R, S>, D>::value, "Deck must be derived from CardSet <Rank, Suit>");
    public:
        GoFishGame(int argc, const char *argv[]);
        virtual ~GoFishGame() = default;
        virtual int play();
        bool collect_books(int playerNum);
    protected:
        int numPlayers;
        D GoFishDeck;
        int deckNum;
        std::vector< CardSet<R, S> > hands;
        std::vector< CardSet<R, S> > books;
        std::vector<int> numBooks;
        std::vector<int> outPlayers;
        virtual void deal();
        bool turn(int playerNum);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "GoFishGame.cpp"
#endif
