//HoldemGame.cpp
//soohoon oh; soohoonoh@wustl.edu
//definitions for the constructor and member functions of HoldemGame class
#include "HoldemGame.h"
#include <bits/stdc++.h>

using namespace std;

ostream& operator<<(ostream & ost, const HoldEmHandRank & handRank){
        switch (handRank) {
        case HoldEmHandRank::xhigh:
            ost << "X-High";
            break;
        case HoldEmHandRank::pair:
            ost << "Pair";
            break;
        case HoldEmHandRank::twopair:
            ost << "Two Pair";
            break;
        case HoldEmHandRank::threeofakind:
            ost << "Three of a Kind";
            break;
        case HoldEmHandRank::straight:
            ost << "Straight";
            break;
        case HoldEmHandRank::flush:
            ost << "Flush";
            break;
        case HoldEmHandRank::fullhouse:
            ost << "Full House";
            break;
        case HoldEmHandRank::fourofakind:
            ost << "Four of a Kind";
            break;
        case HoldEmHandRank::straightflush:
            ost << "Straight Flush";
            break;
        default:
            ost << "Undefined";
            break;
    }
    return ost;
}

bool operator<(const HoldemGame::HoldemGameStruct &param1, const HoldemGame::HoldemGameStruct &param2){
    if(param1.handRank < param2.handRank){
        return true;
    }
    CardSet<HoldemRank, Suit> player1 = param1.hand; 
    CardSet<HoldemRank, Suit> player2 = param2.hand;
///updated the logic with ne member functions
    vector<Card<HoldemRank, Suit> > player1copy(player1.begin(), player1.end());
    vector<Card<HoldemRank, Suit> > player2copy(player2.begin(), player2.end());

    sort(player1copy.begin(), player1copy.end(), isLower_R<HoldemRank, Suit>);
    reverse(player1copy.begin(), player1copy.end());
    sort(player2copy.begin(), player2copy.end(), isLower_R<HoldemRank, Suit>);
    reverse(player2copy.begin(), player2copy.end());

    if (param1.handRank == HoldEmHandRank::pair && param1.handRank == param2.handRank) {
         HoldemRank pairRank1, pairRank2;
         vector<Card<HoldemRank, Suit> >::const_iterator first1, last1, first2, last2;
         for (size_t i = 1; i < player1copy.size(); i++) {
             if (player1copy[i-1].rank == player1copy[i].rank) {
                 pairRank1 = player1copy[i].rank;
                 first1 = player1copy.begin() + (i-1);
                 last1 = player1copy.begin() + i;
             }
             if (player2copy[i-1].rank == player2copy[i].rank) {
                 pairRank2 = player2copy[i].rank;
                 first2 = player2copy.begin() + (i-1);
                 last2 = player2copy.begin() + i;
             }
         }
         if (pairRank1 < pairRank2) {
             return true;
         }
         else {
             vector<Card<HoldemRank, Suit> > nonPairplayer1(first1, last1);
             vector<Card<HoldemRank, Suit> > nonPairplayer2(first2, last2);
             for (size_t i = 0; i < nonPairplayer1.size(); i++) {
                 if (nonPairplayer1[i].rank < nonPairplayer2[i].rank) {
                     return true;
                 }
             }
         }
     }

     if (param1.handRank == HoldEmHandRank::twopair && param1.handRank == param2.handRank) {
         vector<HoldemRank> pairRank1, pairRank2;
         for (size_t i = 1; i < player1copy.size(); i++) {
             if (player1copy[i-1].rank == player1copy[i].rank) {
                 pairRank1.push_back(player1copy[i].rank);
             }
             if (player2copy[i-1].rank == player2copy[i].rank) {
                 pairRank2.push_back(player2copy[i].rank);
             }
         }
         for (size_t i = 0; i < pairRank1.size(); i++) {
             if (pairRank1[i] < pairRank2[i]) {
                 return true;
             }
         }
         HoldemRank nonPairRank1, nonPairRank2;
         for (size_t i = 0; i < player1copy.size(); i++) {
             if (find(pairRank1.begin(), pairRank1.end(), player1copy[i].rank) 
                 == pairRank1.end()) {
                 nonPairRank1 = player1copy[i].rank;
             }
             if (find(pairRank2.begin(), pairRank2.end(), player2copy[i].rank) 
                 == pairRank2.end()) {
                 nonPairRank2 = player2copy[i].rank;
             }
         }
         if (nonPairRank1 < nonPairRank2) {
             return true;
         }
     }

     if ((param1.handRank == HoldEmHandRank::threeofakind || param1.handRank == HoldEmHandRank::fullhouse) 
         && (param1.handRank == param2.handRank)) {
         HoldemRank pairRank1, pairRank2;
         for (size_t i = 2; i < player1copy.size(); i++) {
             if (player1copy[i-1].rank == player1copy[i].rank 
                 && player1copy[i-2].rank == player1copy[i].rank) {
                 pairRank1 = player1copy[i].rank;
             }
             if (player2copy[i-1].rank == player2copy[i].rank 
                 && player2copy[i-2].rank == player2copy[i].rank) {
                 pairRank2 = player2copy[i].rank;
             }
         }
         if (pairRank1 < pairRank2) {
             return true;
         }
     }

     if ((param1.handRank == HoldEmHandRank::straight || param1.handRank == HoldEmHandRank::straightflush) 
         && (param1.handRank == param2.handRank)) {
         if (player1copy[0].rank < player2copy[0].rank) {
             return true;
         }
     }


     if ((param1.handRank == HoldEmHandRank::flush || param1.handRank == HoldEmHandRank::xhigh) 
         && (param1.handRank == param2.handRank)) {
         for (size_t i = 0; i < player1copy.size(); i++) {
             if (player1copy[i].rank < player2copy[i].rank) {
                 return true;
             }
         }
     }

     if (param1.handRank == HoldEmHandRank::fourofakind && param1.handRank == param2.handRank) {
         HoldemRank pairRank1 = player1copy[1].rank;
         HoldemRank pairRank2 = player2copy[1].rank;
         if (pairRank1 < pairRank2) {
             return true;
         }
     }

     return false;
    
}

