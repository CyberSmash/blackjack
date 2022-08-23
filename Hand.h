//
// Created by Jordan Sebastian on 8/21/22.
//

#ifndef BLACKJACK_HAND_H
#define BLACKJACK_HAND_H
#include <vector>
using std::vector;

#include "Card.h"
class Hand {
public:
    Hand();
    Hand(const Card& c);
    Hand(const vector<Card>& hand);
protected:
    vector<Card> hand;
private:
};


#endif //BLACKJACK_HAND_H
