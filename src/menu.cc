#include "menu.h"

/* Constructs a managed menu without initiating it */
managed_menu::managed_menu():
    started(false) { }

managed_menu::managed_menu(WINDOW* win, std::vector<std::string> options){
    startup(win, options);
}

void managed_menu::startup(WINDOW* win, std::vector<std::string> options){
    int x, y;
    started = true;
    menu_win = win;

    /* Starting menu bits.  */
    bare_menu_items = (ITEM**) calloc(options.size() + 1, sizeof(ITEM *));
    for(size_t i = 0; i < options.size(); i++){
        bare_menu_items[i] = new_item(options[i].c_str(), options[i].c_str());
    }
    bare_menu_items[options.size()] = NULL;
    /* TODO: make menu items be prettier.  */
    /* Print menu options */
    menu = new_menu(bare_menu_items);
    post_menu(menu);
    /* resize the x and y to the second screen's size, minus the border.  */
    getmaxyx(win, y, x);
    y -= 2; x -= 2; /* remove borders */
    for(size_t i = 0; i < options.size(); i++){
        int line = (y/2 + i - options.size());
        int col = (x - options[i].size())/2;
        class_menu_items.push_back(menu_item(line, col, options[i].c_str()));
        class_menu_items[i].print(win);
    }

    /* print first item as selected */
    wattron(win, A_STANDOUT);
    class_menu_items[0].print(win);
    wattroff(win, A_STANDOUT);
}

managed_menu::~managed_menu(){
    unpost_menu(menu);
    free_menu(menu);
    for(size_t i=0; i<class_menu_items.size(); i++)
        free_item(bare_menu_items[i]);
}

void managed_menu::move_menu(int key){
    int curr;
    /* print the old selected item without A_STANDOUT */
    curr = item_index(current_item(menu));
    class_menu_items[curr].print(menu_win);
    switch(key){
        case KEY_UP:
        case 'w':
        case 'k':
            /* select new item */
            menu_driver(menu, REQ_UP_ITEM);
            break;
        case KEY_DOWN:
        case 's':
        case 'j':
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
    }
    /* print newly selected item with A_STANDOUT */
    curr = item_index(current_item(menu));
    wattron(menu_win, A_STANDOUT);
    class_menu_items[curr].print(menu_win);
    wattroff(menu_win, A_STANDOUT);
    update_panels();
    doupdate();
}

int managed_menu::select_item(){
    int selected = item_index(current_item(menu)) + 1;
    if(selected == class_menu_items.size()) /* easy exit code */
        return -1;
    return selected;
}
