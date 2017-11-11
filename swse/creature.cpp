#include "main.h"

adat<creature, 512>	creatures;
creature*			players[6];

bool creature::is(feat_s id) const
{
	return (feats[id / 8] & (1 << (id % 8))) != 0;
}

void creature::set(feat_s id, bool interactive)
{
	feats[id / 8] |= (1 << (id % 8));
//	feats[id / 8] &= ~(1 << (id % 8));
}

void creature::remove(feat_s id)
{
	feats[id / 8] &= ~(1 << (id % 8));
}

int creature::getbonus(ability_s id) const
{
	return abilities[id] / 2 - 5;
}

void creature::set(gender_s id)
{
	gender = id;
}

int	creature::get(feat_s id) const
{
	auto result = getheroiclevel() / 2;
	if(is(id))
		result += 5;
	result += getbonus(game::getability(id));
	return result;
}

int	creature::get(defence_s id) const
{
	auto result = 10;
	switch(id)
	{
	case Reflexes:
		if(wears[Armor])
			result += wears[Armor].getreflexes();
		else
			result += getheroiclevel();
		result += getbonus(Dexterity);
		break;
	case Fortitude:
		result += getheroiclevel();
		result += getbonus(Constitution);
		break;
	case Will:
		result += getheroiclevel();
		result += getbonus(Wisdow);
		break;
	}
	return result;
}

int	creature::roll(feat_s id, int dc, bool interactive) const
{
	return roll(get(id), dc, interactive, 0);
}

int	creature::roll(int bonus, int dc, bool interactive, int* dice_rolled) const
{
	auto result = d20();
	auto outcome = result + bonus - dc;
	if(interactive)
	{
		if(outcome >= 0)
			logs::add("[+{%1i%+2i=%3i}] ", result, bonus, result + bonus);
		else
			logs::add("[-{%1i%+2i=%3i}] ", result, bonus, result + bonus);
	}
	if(dice_rolled)
		*dice_rolled = result;
	return outcome;
}

void creature::damage(int count, bool interactive)
{
	if(count < hits)
	{
		hits -= count;
		if(interactive)
			logs::add("%1 получил%2 %3i повреждений.", getname(), getA(), count);
	}
	else
	{
		hits -= count;
		if(interactive)
			logs::add("%1 получил%2 %3i повреждений и упал%2.", getname(), getA(), count);
	}
}

void creature::attack(wear_s id, creature* enemy, bool interactive)
{
	attackinfo e;
	if(!getattackinfo(id, e))
		return;
	int dice_rolled;
	int defence = enemy->get(Reflexes);
	int rolled = roll(e.bonus, 0, interactive, &dice_rolled);
	if(rolled >= defence || rolled >= e.critical_range)
	{
		auto damage_count = e.damage.roll();
		if(rolled >= e.critical_range)
		{
			if(interactive)
				logs::add("%1 критически попал%2.", getname(), getA());
			for(int i = 1; i < e.critical_multiply; i++)
				damage_count += e.damage.roll(e.damage.c, e.damage.d);
		}
		else
		{
			if(interactive)
				logs::add("%1 попал%2.", getname(), getA());
		}
		enemy->damage(damage_count, interactive);
	}
	else
	{
		if(interactive)
			logs::add("%1 промазал%2.", getname(), getA());
	}
}

int	creature::getheroiclevel() const
{
	return classes[Jedi]
		+ classes[Noble]
		+ classes[Scoundrel]
		+ classes[Scout]
		+ classes[Soldier];
}

int	creature::getbaseattack() const
{
	return classes[Jedi] + classes[Soldier] + (classes[Noble] + classes[Scoundrel] + classes[Scout]) * 3 / 4;
}

bool creature::isactive() const
{
	return hits >= 0;
}

bool creature::getattackinfo(wear_s id, attackinfo& e) const
{
	memset(&e, 0, sizeof(e));
	e.critical_range = 20;
	e.critical_multiply = 2;
	if(wears[id])
		e.damage = wears[id].getdice();
	e.bonus = getbaseattack();
	e.damage.b += getheroiclevel() / 2;
	switch(id)
	{
	case MeleeWeapon:
		e.bonus += getbonus(Strenght);
		e.damage.b += getbonus(Strenght);
		break;
	case RangedWeapon:
		e.bonus += getbonus(Dexterity);
		break;
	}
	return true;
}

void creature::getenemies(creaturea& result, const creaturea& source) const
{
	result.initialize();
	for(auto e : source)
	{
		if(!e->isactive())
			continue;
		if(e->side == side)
			continue;
		result.add(e);
	}
}

void creature::set(side_s value)
{
	side = value;
}

void creature::rollinitiative()
{
	initiative = roll(Initiative, 0, false);
}