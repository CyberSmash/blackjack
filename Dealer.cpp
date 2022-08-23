#include "Dealer.h"
#include "RulesEngine.h"
Dealer::Dealer() : Player("Dealer", 0, true)
{
}

actions Dealer::get_action(const Player &dealer, unsigned int hand_num)
{
    // The dealer only ever has one hand.
    int hand_value = RulesEngine::HandValue(hands[0]);
    if (hand_value < 17)
    {
        return actions::hit;
    }
    return actions::stand;
}

std::vector<Card> Dealer::get_obfuscated_hand() const
{
    // Return only the first dealt card.
    return {hands[0].begin(), hands[0].begin() + 1};
}

unsigned int Dealer::num_hands()
{
    return 1;
}

std::vector<Card> Dealer::get_hand()
{
    return hands[0];
}
