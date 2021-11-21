#include "traits.h"

trait::trait(trait_type tt, unsigned int ti):
     time_left(ti), type(tt) { }

trait::trait(std::string line){
    LOG(DEBUG, "creating trait: %s", line.c_str());
    std::vector<std::string> sep = split(line, '|');
    type = traitTypeFromString(sep[0]);
    if(sep.size() > 1){
        time_left = atoi(sep[1].c_str());
    }else{
        time_left = 0;
    }
}

bool trait::decrease(){
    debug_assert(type != TRAIT_INVALID);
    if(time_left == 0) return false;
    time_left --;
    return time_left == 0;
}

trait_type traitTypeFromString(std::string s){
    if(s == "FLY") return TRAIT_FLY;
    if(s == "REACH") return TRAIT_REACH;
    if(s == "HASTE") return TRAIT_HASTE;
    if(s == "FIRST_STRIKE") return TRAIT_FIRST_STRIKE;
    LOG(WARNING, "trait not implemented: %s", s.c_str());
    debug_assert_not_reached();
}

std::string traitTypeAsString(trait_type t){
    if(t == TRAIT_FLY) return std::string("FLY");
    if(t == TRAIT_REACH) return std::string("REACH");
    if(t == TRAIT_HASTE) return std::string("HASTE");
    if(t == TRAIT_FIRST_STRIKE) return std::string("FIRST_STRIKE");
    debug_assert_not_reached();
}
