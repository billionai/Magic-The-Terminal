#include "land.h"

Land::Land(const std::string name,
     const char col,
     std::vector<complexEffect>&& e):
        Card(LAND, name, col),
        effects(std::move(e)) { }

Land make_Land(std::string line, std::unordered_map<std::string, Effect> map){
    std::vector<std::string> params = split(line, ',');
    std::vector<complexEffect> ce_vector;
    debug_assert(params.size() == LAND_PARAMETERS);
    try{
        if(!params[LAND_EFFECTS_INDEX].empty()){
            std::vector<std::string> effect_chains;
            effect_chains = split(params[LAND_EFFECTS_INDEX], '|');
            for(auto single_chain: effect_chains){
                ce_vector.emplace_back(CEfromString(single_chain, map));
            }
        }
    } catch(const std::out_of_range& oor){
        LOG(FAILURE,
            "failed to create card %s, "
            "effects %s were not defined",
            params[LAND_NAME_INDEX].c_str(),
            params[LAND_EFFECTS_INDEX].c_str());
        throw std::invalid_argument(params[LAND_EFFECTS_INDEX]);
    }
    return Land(params[LAND_NAME_INDEX],
                atoi(params[LAND_COLOR_INDEX].c_str()),
                std::move(ce_vector));
}
