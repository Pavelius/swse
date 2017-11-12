#include "main.h"

adat<creature, 512>	creatures;
creature*			players[6];

bool creature::is(feat_s id) const
{
	return (feats[id / 8] & (1 << (id % 8))) != 0;
}

bool creature::is(action_s id) const
{
	return (actions & (1 << id)) == 0;
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

void creature::set(action_s id)
{
	actions |= (1 << id);
}

void creature::setready()
{
	actions = 0;
	reflex_bonus = 0;
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
	static char reflex_size_bonus[] = {10, 5, 2, 1, 0, -1, -2, -5, -10};
	static_assert(lenghtof(reflex_size_bonus) == SizeCollosal + 1, "Invalid count of size elements");
	auto result = 10;
	switch(id)
	{
	case Reflexes:
		if(armor)
			result += armor.getreflexes();
		else
			result += getheroiclevel();
		if(is(NaturalArmor))
			result += 1;
		result += reflex_bonus;
		result += getbonus(Dexterity);
		result += reflex_size_bonus[getsize()];
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
	if(is(SuperiorDefences))
		result++;
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
	if(count < 0)
		count = 1;
	if(count < hits)
	{
		hits -= count;
		if(interactive)
			logs::add("%1 �������%2 %3i �����������.", getname(), getA(), count);
	}
	else
	{
		hits -= count;
		if(interactive)
			logs::add("%1 �������%2 %3i ����������� � ����%2.", getname(), getA(), count);
	}
}

void creature::attack(creature* enemy, bool interactive, int bonus)
{
	attackinfo e; getattackinfo(e);
	e.bonus += bonus;
	int dice_rolled;
	int defence = enemy->get(Reflexes);
	int rolled = roll(e.bonus, defence, interactive, &dice_rolled);
	if(rolled >= 0 || dice_rolled >= e.critical_range)
	{
		auto damage_count = e.damage.roll();
		if(dice_rolled >= e.critical_range)
		{
			if(interactive)
				logs::add("%1 ���������� �����%2.", getname(), getA());
			for(int i = 1; i < e.critical_multiply; i++)
				damage_count += e.damage.roll(e.damage.c, e.damage.d);
		}
		else
		{
			if(interactive)
				logs::add("%1 �����%2.", getname(), getA());
		}
		enemy->damage(damage_count, interactive);
	}
	else
	{
		if(interactive)
			logs::add("%1 ��������%2.", getname(), getA());
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

void creature::getattackinfo(attackinfo& e) const
{
	static unsigned char unarmed_dice[] = {1, 1, 2, 3, 4, 6, 8, 10, 12, 20};
	memset(&e, 0, sizeof(e));
	e.critical_range = 20;
	e.critical_multiply = 2;
	if(weapon)
		e.damage = weapon.getdice();
	else
	{
		int d = getsize();
		if(is(MartialArts))
			d++;
		e.damage.c = 1;
		e.damage.d = unarmed_dice[d];
	}
	e.bonus = getbaseattack();
	e.damage.b += getheroiclevel() / 2;
	if(weapon.ismelee())
	{
		e.bonus += getbonus(Strenght);
		e.damage.b += getbonus(Strenght);
	}
	else
		e.bonus += getbonus(Dexterity);
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

bool creature::isenemy(const creature* e) const
{
	return getside() != e->getside();
}

bool creature::isreachenemy(const creature* e) const
{
	if(!isenemy(e))
		return false;
	return iabs(position - e->position) <= getreach();
}

bool creature::isallow(action_s id) const
{
	switch(id)
	{
	case SwiftAction:
		return is(StandartAction) || is(MoveAction) || is(SwiftAction);
	case MoveAction:
		return is(StandartAction) || is(MoveAction);
	case FullRoundAction:
		return is(StandartAction) && is(MoveAction) && is(SwiftAction);
	default:
		return is(id);
	}
}

action_s creature::getaction(combat_action_s id) const
{
	switch(id)
	{
	case Move:
		return MoveAction;
	case DrawWeapon:
		if(is(QuickDraw))
			return SwiftAction;
		return MoveAction;
	default:
		return StandartAction;
	}
}

void creature::use(action_s id)
{
	switch(id)
	{
	case FullRoundAction:
		set(StandartAction);
		set(SwiftAction);
		set(MoveAction);
		break;
	case MoveAction:
		if(is(MoveAction))
			set(MoveAction);
		else
			set(StandartAction);
		break;
	case SwiftAction:
		if(is(SwiftAction))
			set(SwiftAction);
		else if(is(MoveAction))
			set(MoveAction);
		else
			set(StandartAction);
		break;
	case StandartAction:
		set(StandartAction);
		break;
	case Reaction:
		set(Reaction);
		break;
	}
}

void creature::set(state_s id, bool interactive)
{
	if(this->state == LayingDown && id == StandAndReady)
	{
		this->state = StandAndReady;
		if(is(Acrobatic))
		{
			if(roll(Acrobatic, 15, interactive) >= 0)
			{
				if(interactive)
					logs::add("%1 ����� �������%� �� ����.", getname(), getA());
				use(SwiftAction);
				return;
			}
		}
		if(interactive)
			logs::add("%1 ������%��� �� ����.", getname(), getAS());
		use(MoveAction);
	}
}

bool creature::isgearweapon() const
{
	for(auto e : gears)
	{
		if(e.isweapon())
			return true;
	}
	return false;
}

const char*	creature::getname() const
{
	return game::getname(name);
}