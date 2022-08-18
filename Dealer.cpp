#include "Dealer.h"
#include "RulesEngine.h"
Dealer::Dealer() : Player("Dealer", 0, true)
{
}

actions Dealer::get_action(const Player &dealer)
{
    int hand_value = RulesEngine::HandValue(hand);
    if (hand_value < 17)
    {
        return actions::hit;
    }
    return actions::stand;
}

std::vector<Card> Dealer::get_obfuscated_hand() const
{
    // Return only the first dealt card.
    return {hand.begin(), hand.begin() + 1};
}