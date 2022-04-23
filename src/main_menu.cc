#include <vector>
#include <string>
#include <fstream>

#include "utils.h"
#include "main_menu.h"

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

main_menu_info::main_menu_info()
    : menu() {
    int x, y, starty, startx;
    std::vector<std::string> lines = read_logo_file();
    std::vector<std::string> options = {
        "start game",
        "explore database",
        "exit"
    };
    std::string simple_logo = "MAGIC The Terminal";

    /* Starting the separated screens with logo.  Only start the logo window if
       there is enough space for it, otherwise store NULL as the window.  */
    getmaxyx(stdscr, y, x);
    has_logo = (y > NUM_LINES_LOGO + options.size());
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
        starty = NUM_LINES_LOGO;
    }else{
        starty = 0;
        windows[0] = NULL;
        panels[0] = NULL;
    }
    /* Start the window for the menu itself */
    windows[1] = newwin(y - starty, x, starty, 0);
    panels[1] = new_panel(windows[1]);
    box(windows[1],0,0);
    keypad(windows[1], true);

    menu.startup(windows[1], options);

    update_panels();
    doupdate();
}

main_menu_info::~main_menu_info(){
    if(windows[0]){
        del_panel(panels[0]);
        delwin(windows[0]);
    }
    del_panel(panels[1]);
    delwin(windows[1]);
}

void main_menu_info::move_menu(int key){
    menu.move_menu(key);
}

int main_menu_info::select_item(){
    return menu.select_item();
}

int main_menu_info::get_input(){
    /* get an input from the input's window, so that it won't refresh stdscr */
    return wgetch(windows[1]);
}
