//
// Created by chrisnoper on 6/12/22.
//

#ifndef BLACKJACK_DEALER_H
#define BLACKJACK_DEALER_H

#include <vector>
#include "Player.h"

class Dealer : public Player {
public:
    Dealer();
    actions get_action(const Player &dealer) override;
    std::vector<Card> get_obfuscated_hand() const;


    ~Dealer() override = default;
protected:

};


#endif //BLACKJACK_DEALER_H
