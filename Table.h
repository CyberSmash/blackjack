//
// Created by chrisnoper on 6/12/22.
//

#ifndef BLACKJACK_TABLE_H
#define BLACKJACK_TABLE_H
#include "Player.h"
#include "Dealer.h"
#include "Card.h"
#include "RulesEngine.h"
#include <vector>
#include <memory>
#include "Shoe.h"
class Table {

public:
    enum class table_state
    {
        check_shoe,
        get_bets,
        deal,
        resolve_blackjacks,
        resolve_players,
        resolve_dealer,
        resolve_table,
        game_over,
    };
    explicit Table(double table_minimum);

    void add_player(std::unique_ptr<Player> player);
    void step();
    void get_bets();
    void check_shoe();
    void deal();
    void resolve_blackjacks();

    bool resolve_players();
    bool resolve_player(const std::unique_ptr<Player>& player);
    bool resolve_dealer();
    void resolve_table();

    table_state get_state();

    virtual ~Table() = default;
private:

    bool handle_bust(const std::unique_ptr<Player>& player);

    std::vector<std::unique_ptr<Player>> players;
    Dealer dealer;
    table_state state;
    std::unique_ptr<Shoe> shoe;
    double table_minimum;
};


#endif //BLACKJACK_TABLE_H
