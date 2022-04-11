#include <vector>
#include <string>
#include <fstream>

#include "utils.h"
#include "main_menu.h"

/* how many options does the main menu have. */
#define NUM_OPTIONS 0
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
    update_panels();
    doupdate();
}

int handle_main_menu(){
    main_menu_info info;
    getch();
    return 0;
}
