#include <iostream>
#include "Card.h"
#include "Shoe.h"
#include "Player.h"
#include "Table.h"
#include "RulesEngine.h"

int main() {

    Table table(10);

    table.add_player(std::make_unique<Player>("Jordan", 1500.00));
    table.add_player(std::make_unique<Player>("Kevin", 1500.00));
    table.add_player(std::make_unique<Player>("Paul", 1500.00));
    table.add_player(std::make_unique<Player>("Marcus", 1500.00));


    while(table.get_state() != Table::table_state::game_over)
    {
        table.step();
    }

    table.print_players();

    return 0;

}
