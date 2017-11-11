#include "main.h"

static struct action_i
{
	feat_s			feat;
	wear_s			weapon;
	const char*		text;
	bool			(creature::*t0)() const;
	bool			(creature::*t1)(const creature*) const;
	bool			(creature::*t2)(const creature*) const;

	bool match(const creature* player, const creature* opponent) const
	{
		if(t1 && !(player->*t1)(opponent))
			return false;
		if(t2 && !(player->*t2)(opponent))
			return false;
		return true;
	}

	bool match(const creature* player, creaturea& combatants) const
	{
		for(auto p : combatants)
		{
			if(!p->isactive())
				continue;
			if(match(player, p))
				return true;
		}
		return false;
	}

} action_data[] = {
	{BurstFire, RangedWeapon, "Дать короткую очередь в одну цель", 0, &creature::isenemy},
	{BanthaRush, MeleeWeapon, "С криком броситься на врага в рукопашную"},
	{AcrobaticStrike, MeleeWeapon, "Сделать пирует и атаковать врага"},
	{ChargingFire, RangedWeapon, "С криком броситься на врага, стреляя в него на бегу"},
	{NoFeat, MeleeWeapon, "Нанести удар противнику"},
	{NoFeat, RangedWeapon, "Стрельнуть по противнику"}
};

static int compare_initiative(const void* p1, const void* p2)
{
	return (*((creature**)p2))->getinitiative()
		- (*((creature**)p1))->getinitiative();
}

static bool iscombat(creaturea& source)
{
	if(!source.count)
		return false;
	auto side = source.data[0]->getside();
	for(auto p : source)
	{
		if(!p->isactive())
			continue;
		if(p->getside() != side)
			return true;
	}
	return false;
}

static creature* getmelee(creaturea& enemies)
{
	return enemies.data[0];
}

static bool test(creature* player, creaturea& enemies, creature::testing t1)
{
	for(auto p : enemies)
	{
		if(t1 && !(player->*t1)(p))
			continue;
	}
	return false;
}

void creature::combatactions(creaturea& enemies, bool interactive)
{
	for(unsigned i=0; i<lenghtof(action_data); i++)
	{
		if(action_data[i].feat && !is(action_data[i].feat))
			continue;
		if(!action_data[i].match(this, enemies))
			continue;
		logs::add(i, action_data[i].text);
	}
	auto id = logs::input(interactive, false, "Что будет делать [%1]?", getname());
}

void game::combat(bool interactive)
{
	creaturea source; source.initialize();
	// 1 - select combatants
	for(auto p : players)
	{
		if(!p)
			continue;
		p->set(PartySide);
		source.add(p);
	}
	auto p = creature::create(false, false);
	p->set(EnemySide);
	source.add(p);
	// 2 - roll initiative
	for(auto p : source)
		p->rollinitiative();
	qsort(source.data, source.count, sizeof(source.data[0]), compare_initiative);
	// 3 - run combat
	while(iscombat(source))
	{
		for(auto p : source)
		{
			if(!p->isactive())
				continue;
			creaturea enemies;
			p->getenemies(enemies, source);
			if(!enemies)
				continue;
			p->combatactions(enemies, interactive);
		}
	}
}

