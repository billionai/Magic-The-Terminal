# Magic the Terminal

This project aims to make an arena game based on Magic the Gathering's Commander style game

DATABASE:

The database is made up of CSV files detailing all information needed. The current syntax works like so:

1. add fields are separated by ','
2. some fields may have multiple values, such as triggers for effects; these are separated by '|'
3. some of THOSE can still have multiple values, specifically thinking of effect chain. these are separated by -

An example of a creature as complex as possible is as follows:

Timberwatch Elf, 16, 2G, 1, 2,,ADD\_CE\_ON\_ELF\_ENTER-ADD\_FREE\_PLUS1|TAP\_ADD\_PLUS1, Elf

which reads like so: Timberwatch Elf, a green elf card, with mana cost of 2 colorless mana and one green mana, has an attack of 1, a toughness of 2, and 2 ability chains: one that adds a complex effect when an elf enters the battlefield, other that adds +1/+1 countes to the target creature with a number equal to the amount of elves on the board.

The current TODO list includes:
* setup specific classes for all card types
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
* added a simple CSV database to the project
* created file reader for lands, creatures and effects
* created complexEffects as a way to chain simple effects together
* created effects that can be activated and generate results
* created trait class, to be used by creature class as information (stuff like flying, haste, ...)
* created creature class
* [2021-11-11]: Created mana class
* [2021-11-07]: Created Land class and parser from CSV file
* [2021-11-06]: Created logging singleton
* [2021-11-06]: created base Card class

Current "I thought about it some more and wont do it" list:
* setting up an sqlite3 database for the cards
    * I will access data in a mostly linear fashion, and all data has a numerical and incrementing ID. I can use a vector well enough for now. maybe will add this if performace starts being bad
* gather enough data on MTG cards to have a deck
    * Not sure if I can actually distribute this. instead, I'm adding locally and wish good luck to anyone that tries to do the same.


Legal disclaimer thingy:
Magic the Terminal is unofficial Fan Content permitted under the Fan Content Policy. Not approved/endorsed by Wizards. Portions of the materials used are property of Wizards of the Coast. ©Wizards of the Coast LLC.
