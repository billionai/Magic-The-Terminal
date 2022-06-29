#ifndef DECK_H
#define DECK_H

#include <deque>
#include <algorithm>
#include <unordered_map>

#include "card.h"
#include "graphic.h"

class deck{
private:
    int count; //how many cards are in this deck
    std::vector<Card> cards; //which cards are in this deck
    //how these cards are shuffled, we shuffle the indexes of the deck
    std::deque<int> curr_shuffle;
    //Holds an ordered list of cards in the graveyard, referencing them through their indexes.
    std::deque<int> graveyard;
public:
    deck(std::string, std::unordered_map<std::string, Card>);
    deck(std::vector<Card>, int = 60);

    void shuffle(); //make a new shuffle of the deck

    //insert an index to the graveyard
    void insert_to_graveyard(int);
    //find if a card with the given name is in the graveyard
    //and return the first position, if found, or -1 if not
    int search_graveyard(std::string);
    //remove the n-th card from the graveyard, and return the
    //index contained there
    int remove_from_graveyard(size_t);

    void print_ordered();
    void print_short();
    void print_shuffle();
};

deck make_deck(std::string f_name, std::unordered_map<std::string, Card> all_cards);

#endif /* DECK_H */
