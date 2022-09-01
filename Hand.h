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
    explicit Hand(const Card& c);
    explicit Hand(const vector<Card>& hand);
    vector<Card> get_hand() const;
    void add_card(Card card);
    friend std::ostream & operator<<(std::ostream&os, const Hand& hand);


protected:
    vector<Card> hand;
private:
};


#endif //BLACKJACK_HAND_H
