#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <unordered_map>

#include "effects.h"
#include "card.h"

void start_cards();

void start_effects();

const std::unordered_map<std::string, Effect>& get_effect_database();
const std::unordered_map<std::string, Card>& get_card_database();

#endif /* __DATABASE_H__ */
