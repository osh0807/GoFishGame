//HoldemDeck.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for HoldemDeck class which is derived from Deck template
//also declarations of enum class HoldemRank, representing Ranks in holdem game.
#pragma once
#include <iostream>
#include <vector>

#include "Deck.h"
#include "Suit.h"
#include "Card.h"

enum class HoldemRank {
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten, 
    jack, 
    queen, 
    king, 
    ace, 
    undefined
};

class HoldemDeck : public Deck<HoldemRank, Suit> {
public:
    HoldemDeck();
};

std::ostream& operator<<(std::ostream& ost, const HoldemRank& hRank);

HoldemRank& operator++(HoldemRank& hRank);