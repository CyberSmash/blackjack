//
// Created by chrisnoper on 6/12/22.
//

#include "Shoe.h"
#include <array>
#include <iostream>

Shoe::Shoe(int num_decks) : num_decks(num_decks)
{
    g = std::make_unique<std::mt19937>(rd());
    std::array<SUIT, 4> suits { SUIT::HEART, SUIT::SPADE,
                                SUIT::DIAMOND, SUIT::CLUB };

    for (int i = 0; i < num_decks; i++)
    {
        for (int val = 2; val <= FACE_CARD::ACE; val++)
        {
            for(auto suit : suits)
            {
                shoe.emplace_back(suit, val);
            }
        }
    }

    shuffle();
}

void Shoe::shuffle()
{
    // Place the shoe card in the bottom 5th of the cards.
    std::uniform_int_distribution<int> dist(shoe.size() - shoe.size() / 5, shoe.size());
    shoe_stop = dist(*g);
    shoe_pos = 0;
    std::shuffle(shoe.begin(), shoe.end(), *g);
}

Card Shoe::deal()
{
    return shoe[shoe_pos++];
}


std::string Shoe::print_shoe()
{
    std::string out;
    for (auto const& card : shoe)
    {
        out += card.to_string() + "\n";
    }


    return out;
}