HoldemGame::HoldemGame(int argc, const char *argv[]): Game(argc, argv){
    HoldemGame::state = HoldemState::preflop;
    for(int i = Game::FIRST_PLAYER; i <argc; i++){
        hands.push_back(CardSet <HoldemRank, Suit>());
    }
}

HoldEmHandRank HoldemGame::holdem_hand_evaluation(const CardSet<HoldemRank, Suit>& playerCards){
    CardSet<HoldemRank, Suit> playerHand(playerCards);
    ///copy over the card deck

    playerHand.sort();
    
    vector< Card<HoldemRank, Suit> > handCopy(playerHand.begin(), playerHand.end());

    if(handCopy.size() != FINAL_HAND_SIZE) {
        return HoldEmHandRank::undefined;
    }
    sort(handCopy.begin(), handCopy.end(),isLower_R<HoldemRank, Suit>);

    bool flush = isFlush(handCopy);
    bool straight = isStraight(handCopy);

    // straight flush
    if (flush && straight) {
        return HoldEmHandRank::straightflush;
    }

    if (isFourOfAKind(handCopy)) {
        return HoldEmHandRank::fourofakind;
    }

    if (isFullHouse(handCopy)) {
        return HoldEmHandRank::fullhouse;
    }

    if (flush) {
        return HoldEmHandRank::flush;
    }

    if (straight) {
        return HoldEmHandRank::straight;
    }

    if (isThreeOfAKind(handCopy)) {
        return HoldEmHandRank::threeofakind;
    }

    if (isTwoPair(handCopy)) {
        return HoldEmHandRank::twopair;
    }

    if (isPair(handCopy)) {
        return HoldEmHandRank::pair;
    }

    return HoldEmHandRank::xhigh;

}

///helper functions for holdem_hand_evaluation()

bool HoldemGame::isFlush(const vector<Card<HoldemRank, Suit> > &cards) {
    for (size_t i = 1; i < cards.size(); i++) {
        if (cards[i].suit != cards[i - 1].suit) {
            return false;
        }
    }
    return true;
}


bool HoldemGame::isStraight(const vector<Card<HoldemRank, Suit> > &cards) {
    for (size_t i = 1; i < cards.size(); i++) {
        int prevRank = static_cast<int>(cards[i - 1].rank);
        int currRank = static_cast<int>(cards[i].rank);
        if (prevRank + 1 != currRank &&
            !(cards[i - 1].rank == HoldemRank::five &&
              cards[i].rank == HoldemRank::ace)) {
            return false;
        }
    }
    return true;
}


