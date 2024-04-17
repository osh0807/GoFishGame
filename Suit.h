//Suit.h
//soohoon oh; soohoonoh@wustl.edu
//declarations of enum class Suit and operators for it
#pragma once
#include <iostream>

enum class Suit {clubs, diamonds, hearts, spades, undefined};

std::ostream& operator<<(std::ostream& ost, const Suit& suit);
Suit& operator++(Suit& suit);