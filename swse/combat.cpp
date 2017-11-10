#include "main.h"

static struct action_i
{
	feat_s			feat;
	const char*		text;
	bool			(creature::*test)();
} action_data[] = {
	{WeaponProficiencySimpleWeapons, "��������� �����"},
	{WeaponProficiencyPistols, "�������� �� �����"},
	{BurstFire, "���� �������� �������"},
	{BanthaRush, "� ������ ��������� �� ����� � ����������"},
	{AcrobaticStrike, "������� ������ � ��������� �����"}
};

static int compare_initiative(const void* p1, const void* p2)
{
	return (*((creature**)p2))->initiative
		- (*((creature**)p1))->initiative;
}

static bool iscombat(creaturea& source)
{
	if(!source.count)
		return false;
	auto side = source.data[0]->side;
	for(auto p : source)
	{
		if(!p->isactive())
			continue;
		if(p->side != side)
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
		p->side = PartySide;
		source.add(p);
	}
	auto p = creature::create(false, false);
	p->side = EnemySide;
	source.add(p);
	// 2 - roll initiative
	for(auto p : source)
		p->initiative = p->roll(Initiative, 0, false);
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
