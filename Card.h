//Card.h
//soohoon oh; soohoonoh@wustl.edu
//declarations for the card struct template and right shift operator of card template
#pragma once
#include <iostream>

template <typename R, typename S>
struct Card {
    R rank;
    S suit;

    Card(R r_, S s_) : rank(r_), suit(s_) {}
};

template <typename R, typename S>
std::ostream& operator<<(std::ostream& ost, const Card<R, S>& card);

template <typename R, typename S>
bool isLower_R(const Card<R, S>& first, const Card<R, S>& second);

template <typename R, typename S>
bool isLower_S(const Card<R, S>& first, const Card<R, S>& second);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card.cpp"
#endif