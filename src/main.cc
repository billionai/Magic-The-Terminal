#include <stdio.h>
#include <vector>

#include "card.h"

void start_cards(std::vector<Card> &cards){
    /* TODO: Change this to include things to the sqlite database */
    cards.push_back(Card(CREATURE, 1, "Cloudfin Raptor", BLUE));
    cards.push_back(Card(CREATURE, 2, "Evolve", GREEN));
}

int main(){
    std::vector<Card> all_cards;
    start_cards(all_cards);
    for(auto card: all_cards){
        printf("%s\ncard type: %d, card ID: %d, card colors: %d\n", card.name.c_str(), card.type, card.ID, card.color);
    }
    printf("Welcome to Magic the Terminal.\n\nThis area is under constructor, please come back later\n");
    return 0;
}
