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
    for (auto &c: h) hand.push_back(c);
}

Hand::Hand(const Card& c)
{
    hand.push_back(c);
}


