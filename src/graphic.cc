#include "graphic.h"

terminal_options current_terminal_options = {
    0, /* raw. not set on my terminals. */
    1, /* echo. set on my terminals. */
};

static void set_raw(){
    raw();
    current_terminal_options.raw = 1;
}

static void set_noraw(){
    noraw();
    current_terminal_options.raw = 0;
}

static void set_echo(){
    echo();
    current_terminal_options.echo = 1;
}

static void set_noecho(){
    noecho();
    current_terminal_options.echo = 0;
}

void start_graphics(){
    initscr();
    set_raw();
    set_noecho();
}

void finish_graphics(terminal_options original_opts){
    (original_opts.raw) ? set_raw() : set_noraw();
    (original_opts.echo) ? set_echo() : set_noecho();
    endwin();
}

terminal_options get_terminal_options() {
    return current_terminal_options;
}
