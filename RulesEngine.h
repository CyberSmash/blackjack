#ifndef BLACKJACK_RULESENGINE_H
#define BLACKJACK_RULESENGINE_H
#include <vector>
#include "Card.h"

class RulesEngine {
public:
    static constexpr double blackjack_payout_multiplier = 1.5;
    static const unsigned int HAND_MAX = 21;
    static int HandValue(const std::vector<Card>& hand);
    static bool is_player_busted(const std::vector<Card>& hand);
    static bool is_blackjack(const std::vector<Card>& hand);
    static bool has_ace(const std::vector<Card>& hand);
    static bool is_hard(const std::vector<Card>& hand);
};


#endif //BLACKJACK_RULESENGINE_H
