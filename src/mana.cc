#include <ctype.h> //used for isdigit()
#include "mana.h"

mana::mana(std::string ss){
    //constructs a sorted string with insertion sort
    size_t i;
    for(i=0; i<ss.length() && isdigit(ss[i]); i++){
        s += ss[i];//just adds the numbers
    }
    char order[]={'C', 'W', 'U', 'B', 'R', 'G'};
    for(int o = 0; o < 6; o++) {
        for(size_t j = i+1; j < ss.length(); j++){
            debug_assert(!isdigit(ss[j]));//we can't have leftover digits
            if(ss[j] == order[o]) s += ss[j];
        }
    }
}

bool mana::has_hybrid(){
    return s.find('(') >= 0;
}

bool mana::has_generic(){
    //if this has generic mana, at least the first character mus be a digit
    return isdigit(s[0]);
}

int mana::count_generic(){
    int end = 0;
    while(isdigit(s[end])) end++;
    return atoi(s.substr(0, end).c_str());
}

bool mana::operator >=(mana& m){
    debug_assert(!has_hybrid());
    debug_assert(!has_generic());
    auto itr_a = s.rbegin();
    auto itr_b = m.s.rbegin();
    int generic = m.count_generic();
    //TODO: ADD SUPPORT TO HYBRID MANA
    for(;itr_a != s.crend() && itr_b != m.s.crend() && !isdigit(*itr_b);
         itr_a ++, itr_b ++){
        while((*itr_a != *itr_b) && itr_a != s.crend()){
            itr_a++;
            if(generic) generic--;
        }
    }
    return (generic == 0) && (itr_b == m.s.crend() || isdigit(*itr_b));
}
