//UnoDeck.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for UnoDeck class which is derived from Deck template
//also declarations of enum class UnoDeck, representing Ranks in GoFish game with unodeck
#pragma once
#include "Deck.h"

enum class Color {
    red, blue, green, yellow, black, undefined
};

enum class UnoRank {
    zero, one, two, three, four, five, six, seven, eight, nine, 
    skip, reverse, drawtwo, drawfour, wild, blank, undefined
};

class UnoDeck : public Deck<UnoRank, Color> {
public:
    UnoDeck();
};

std::ostream& operator<<(std::ostream& ost, const UnoRank& uRank);
UnoRank& operator++(UnoRank& uRank);
std::ostream& operator<<(std::ostream& ost, const Color& c);
Color& operator++(Color& c);
