#ifndef _COUNTER_H
#define _COUNTER_H

#include "utils.h"
#include <ctype.h>

struct modifier{
    int atk;
    int def;
    modifier(int a=0, int d=0):atk(a),def(d) { }
};

enum counter_type{
    COUNTER_TYPE_INVALID,
    MODIFIER,
    POISON,
};

class counter{
private:
    counter_type type;
    struct modifier mod;
    bool is_counter; /* < if abilities that rely on counter amounts should count this counter */
    unsigned int amnt; /* < how many of these counters it has */
public:
    counter(int a, int d, counter_type ct = MODIFIER,
            bool c = false, unsigned int count = 1):
        type(ct),mod(a,d),
        is_counter(c),amnt(count) { }
    counter(std::string line):type(COUNTER_TYPE_INVALID){
        set_counter(line);
    }
    counter(): type(COUNTER_TYPE_INVALID) { }

    void set_counter(std::string line){
        debug_assert(type == COUNTER_TYPE_INVALID);
        /* The syntax for making a counter is:
         * 1. if it has uppercase letters, it is a counter of
         *    type equal to the uppercase word
         * 2. if not, it is a +x/+y modifier, and thus:
         *   2.1 a p indicates +
         *   2.2 an m indicates -
         *   2.3 the numbers are separated by '/'
         * 3. it may be seaparted by another '/', and if there
         *    is a 'c' as the first character, is_counter
         *    is true
         * 4. maybe separated by another '/', it indicates how
         *    many counter are put
         */
        is_counter = false;
        amnt = 1;
        mod.atk = 0;
        mod.def = 0;
        if(isupper(line[0])){
            LOG(FAILURE, "this has not been implemented yet",1);
            debug_assert_not_reached();
        }else{
            std::vector<std::string> sp = split(line, '/');
            if(sp.size() >= 3){
                is_counter = (sp[2][0] == 'c');
                if(sp.size() == 4){
                    amnt = sizeof(sp[4].c_str());
                }
            }
            mod.atk = (sp[0][0] == 'm')?
                        - atoi(sp[0].substr(1).c_str()):
                          atoi(sp[0].substr(1).c_str());
            mod.def = (sp[1][0] == 'm')?
                        - atoi(sp[1].substr(1).c_str()):
                          atoi(sp[1].substr(1).c_str());
        }
    }

    unsigned int increment(){
        return ++amnt;
    }

    unsigned int decrement(){
        return --amnt;
    }

    bool counts(){
        return is_counter;
    }

    struct modifier get_mod(){
        debug_assert(type == MODIFIER);
        return mod;
    }

    counter_type get_type(){
        return type;
    }
};

#endif/*_COUNTER_H*/
