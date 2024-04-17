//CardSet.h
//soohoon oh; soohoonoh@wustl.edu
//declarations of class template CardSet
#pragma once
#include "Card.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

template <typename R, typename S>
class CardSet{
    protected:
        std::vector< Card<R, S> > cards;

    public:
        typedef Card<R, S> card_type;
        typedef S suit_type;
        typedef R rank_type;
        typedef typename std::vector< Card<R, S> >::iterator card_it;

        CardSet() = default;
        CardSet(const CardSet<R, S>& other) = default;
        void print(std::ostream& ost, size_t num);
        bool is_empty();
        CardSet<R, S>& operator>>(CardSet<R, S>& other);
        card_it begin();
        card_it end();
        void addCards(CardSet<R, S> & other);
        void sort();
        void collect(CardSet<R, S>& cardset_);
        void collect_if(CardSet<R, S>& deck, std::function<bool(Card<R, S>&)> predicate);
        bool request(CardSet<R, S>& other, const R & r);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet.cpp"
#endif