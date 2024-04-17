//Deck.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for Deck class template which is derived from CardSet template
#pragma once
#include <random>
#include <algorithm>
#include "CardSet.h"

template <typename R, typename S>
class Deck : public CardSet<R,S> {
public:
    void shuffle();
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck.cpp"
#endif