bool HoldemGame::isFourOfAKind(const vector<Card<HoldemRank, Suit> > &cards) {
    return cards[0].rank == cards[3].rank || cards[1].rank == cards[4].rank;
}


bool HoldemGame::isFullHouse(const vector<Card<HoldemRank, Suit> > &cards) {
    return (cards[0].rank == cards[1].rank && cards[2].rank == cards[4].rank) ||
           (cards[0].rank == cards[2].rank && cards[3].rank == cards[4].rank);
}


bool HoldemGame::isThreeOfAKind(const vector<Card<HoldemRank, Suit> > &cards) {
    return cards[0].rank == cards[2].rank || cards[1].rank == cards[3].rank ||
           cards[2].rank == cards[4].rank;
}


bool HoldemGame::isTwoPair(const vector<Card<HoldemRank, Suit> > &cards) {
    return (cards[0].rank == cards[1].rank && cards[2].rank == cards[3].rank) ||
           (cards[0].rank == cards[1].rank && cards[3].rank == cards[4].rank) ||
           (cards[1].rank == cards[2].rank && cards[3].rank == cards[4].rank);
}


bool HoldemGame::isPair(const vector<Card<HoldemRank, Suit> > &cards) {
    return cards[0].rank == cards[1].rank || cards[1].rank == cards[2].rank ||
           cards[2].rank == cards[3].rank || cards[3].rank == cards[4].rank;
}


void HoldemGame::deal(){
    switch(state){
        case HoldemState::preflop:
            for(size_t i = 0; i < HAND_SIZE; i++){
                for(size_t j = 0; j < players.size(); j++){
                    hDeck >> hands[j];
                }
            }
            state = HoldemState::flop;
            break;
        
        case HoldemState::flop:
            for(int i = 0; i < FLOP_BOARD_SIZE; i++){
                hDeck >> sharedCards;
            }
            state = HoldemState::turn;
            break;

        case HoldemState::turn:
            hDeck >> sharedCards;
            state = HoldemState:: river;
            break;

        case HoldemState::river:
            hDeck >> sharedCards;
            state = HoldemState:: undefined;
            break;
        default:
            break;
    }

}

void HoldemGame::printHands(){
    for (size_t i = 0; i < players.size(); i++) {
         cout << players[i] << "'s hands:" << endl;
         hands[i].print(cout, HAND_SIZE);
         cout << endl;
     }
}

void HoldemGame::printBoard(size_t boardSize){
    sharedCards.print(cout, boardSize);
}

void HoldemGame::collect(){
    for (size_t i = 0; i < players.size(); i++) {
         hDeck.collect(hands[i]);
    }
    hDeck.collect(sharedCards);
}

int HoldemGame::play(){
    while(true){
        hDeck.shuffle();
        state = HoldemState::preflop;
        deal();
        printHands();

        deal();
        cout << "BOARD (flop):" << endl;
        printBoard(FLOP_BOARD_SIZE);
        cout << endl;
        
        vector<HoldemGameStruct> structs;
         for (size_t i = 0; i < players.size(); i++) {
             structs.push_back(HoldemGameStruct(hands[i], players[i], HoldEmHandRank::undefined));
        }
        
       
        for (size_t i = 0; i < structs.size(); i++) {
             structs[i].hand.addCards(sharedCards);
             structs[i].handRank = holdem_hand_evaluation(structs[i].hand);
        }
        for (auto &hgStruct : structs){
            hgStruct.hand.sort();
            reverse(hgStruct.hand.begin(), hgStruct.hand.end());
        }
///updated sort and reverse logic with new member function
        std::sort(structs.begin(), structs.end(), [](const HoldemGameStruct &a, const HoldemGameStruct &b)
        {
            return a < b;
        });
        std::reverse(structs.begin(), structs.end());

         for (size_t i = 0; i < structs.size(); i++) {
             cout << structs[i].playerName << "'s rank: " << structs[i].handRank << endl;
        }
        cout << endl;

        deal();
        cout << "BOARD (turn):" << endl;
        printBoard(TURN_BOARD_SIZE);

        deal();
        cout << "BOARD (river):" << endl;
        printBoard(RIVER_BOARD_SIZE);
        collect();
        cout << endl;
        
        if(endGame()){
            break;
        }
    }
    return SUCCESS;
}

