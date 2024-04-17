//PinochleDeck.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the member functions of PinochleDeck class
#include "PinochleDeck.h"

PinochleDeck::PinochleDeck(){
    for (size_t i = 0; i < numPush; i++){
        for ( Suit j = Suit::clubs; j <= Suit::spades; ++j){
            for (PinochleRank k = PinochleRank::nine; k <=PinochleRank::ace; ++k){
                PinochleDeck::cards.push_back(Card<PinochleRank, Suit> (k, j));
            }
        }
    }
}

std::ostream& operator<<(std::ostream& ost, const PinochleRank& pRank){
    switch(pRank){
        case PinochleRank::nine:
            ost<< "9";
            break;
        case PinochleRank::jack:
            ost<< "J";
            break;
        case PinochleRank::queen:
            ost<< "Q";
            break;
        case PinochleRank::king:
            ost<< "K";
            break;
        case PinochleRank::ten:
            ost<< "10";
            break;
        case PinochleRank::ace:
            ost<< "A";
            break;
        case PinochleRank::undefined:
            ost<< "?";
            break;
    }
    return ost;
}

PinochleRank& operator++(PinochleRank& pRank){
    switch(pRank){
        case PinochleRank::undefined:
            break;
        default:
            pRank = static_cast<PinochleRank>(static_cast<int>(pRank)+1);
            break;
    }
    return pRank;
}