//
// Created by chrisnoper on 6/12/22.
//

#include "Player.h"
#include <utility>
#include <sstream>
#include "RulesEngine.h"

Player::Player(std::string  name,
               double starting_bankroll, bool is_dealer) :
        name(std::move(name)), starting_bankroll(starting_bankroll), is_dealer(is_dealer), hands(1)
{
    current_bankroll = starting_bankroll;
}

void Player::add_card(const Card& card, unsigned int hand_num)
{
    hands[hand_num].add_card(card);
}

double Player::get_current_bet()
{
    return current_bet;
}

double Player::get_bet(double minimum)
{
    if (minimum <= current_bankroll)
    {
        current_bankroll -= minimum;
        current_bet = minimum;
        return minimum;
    }

    return 0;
}


bool Player::can_increase_bet(double amount)
{
    return amount <= current_bankroll;
}

void Player::increase_bet(double amount)
{
    current_bet += amount;
    current_bankroll -= amount;
}

void Player::player_win(double amount)
{
    std::cout << get_name() << " wins $" << amount << std::endl;
    current_bet = 0;
    current_bankroll += amount;
}

void Player::player_lose()
{
    std::cout << get_name() << " loses." << std::endl;
    current_bet = 0;
}

void Player::player_bust()
{
    std::cout << get_name() << " busts." << std::endl;
    busted = true;
    player_lose();
}

void Player::player_push()
{
    std::cout << get_name() << " pushes." << std::endl;
    current_bankroll += current_bet;
    current_bet = 0;
}

bool Player::is_busted()
{
    return busted;
}



std::string Player::get_name()
{
    return name;
}


std::vector<Card> Player::get_hand(unsigned int hand_num) const
{
    return hands[hand_num].get_hand();
}

Hand& Player::get_hand_obj(unsigned int hand_num)
{
    return hands[hand_num];
}

/**
 * A really dumb player, always tries to beat the dealer, assuming the dealer
 * has a 10 in his hidden card.
 * @param dealer - The dealer object.
 * @return - An action to take.
 */
actions Player::get_action(const Player& dealer, unsigned int hand_num)
{
    int current_hand_value = RulesEngine::HandValue(get_hand(0));

    if (current_hand_value == 11 && can_increase_bet(current_bet))
    {
        double_down();
        return actions::double_down;
    }


    if (current_hand_value >= 17)
    {
        return actions::stand;
    }

    // Dealers only ever have one hand.
    int dealer_value = RulesEngine::HandValue(dealer.get_hand(0));
    // Assume the dealer has a 10.
    dealer_value += 10;

    if (current_hand_value <= dealer_value)
    {
        return actions::hit;
    }
    return actions::stand;

}

std::string Player::hand_to_str()
{
    std::stringstream ss;
    for (unsigned int hand_num = 0; hand_num < num_hands(); hand_num++)
    {
        ss << hand_num << ": ";
        for (auto& c : get_hand(hand_num))
        {
            ss << c << " ";
        }
        ss << std::endl;
    }


    return ss.str();
}

void Player::reset_player()
{
    busted = false;
    current_bet = 0;
}

void Player::double_down()
{
    current_bankroll -= current_bet;
    current_bet *= 2;
}

unsigned int Player::num_hands()
{
    return hands.size();
}

std::ostream &operator<<(std::ostream os, const Player &player)
{

}
