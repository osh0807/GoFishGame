//CardSet.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for member functions of CardSet template
#include "CardSet.h"
using namespace std;

template <typename R, typename S>
void CardSet<R, S>::print(std::ostream& ost, size_t num){
    size_t count = 0;
    for(card_it it = cards.begin();it != cards.end(); ++it)
    {
        ost << (*it) << " ";
        count++;
        if(count % num == 0){
            ost << endl;
        }
    }
}

template <typename R, typename S>
CardSet<R, S>& CardSet<R, S>::operator>>(CardSet<R, S>& other){
    if(is_empty()){
        throw runtime_error("Cardset is empty\n");
    }
    Card<R, S> card_ = cards.back();

    other.cards.push_back(card_);
    cards.pop_back();
    return *this;
}

template <typename R, typename S>
bool CardSet<R, S>::is_empty() {
    bool result = CardSet<R, S>::cards.empty();
    return result;
}

template<typename R, typename S>
typename vector< Card<R, S> >::iterator CardSet<R, S>::begin(){
    return CardSet<R, S>::cards.begin();
}

template<typename R, typename S>
typename vector< Card<R, S> >::iterator CardSet<R, S>::end(){
    return CardSet<R, S>::cards.end();
}

///added this helper method for inserting card into protected vector
template<typename R, typename S>
void CardSet<R, S>::addCards(CardSet<R, S> &other) {
    cards.insert(cards.end(), other.begin(), other.end());
}

template<typename R, typename S>
void CardSet<R,S>::sort(){
    std::sort(begin(), end(), isLower_R <R,S>);
}

///move all cards from another cardset
template<typename R, typename S>
void CardSet<R, S>::collect(CardSet<R, S>& cardset_){
    std::move(cardset_.begin(), cardset_.end(), std::back_inserter(cards));
    cardset_.cards.clear();
}

template<typename R, typename S>
void CardSet<R, S>::collect_if(CardSet<R, S>& deck, std::function<bool(Card<R, S>&)> predicate){
    vector<card_type> cardCopy;
    copy_if(deck.begin(), deck.end(), back_inserter(cardCopy), predicate);
    cards.insert(cards.end(), cardCopy.begin(), cardCopy.end());
    ///remove cards with the certain condition
    deck.cards.erase(remove_if(deck.begin(), deck.end(), predicate), deck.end());
}

template<typename R, typename S>
bool CardSet<R, S>::request(CardSet<R, S>& other, const R & r){
    auto it = std::find_if(other.begin(), other.end(), [&r](const card_type & card){
        return card.rank == r;
    });
    if(it != other.end()){
        ///if found the vard, move and return true
        cards.push_back(std::move(*it));
        other.cards.erase(it);
        return true;
    }
    return false;
}