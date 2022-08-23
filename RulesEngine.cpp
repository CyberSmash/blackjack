#include "RulesEngine.h"
#include "Card.h"
#include <vector>
#include <algorithm>

int RulesEngine::HandValue(const std::vector<Card>& hand)
{
    int aces = 0;
    int total = 0;
    for (const auto& c : hand)
    {
        if (c.get_value() == FACE_CARD::ACE)
        {
            aces++;
            continue;
        }

        if (c.get_value() < 10)
            total += c.get_value();
        else
            total += 10;
    }
    if (aces == 0)
        return total;
    if (aces == 1)
    {
        if (total + 11 > 21)
        {
            return total + 1;
        }
        else
        {
            return total + 11;
        }
    }

    if (aces > 1 )
    {
        if (total + 11 > 21)
            total += aces;
        else
            total += 11 + (aces - 1);

    }
    else
    {
        total += 11;
        total += (aces - 1);
    }
    return total;


}

bool RulesEngine::is_player_busted(const std::vector<Card>& hand)
{
    unsigned int hand_value = RulesEngine::HandValue(hand);
    return hand_value > RulesEngine::HAND_MAX;
}

bool RulesEngine::is_blackjack(const std::vector<Card>& hand)
{
    // Must be the first two cards.
    if (hand.size() > 2)
        return false;


    bool has_ten = false;
    for (auto& card: hand)
    {

        if (card.is_ten_card())
        {
            has_ten = true;
        }
    }

    return has_ace(hand) && has_ten;
}

bool RulesEngine::has_ace(const std::vector<Card>& hand)
{
    return std::any_of(hand.begin(), hand.end(), [](const Card& c) {
        return c.is_ace();
    });
}

bool RulesEngine::has_ten(const std::vector<Card>& hand)
{
    return std::any_of(hand.begin(), hand.end(), [](const Card& c){
        return c.is_ten_card();
    });
}

/**
 * Determines if the hands's value is "hard" or not.
 *
 * A hands's value is "hard" if there is no ace. This function
 * DOES NOT take into account the the situation where and
 * ace exists, but is being treated as a 1.
 *
 *
 * @param hand - The hands to search.
 * @return True if there is no ace in the hands. False otherwise.
 */
bool RulesEngine::is_hard(const std::vector<Card>& hand)
{
    return has_ace(hand);
}