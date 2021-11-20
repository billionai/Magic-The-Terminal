#include "effects.h"

Effect::Effect(std::string nam, bool man, int tr, int c, int res, int tar, mana cst, int N):
    name(nam), mandatory(man), trigger(tr), cost(c), result(res), target(tar),mana_cost(cst),n(N)
    { }

effectTrigger stringToEffectTrigger(std::string s){
    if(s == "ANYTIME") return TRIGGER_ANYTIME;
    if(s == "SORCERY_LIKE") return TRIGGER_SORCERY_LIKE;
    if(s == "ENTER_FIELD") return TRIGGER_ENTER_FIELD;
    if(s == "OTHER_ENTER_FIELD") return TRIGGER_OTHER_ENTER_FIELD;
    if(s == "ATTACK") return TRIGGER_ATTACK;
    if(s == "GET_ATTACKED") return TRIGGER_GET_ATTACKED;
    if(s == "RECEIVE_TOKEN") return TRIGGER_RECEIVE_TOKEN;
    return TRIGGER_INVALID;
}

effectCost stringToEffectCost(std::string s){
    if(s == "FREE") return EFFECT_COST_FREE;
    if(s == "TAP") return EFFECT_COST_TAP;
    if(s == "PAY_MANA") return EFFECT_COST_PAY_MANA;
    if(s == "SACRIFICE_CARD") return EFFECT_COST_SACRIFICE_CARD;
    return EFFECT_COST_INVALID;
}

effectResult stringToEffectResult(std::string s){
    if(s == "GENERATE_MANA") return RESULT_GENERATE_MANA;
    if(s == "TAP_TARGET") return RESULT_TAP_TARGET;
    if(s == "DEAL_DAMAGE") return RESULT_DEAL_DAMAGE;
    if(s == "ADD_COUNTER") return RESULT_ADD_COUNTER;
    return RESULT_INVALID;
}

effectTargetType stringToEffectTargetType(std::string s){
    if(s == "SELF") return TARGET_SELF;
    if(s == "CHOOSE_ANY_PERMANENT") return TARGET_CHOOSE_ANY_PERMANENT;
    if(s == "CHOOSE_OPPONENT_PERMANENT") return TARGET_CHOOSE_OPPONENT_PERMANENT;
    if(s == "CHOOSE_OPPONENT_LAND") return TARGET_CHOOSE_OPPONENT_LAND;
    if(s == "CHOOSE_OWN_PERMANENT") return TARGET_CHOOSE_OWN_PERMANENT;
    if(s == "CHOOSE_OWN_LAND") return TARGET_CHOOSE_OWN_LAND;
    return TARGET_INVALID;
}

Effect make_effect(std::string line){
    std::vector<std::string> params = split(line, ',');
    std::string name = params[0];
    bool mandatory = (params[1][0] == '1');
    std::vector<std::string> triggers = split(params[2],'|');
    std::vector<std::string> costs = split(params[3],'|');
    std::vector<std::string> results = split(params[4],'|');
    std::vector<std::string> targets = split(params[5],'|');
    mana m(params[6]);
    int n = atoi(params[7].c_str());
    int tr, c, res, tar;
    tr = c = res = tar = 0;
    for (auto itr: triggers){
        effectTrigger t = stringToEffectTrigger(itr);
        debug_assert(t != TRIGGER_INVALID);
        debug_assert(!CHECK_BIT(tr, t));
        ADD_BIT(tr, t);
    }
    for(auto itr: costs){
        effectCost cost = stringToEffectCost(itr);
        debug_assert(cost != EFFECT_COST_INVALID);
        debug_assert(!CHECK_BIT(c,cost));
        ADD_BIT(c, cost);
    }
    for(auto itr: results){
        effectResult result = stringToEffectResult(itr);
        debug_assert(result != RESULT_INVALID);
        debug_assert(!CHECK_BIT(res,result));
        ADD_BIT(res, result);
    }
    for(auto itr: targets){
        effectTargetType target = stringToEffectTargetType(itr);
        debug_assert(target != TARGET_INVALID);
        debug_assert(!CHECK_BIT(tar,target));
        ADD_BIT(tar, target);
    }
    return Effect(name, mandatory, tr, c, res, tar, m, n);
}
