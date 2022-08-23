#include "Card.h"
#include <stdexcept>
Card::Card(SUIT suit, int val): suit(suit) {
    if (val < 2 || val > FACE_CARD::ACE)
        throw std::logic_error("Error: A card was created that wasn't within the proper range of a standard shoe");
    value = val;
}

std::string Card::suit_to_string() const
{
    switch(suit)
    {
        case SUIT::CLUB:
            return "\xe2\x99\xa3";
        case SUIT::DIAMOND:
            return "\xe2\x99\xa6";
        case SUIT::HEART:
            return "\xe2\x99\xa5";
        case SUIT::SPADE:
            return "\xe2\x99\xa0";
        default:
            return "?";
    }

}

std::string Card::to_string() const
{
    std::string out;

    if (value >= 2 && value < FACE_CARD::JACK)
    {
        out += std::to_string(value);
    }
    else if (value == FACE_CARD::JACK)
    {
        out += "J";
    }
    else if (value == FACE_CARD::QUEEN)
    {
        out += "Q";
    }
    else if (value == FACE_CARD::KING)
    {
        out += "K";
    }
    else if (value == FACE_CARD::ACE)
    {
        out += "A";
    }
    else
        throw std::logic_error("Invalid value for card when converting to a string.");

    out += suit_to_string();

    return out;
}

int Card::get_value() const
{
    return value;
}

SUIT Card::get_suit() const
{
    return suit;
}

std::ostream & operator<<(std::ostream&os, const Card& card)
{
    os << "\x1b[31m" << card.to_string() << "\x1b[00m";
    return os;
}
bool Card::is_ten_card() const
{
    return get_value() >= 10 && get_value() < FACE_CARD::ACE;
}

bool Card::is_ace() const
{
    return get_value() == FACE_CARD::ACE;
}