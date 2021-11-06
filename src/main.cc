#include <stdio.h>
#include <vector>

#include "card.h"

void start_cards(std::vector<Card> &cards){
    /* TODO: Change this to include things to the sqlite database */
    cards.push_back(Card(CREATURE, 1, "Cloudfin Raptor", BLUE));
    cards.push_back(Card(CREATURE, 2, "Experiment One", GREEN));
}

int main(){
    std::vector<Card> all_cards;
    start_cards(all_cards);
    printf("Welcome to magic the terminal!\n\n");
    for(auto card: all_cards){
        printf("%s\ncard type: %s, card ID: %d, card colors: %s\n", card.name.c_str(),
                            cardTypeAsString(card.type).c_str(), card.ID, cardColorAsString(card.color).c_str());
    }
    return 0;
}
