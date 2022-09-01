#include "Table.h"
#include <iomanip>

Table::Table(double table_minimum) : table_minimum(table_minimum)
{
    state = table_state::check_shoe;
    shoe = std::make_unique<Shoe>(6);
}


void Table::step()
{
    switch (state)
    {
        case table_state::check_shoe:
            check_shoe();
            break;
        case table_state::get_bets:
            get_bets();
            break;
        case table_state::deal:
            deal();
            break;
        case table_state::resolve_blackjacks:
            resolve_blackjacks();
            break;
        case table_state::resolve_players:
            resolve_players();
            break;
        case table_state::resolve_dealer:
            resolve_dealer();
            break;
        case table_state::resolve_table:
            resolve_table();
            break;
        default:
            std::cout << "That is not implemented yet." << std::endl;
            break;
    }
}

void Table::check_shoe()
{
    state = table_state::get_bets;
}

void Table::get_bets()
{
    for(auto& p : players)
    {
        double bet = p->get_bet(table_minimum);
        std::cout << "Player " << p->get_name() << " bet " << bet << std::endl;
    }
    state = table_state::deal;
}

void Table::deal()
{
    for (int i = 0; i < 2; i++)
    {
        for(auto& p : players)
        {
            if (p->get_current_bet() == 0)
                continue;

            // Dealing always deals to the players first hand.
            p->add_card(shoe->deal(), 0);
        }

        dealer.add_card(shoe->deal(), 0);
    }


    for (auto& player: players)
    {
        for (int i = 0; i < player->num_hands(); i++)
        {
            std::cout << std::left << std::setw(10) << player->get_name() << " | "
                      << std::setw(20) << player->get_hand_obj(i) << " | "
                      << std::setw(5) << player->get_current_bet() << std::endl;
        }

    }
    std::cout << std::left << std::setw(10) << dealer.get_name() << " | " <<
    dealer.hand_to_str() << " | " << std::endl;
    state = table_state::resolve_blackjacks;
}

bool Table::resolve_players()
{
        for (auto& player : players)
        {
            if (player->get_current_bet() == 0 || player->is_busted())
                continue;
            resolve_player(player);
        }

        return true;
}

bool Table::resolve_dealer()
{
    actions action = dealer.get_action(dealer, 0);
    std::cout << "Dealer reveals hands: " << dealer.hand_to_str() << std::endl;
    unsigned int hand_total = RulesEngine::HandValue(dealer.get_hand());
    while (action != actions::stand)
    {
        if (action == actions::hit)
        {
            dealer.add_card(shoe->deal(), 0);
            std::cout << dealer.get_name() << " gets a " << dealer.get_hand().back() << std::endl;
            hand_total = RulesEngine::HandValue(dealer.get_hand());
            bool is_busted = RulesEngine::is_player_busted(dealer.get_hand());
            if (is_busted)
            {
                std::cout << dealer.get_name() << " busts with a total of " << hand_total << std::endl;
                dealer.player_bust();
                break;
            }
            std::cout << dealer.get_name() << " has a total of " << hand_total << std::endl;
        }
        action = dealer.get_action(dealer, 0);
    }

    if (action == actions::stand)
    {
        std::cout << dealer.get_name() << " stands with a total of " << hand_total << std::endl;
    }

    state = table_state::resolve_table;
    return false;
}

/**
 * Resolve a players turn.
 * @param player - The player object.
 * @return True of the player busts. False if they don't bust.
 */
bool Table::resolve_player(const std::unique_ptr<Player>& player)
{
    actions action = player->get_action(dealer, 0);
    std::cout << player->get_name() << " " << player->hand_to_str() << std::endl;

    if (action == actions::double_down)
    {
        player->add_card(shoe->deal(), 0);
        std::cout << player->get_name() << " doubles down ... " << std::endl;
        std::cout << player->get_name() << " gets " << player->get_hand(0).back() << std::endl;
        std::cout << player->get_name() << " has a total of " << RulesEngine::HandValue(player->get_hand(0)) << std::endl;

        return handle_bust(player);
    }

    while(action == actions::hit)
    {

        player->add_card(shoe->deal(), 0);
        std::cout << player->get_name() << " hits ... " << std::endl;
        std::cout << player->get_name() << " gets " << player->get_hand(0).back() << std::endl;
        std::cout << player->get_name() << " " << player->hand_to_str() << std::endl;
        std::cout << player->get_name() << " has a total of: "
                  << RulesEngine::HandValue(player->get_hand(0)) << std::endl;
        std::cout << player->get_name() << " has " << RulesEngine::HandValue(player->get_hand(0)) << std::endl;
        bool player_busted = handle_bust(player);
        if (player_busted)
            return true;

        action = player->get_action(dealer, 0);
    }
    std::cout << player->get_name() << " stands with " << RulesEngine::HandValue(player->get_hand(0)) << std::endl;
    state = table_state::resolve_dealer;
    return false;
}

void Table::resolve_table()
{
    unsigned int dealer_hand_value = RulesEngine::HandValue(dealer.get_hand());
    for (auto& player: players)
    {
        // Ignore all players who's play has already been resolved.
        if (player->is_busted() || player->get_current_bet() == 0)
            continue;

        if (dealer.is_busted())
        {
            player->player_win(player->get_current_bet() * 2);
        }
        else if (dealer.is_busted())
        {
            continue;
        }

        unsigned int player_hand_value = RulesEngine::HandValue(player->get_hand(0));
        if (dealer_hand_value > player_hand_value)
        {
            player->player_lose();
        }
        else if (dealer_hand_value == player_hand_value)
        {
            player->player_push();
        }
        else
        {
            std::cout << player->get_name() << " wins $" << player->get_current_bet() << player_hand_value << " > " << dealer_hand_value << std::endl;
            player->player_win(player->get_current_bet());
        }
    }
    state = table_state::game_over;
}

void Table::resolve_blackjacks()
{
    for (auto& player: players)
    {
        if (RulesEngine::is_blackjack(player->get_hand(0)))
        {
            std::cout << player->get_name() << " has a natural blackjack and wins " << player->get_current_bet() * 1.5 << std::endl;
            player->player_win(player->get_current_bet() + (player->get_current_bet() * RulesEngine::blackjack_payout_multiplier));
        }
    }
    state = table_state::resolve_players;
}

void Table::add_player(std::unique_ptr<Player> player)
{
    players.push_back(std::move(player));
}

bool Table::handle_bust(const std::unique_ptr<Player>& player)
{
    bool player_busted = RulesEngine::is_player_busted(player->get_hand(0));
    if (player_busted)
        player->player_bust();
    return player_busted;
}

Table::table_state Table::get_state()
{
    return state;
}

