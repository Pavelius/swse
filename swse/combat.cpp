#include "main.h"

static struct action_i
{
	feat_s			feat;
	const char*		text;
	bool			(creature::*condition)();
	bool			(creature::*targetable)();
} action_data[] = {
	{BurstFire, "Дать короткую очередь"},
	{BanthaRush, "С криком броситься на врага в рукопашную"},
	{AcrobaticStrike, "Сделать пирует и атаковать врага"}
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

void creature::combatactions(creaturea& enemies, bool interactive)
{
	for(unsigned i=0; i<lenghtof(action_data); i++)
	{
		if(!is(action_data[i].feat))
			continue;
		logs::add(i, action_data[i].text);
	}
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

