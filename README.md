# Magic the Terminal

This project aims to make an arena game based on Magic the Gathering's Commander style game

The current TODO list includes:
* setup specific classes for all card types
    * create a reader function, that can read card information from a file and turn into a card object
* create an Effect class, that handles special triggers
* Create a deck class, that can be shuffled and stores the IDs of the cards
    * It must also have a reader from file
    * And could be coupled with the graveyard, maybe
* Create a player class
    * It must a deck, a graveyard, a hand, know how much mana it generates, and health count
    * Must also be able to play cards from the hand, and have a specific "PlayInstant" method, for reactions
* Create a GameLoop class
    * It will hold references to both players of the game
    * know whose turn it is
    * know which part of the turn it is, to know what kind of cards can be played
    * know which effects have been registered, and call them correctly;
* setup ncurses, to render the game

Current done list:
* [2021-11-07]: Created Land class and parser from CSV file
* [2021-11-06]: Created logging singleton
* [2021-11-06]: created base Card class

Current "I thought about it some more and wont do it" list:
* setting up an sqlite3 database for the cards
    * I will access data in a mostly linear fashion, and all data has a numerical and incrementing ID. I can use a vector well enough for now. maybe will add this if performace starts being bad
* gather enough data on MTG cards to have a deck
    * Not sure if I can actually distribute this. instead, I'm adding locally and wish good luck to anyone that tries to do the same.
