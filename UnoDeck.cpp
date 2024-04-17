//UnoDeck.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the member functions of UnoDeck class
#include "UnoDeck.h"

using namespace std;

UnoDeck::UnoDeck(){
    for (Color j = Color::red; j <= Color::yellow; ++j){
        UnoDeck::cards.push_back(Card<UnoRank, Color> (UnoRank::zero, j));
        for (UnoRank k = UnoRank::one; k <= UnoRank::drawtwo; ++k){
            UnoDeck::cards.push_back(Card<UnoRank, Color> (k, j));
            UnoDeck::cards.push_back(Card<UnoRank, Color> (k, j));
        }
    }
    for (UnoRank k = UnoRank::drawfour; k <= UnoRank::blank; ++k){
        for (int i = 0; i < 4; i++){
        UnoDeck::cards.push_back(Card<UnoRank, Color> (k, Color::black));
        }
    }

}

ostream& operator<<(std::ostream& ost, const UnoRank& uRank){
    switch (uRank){
        case UnoRank::zero:
            ost << "0";
            break;
        case UnoRank::one:
            ost << "1";
            break;
        case UnoRank::two:
            ost << "2";
            break;
        case UnoRank::three:
            ost << "3";
            break;
        case UnoRank::four:
            ost << "4";
            break;
        case UnoRank::five:
            ost << "5";
            break;
        case UnoRank::six:
            ost << "6";
            break;
        case UnoRank::seven:
            ost << "7";
            break;
        case UnoRank::eight:
            ost << "8";
            break;
        case UnoRank::nine:
            ost << "9";
            break;
        case UnoRank::skip:
            ost << "skip";
            break;
        case UnoRank::reverse:
            ost << "reverse";
            break;
        case UnoRank::drawtwo:
            ost << "drawtwo";
            break;
        case UnoRank::drawfour:
            ost << "drawfour";
            break;
        case UnoRank::wild:
            ost << "wild";
            break;
        case UnoRank::blank:
            ost << "blank";
            break;
        case UnoRank::undefined:
            ost << "?";
            break;
    }
    return ost;
}

UnoRank& operator++(UnoRank& uRank){
    switch (uRank){
        case UnoRank::undefined:
            break;
        default:
            uRank = static_cast<UnoRank>(static_cast<int>(uRank) + 1);
            break; 
    }
    return uRank;
}

ostream& operator<<(ostream& ost, const Color& c){
    switch (c){
        case Color::red:
            ost << "red";
            break;
        case Color::blue:
            ost << "blue";
            break;
        case Color::green:
            ost << "green";
            break;
        case Color::yellow:
            ost << "yellow";
            break;
        case Color::black:
            ost << "black";
            break;
        default:
            ost << "?";
            break;
    }
    return ost;
}

Color& operator++(Color& c){
    switch (c){
        case Color::undefined:
            break;
        default:
            c = static_cast<Color>(static_cast<int>(c) + 1);
            break; 
    }
    return c;
}