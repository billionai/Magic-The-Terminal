#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__
#include <ncurses.h>
#include <panel.h>

/* What options that were enabled at the time of querying.
   This struct is used to save and set options conveniently. */
#define bit(name) unsigned int name:1
struct terminal_options {
    bit(raw);
    bit(echo);
};

/* Initialization function. Start graphics defines the default
   ncurses screen for this program. They are:
   Noecho - disabling echo makes navigation better to understand
   Raw - disables line buffering
   keypad - simplifies dealing with arrow and function keys
   */
void start_graphics();
/* finishing function. Returns the terminal to the original state */
void finish_graphics(terminal_options);

/* Get the options that are currently being used. Usually used to
   save the current state and reset it afterwards. */
terminal_options get_terminal_options();
#endif /*__GRAPHIC_H__*/
