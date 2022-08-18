#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H
#include <string>
#include <iostream>

enum class SUIT {
    DIAMOND,
    SPADE,
    CLUB,
    HEART,
};
enum FACE_CARD {
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14,
};

class Card {

public:
    Card(SUIT suit, int val);
    std::string  to_string() const;
    std::string suit_to_string() const;
    int get_value() const;
    SUIT get_suit() const;
    bool is_ten_card() const;
    bool is_ace() const;
    friend std::ostream & operator<<(std::ostream&os, const Card& card);
    virtual ~Card() = default;

private:
    SUIT suit;
    int value;

};


#endif //BLACKJACK_CARD_H
