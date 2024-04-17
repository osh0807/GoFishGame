//Suit.h
//soohoon oh; soohoonoh@wustl.edu
//definitions of operator for Suit enum class
#include "Suit.h"

std::ostream& operator<<(std::ostream& ost, const Suit& suit){
    switch(suit){
        case Suit::clubs:
            ost << "C";
            break;
        case Suit::diamonds:
            ost << "D";
            break;
        case Suit::hearts:
            ost << "H";
            break;
        case Suit::spades:
            ost << "S";
            break;
        case Suit::undefined:
            ost << "?";
            break;
    }
    return ost;
}

Suit& operator++(Suit& suit){
    switch(suit){
        case Suit::undefined:
            break;
        default:
            suit = static_cast<Suit>(static_cast<int>(suit)+1);
            break;
    }

    return suit;
}