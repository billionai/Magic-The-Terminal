#include <fstream>
#include <string>
#include <map>

#include "deck.h"

deck::deck(std::vector<Card> Cards, int card_count):
    count(card_count), cards(Cards)
{
    shuffle();
}

deck::deck(std::string f_name, std::unordered_map<std::string, Card> all_cards){
    std::string line;
    std::ifstream deckFile("database/decks/" + f_name);
    debug_assert(deckFile.is_open());
    getline(deckFile, line);
    while(!line.empty()){
        auto itr = all_cards.find(line);
        debug_assert(itr != all_cards.end());
        cards.push_back(itr->second);
        getline(deckFile, line);
    }
    count = cards.size();
    shuffle();
}

void deck::shuffle(){
    std::vector<int> vec(count,0);
    for (int i=0;i<count; i++) vec[i] = i;
    std::random_shuffle(vec.begin(), vec.end());
    curr_shuffle.clear();
    curr_shuffle.resize(0);
    for(int i:vec){
        curr_shuffle.push_back(i);
    }
}

void deck::insert_to_graveyard(int index){
    graveyard.push_back(index);
}

int deck::search_graveyard(std::string name){
    int i=0;
    for(auto it = graveyard.rbegin();
            it != graveyard.rend();
            it ++, i++){
        if(cards[*it].name == name) return i;
    }
    return -1;
}

int deck::remove_from_graveyard(size_t pos){
    debug_assert(pos < graveyard.size());
    auto it = graveyard.rbegin() + pos;
    int ret = *it;
    //please test this extensively, it is a SO solution
    std::advance(it, 1);
    graveyard.erase(it.base());
    return ret;
}

void deck::print_ordered(){
    for(Card c: cards){
        printf("%s\n", c.name.c_str());
    }
}

void deck::print_short(){
    std::map<std::string, int> ordered;
    for(Card c: cards){
        ordered[c.name]++;
    }
    for(auto it = ordered.begin(); it!=ordered.end(); it++){
        printf("%2d x \t%s\n", it->second, it->first.c_str());
    }
}

void deck::print_shuffle(){
    for(int i:curr_shuffle){
        printf("%s\n", cards[i].name.c_str());
    }
}

deck make_deck(std::string f_name, std::unordered_map<std::string, Card> all_cards){
    std::vector<Card> cards;
    std::string line;
    std::ifstream deckFile("database/deck/" + f_name);
    debug_assert(deckFile.is_open());
    getline(deckFile, line);
    while(!line.empty()){
        debug_assert(all_cards.count(line) == 1);
        cards.push_back((all_cards.at(line)));
        getline(deckFile, line);
    }
    return deck(cards, cards.size());
}
