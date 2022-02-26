#ifndef DECK_H
#define DECK_H

#include <deque>
#include <algorithm>

#include "card.h"

class deck{
private:
    int count; //how many cards are in this deck
    std::vector<Card> cards; //which cards are in this deck
    std::deque<int> curr_shuffle; //how these cards are shuffled
public:
    deck(std::string, std::unordered_map<std::string, Card>);
    deck(std::vector<Card>, int = 60);

    void shuffle(); //make a new shuffle of the deck

    void print_ordered();
    void print_short();
    void print_shuffle();
};

deck make_deck(std::string f_name, std::unordered_map<std::string, Card> all_cards);

#endif /* DECK_H */
