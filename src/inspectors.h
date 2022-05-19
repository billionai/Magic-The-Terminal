/* This file is used to create the screens to inspec all known cards, all known and created decks, and all effects.
   Each of these options are turned into a class, thath will create their panel with a list of all known items.
   Each item will be able to be inspected further, as explained in each of the classes.

   FIXME: Once saves are implemented, this inspector should be moved to __after__ loading the desired save, and
   it should obfuscate the unseen cards/decks/effects. sort of like a pokedex for cards.
*/

#include "utils.h"
#include "graphic.h"
#include "menu.h"
#include <string>
#include <vector>

/* This creates the base menu to select what to inspect, effects, cards, and decks.
*/
class inspector_menu{
private:
    int width, height;
    WINDOW* win;
    PANEL* pan;
    managed_menu menu;
public:
    /* Constructor for the menu to choose inspectors. 
       It takes 2 ints, WIDTH and HEIGHT, which are the sizes of the ORIGINAL window, not the sizes of the final menu
       Final sizes are calculated inside the constructor, as 75% of the original size,
       unless this is <= size(biggest_text), in which case it is the same as the original size. */
    inspector_menu(int, int);
    ~inspector_menu();

    void move_menu(int);
    int select_item();
    int get_input();
};

/* This panel creates a list of all known effects, and by selecting an effect by name it opens an
   effect_inspector, that shows the chain of effects that may take place if this effect is triggered. */
class inspect_all_effects{
private:
    int width, height;
    WINDOW* win;
    PANEL* pan;
    managed_menu;
public:
    inspect_all_effects(int, int);
    ~inspect_all_effects();
};

/* This panel creates a list of all known cards, and by selecting a card by name, it will open a
   card_inspector panel, with all the interesting information - name, mana cost, atk/def, effects and so on.
   At some point, ascii art should be available too.
   Hopefully, the card_inspector will allow the user to check effects by calling an effect_inspector.
*/
class inspect_all_cards {
};

/* This panel creates a list of all known decks. Decks are found by listing the directory, instead of
   accessing a database for now. By selecting a deck, a deck_inspector is created, which lists all
   cards in the selected deck, and each card can be selected to open a card_inspector.

   FIXME: Once an actual SQL database is implemented, decks should be migrated to it.
*/
class inspect_all_decks {
};

/* ===========================================================================
   Exported functions! */

/* Main inspector menu. This lets you choose which part of the database you want to inspect
   and calls the relevant functions. */
void choose_inspector();
