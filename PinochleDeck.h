//PinochleDeck.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for PinochleDeck class which is derived from Deck template
//also declarations of enum class PinochleRank, representing Ranks in Pinochle game.
#pragma once
#include <iostream>
#include <vector>

#include "Deck.h"
#include "Suit.h"
#include "Card.h"

enum class PinochleRank {nine, jack, queen, king, ten, ace, undefined};

class PinochleDeck : public Deck<PinochleRank, Suit> {
public:
    static const size_t numPush = 2;
    PinochleDeck();
};

std::ostream& operator<<(std::ostream& ost, const PinochleRank& pRank);

PinochleRank& operator++(PinochleRank& pRank);