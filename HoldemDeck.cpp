//HoldemDeck.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the member functions of HoldemDeck class
#include "HoldemDeck.h"

HoldemDeck::HoldemDeck(){
    for (Suit j = Suit::clubs; j <= Suit::spades; ++j){
        for (HoldemRank k = HoldemRank::two; k <=HoldemRank::ace; ++k){
            HoldemDeck::cards.push_back(Card<HoldemRank, Suit> (k, j));
        }
    }  
}

std::ostream& operator<<(std::ostream& ost, const HoldemRank& hRank){
    switch (hRank){
        case HoldemRank::two:
            ost<< "2";
            break;
        case HoldemRank::three:
            ost<< "3";
            break;
        case HoldemRank::four:
            ost<< "4";
            break;
        case HoldemRank::five:
            ost<< "5";
            break;
        case HoldemRank::six:
            ost<< "6";
            break;
        case HoldemRank::seven:
            ost<< "7";
            break;
        case HoldemRank::eight:
            ost<< "8";
            break;
        case HoldemRank::nine:
            ost<< "9";
            break;
        case HoldemRank::ten:
            ost<< "10";
            break;
        case HoldemRank::jack:
            ost<< "J";
            break;
        case HoldemRank::queen:
            ost<< "Q";
            break;
        case HoldemRank::king:
            ost<< "K";
            break;
        case HoldemRank::ace:
            ost<< "A";
            break;
        case HoldemRank::undefined:
            ost<< "?";
            break;
    }
    return ost;
};

HoldemRank& operator++(HoldemRank& hRank){
    switch (hRank){
        case HoldemRank::undefined:
            break;
        default:
            hRank = static_cast<HoldemRank>(static_cast<int>(hRank) + 1);
            break; 
    }
    return hRank;
};