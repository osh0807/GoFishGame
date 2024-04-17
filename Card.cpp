//Card.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the right shift operator of card template
#include "Card.h"

template<typename R, typename S>
std::ostream& operator<<(std::ostream& ost, const Card<R, S>& card){
    ost << card.rank << " " << card.suit;
    return ost;
}

template <typename R, typename S>
bool isLower_R(const Card<R, S>& first, const Card<R, S>& second){
if(first.rank<second.rank){
    return true;
}
if(first.rank == second.rank){
    if(first.suit <second.suit){
        return true;
    }
}
return false;
}

template <typename R, typename S>
bool isLower_S(const Card<R, S>& first, const Card<R, S>& second){
if(first.suit < second.suit){
    return true;
}
if(first.suit ==second.suit){
    if(first.rank < second.rank){
        return true;
    }
}
return false;
}