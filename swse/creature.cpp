#include "main.h"

adat<creature, 512>	creatures;

bool creature::is(feat_s id) const
{
	return (feats[id / 8] & (1 << (id % 8)))!=0;
}

void creature::set(feat_s id, bool value)
{
	if(value)
		feats[id / 8] |= (1 << (id % 8));
	else
		feats[id / 8] &= ~(1 << (id % 8));
}

bool creature::is(skill_s id) const
{
	return (skills[id / 8] & (1 << (id % 8))) != 0;
}

void creature::set(skill_s id, bool value)
{
	if(value)
		skills[id / 8] |= (1 << (id % 8));
	else
		skills[id / 8] &= ~(1 << (id % 8));
}

int creature::getbonus(ability_s id) const
{
	return abilities[id] / 2 - 5;
}

void creature::set(gender_s id)
{
	gender = id;
}