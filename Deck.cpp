//Deck.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the member functions of Deck template
#include "Deck.h"

using namespace std;

template <typename R, typename S>
void Deck< R, S >::shuffle() {
    random_device rd;
    mt19937 rng(rd());
    std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), rng);
}
