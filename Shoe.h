//
// Created by chrisnoper on 6/12/22.
//

#ifndef BLACKJACK_SHOE_H
#define BLACKJACK_SHOE_H
#include <stack>
#include <algorithm>
#include <random>
#include <memory>
#include "Card.h"

class Shoe {
public:
    Shoe(int num_decks);

    std::string print_shoe();
    void shuffle();
    Card deal();
    virtual ~Shoe() = default;
private:

    std::vector<Card> shoe;
    std::random_device rd;
    std::unique_ptr<std::mt19937> g;
    int num_decks;
    unsigned int shoe_stop = 0;
    unsigned int shoe_pos = 0;
};


#endif //BLACKJACK_SHOE_H
