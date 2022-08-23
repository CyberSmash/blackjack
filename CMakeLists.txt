cmake_minimum_required(VERSION 3.20)
project(blackjack)

set(CMAKE_CXX_STANDARD 20)

add_executable(blackjack main.cpp Hand.cpp Card.cpp Card.h Shoe.cpp Shoe.h Player.cpp Player.h RulesEngine.cpp RulesEngine.h Dealer.cpp Dealer.h Table.cpp Table.h)
