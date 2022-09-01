//
// Created by Jordan Sebastian on 8/21/22.
//

#include "Hand.h"
#include <algorithm>
Hand::Hand()
{
    hand.reserve(2);
}
Hand::Hand(const vector<Card>& h)
{
    std::copy(std::begin(h), std::end(h), std::back_inserter(hand));
}

Hand::Hand(const Card& c)
{
    hand.push_back(c);
}

vector<Card> Hand::get_hand() const
{
    return hand;
}

void Hand::add_card(Card card)
{
    hand.push_back(card);
}

std::ostream &operator<<(std::ostream &os, const Hand &hand)
{
    for (const auto& card : hand.hand)
    {
        os << card << " ";
    }

    return os;
}


