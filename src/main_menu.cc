#include <vector>
#include <string>
#include <fstream>

#include "utils.h"
#include "main_menu.h"

/* how many options does the main menu have. */
#define NUM_OPTIONS 2
const std::string item_names[] ={
    "start game",
    "exit"
};
#define NUM_LINES_LOGO 5

std::vector<std::string> read_logo_file() {
    std::vector<std::string> lines;
    std::ifstream logoFile("graphics/logo");
    debug_assert(logoFile.is_open());
    lines.resize(NUM_LINES_LOGO);
    for(int i = 0; i < NUM_LINES_LOGO; i++){
        getline(logoFile, lines[i]);
    }
    return lines;
}

main_menu_info::main_menu_info() {
    int x, y, starty, startx;
    std::vector<std::string> lines = read_logo_file();
    std::string simple_logo = "MAGIC The Terminal";

    /* Starting the separated screens with logo.  */
    getmaxyx(stdscr, y, x);
    has_logo = (y > NUM_LINES_LOGO + NUM_OPTIONS);
    if(has_logo){
        windows[0] = newwin(NUM_LINES_LOGO, x, 0, 0);
        panels[0] = new_panel(windows[0]);
        if(x > (int)lines[0].size()){
            startx = (x - lines[0].size())/2;
            for(int i = 0; i < NUM_LINES_LOGO; i++)
                mvwprintw(windows[0], i, startx, lines[i].c_str());
        }else{
            startx = (x - simple_logo.size())/2;
            mvwprintw(windows[0], 2, startx, simple_logo.c_str());
        }
        starty = 5;
    }else{
        starty = 0;
        windows[0] = NULL;
        panels[0] = NULL;
    }
    windows[1] = newwin(y - starty, x, starty, 0);
    panels[1] = new_panel(windows[1]);
    box(windows[1],0,0);

    /* Starting menu bits.  */
    bare_menu_items = (ITEM**) calloc(NUM_OPTIONS + 1, sizeof(ITEM *));
    for(int i = 0; i < NUM_OPTIONS; i++){
        bare_menu_items[i] = new_item(item_names[i].c_str(), item_names[i].c_str());
    }
    bare_menu_items[NUM_OPTIONS] = NULL;
    /* TODO: make menu items be prettier.  */
    /* Print menu options */
    menu = new_menu(bare_menu_items);
    post_menu(menu);
    /* resize the x and y to the second screen's size, minus the border.  */
    getmaxyx(windows[1], y, x);
    y -= 2; x -= 2; /* remove borders */
    for(int i = 0; i < NUM_OPTIONS; i++){
        int line = (y/2 + i - NUM_OPTIONS);
        int col = (x - item_names[i].size())/2;
        class_menu_items.push_back(main_menu_item(line, col, item_names[i].c_str()));
        class_menu_items[i].print(windows[1]);
    }

    /* print first item as selected */
    wattron(windows[1], A_STANDOUT);
    class_menu_items[0].print(windows[1]);
    wattroff(windows[1], A_STANDOUT);
    update_panels();
    doupdate();
}

main_menu_info::~main_menu_info(){
    unpost_menu(menu);
    free_menu(menu);
    for(int i=0; i<NUM_OPTIONS; i++)
        free_item(bare_menu_items[i]);
    if(windows[0]){
        del_panel(panels[0]);
        delwin(windows[0]);
    }
    del_panel(panels[1]);
    delwin(windows[1]);
}

void main_menu_info::move_menu(int key){
    int curr;
    /* print the old selected item without A_STANDOUT */
    curr = item_index(current_item(menu));
    class_menu_items[curr].print(windows[1]);
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
    wattron(windows[1], A_STANDOUT);
    class_menu_items[curr].print(windows[1]);
    wattroff(windows[1], A_STANDOUT);
    update_panels();
    doupdate();
}

int main_menu_info::select_item(){
    int selected = item_index(current_item(menu)) + 1;
    if(selected == class_menu_items.size()) /* easy exit code */
        return -1;
    return selected;
}
