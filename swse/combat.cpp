#include "main.h"

static struct combat_action_i
{
	combat_action_s	action;
	const char*		text;
	bool			(creature::*self)() const;
	bool			(creature::*opponent)(const creature* e) const;
} combat_action_data[] = {
	{Attack, "������� ���� ����������", &creature::ismelee, &creature::isreachenemy},
	{Attack, "�������� �� ����������", &creature::isrange, &creature::isenemy},
	{FightDefensively, "������� ���� ���������� �� �������� ������", &creature::ismelee, &creature::isreachenemy},
	{Charge, "� ������� ��������� �� �����", 0, &creature::isenemy},
	{Disarm, "���������� ����������� �����", 0, &creature::isreachenemy},
	{Grab, "�������� ���������", 0, &creature::isreachenemy},
	{Move, "��������� � ������� �����", 0},
	{DrawWeapon, "������� ������", &creature::isgearweapon},
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

static unsigned select(creature** result, unsigned count, const creature* player, creaturea& combatants, bool (creature::*proc)(const creature* p) const)
{
	auto pa = result;
	auto pb = pa + count;
	for(auto p : combatants)
	{
		if(!p->isactive())
			continue;
		if(!(player->*proc)(p))
			continue;
		if(pa < pb)
			*pa++ = p;
		else
			break;
	}
	return pa - result;
}

static bool match(creature* player, creaturea& combatants, bool (creature::*proc)(const creature* p) const)
{
	creature* result[1];
	return select(result, lenghtof(result), player, combatants, proc)!=0;
}

static creature* choose(creature* player, creaturea& combatants, bool (creature::*proc)(const creature* p) const, bool intaractive)
{
	creaturea result;
	result.count = select(result.data, lenghtof(result.data), player, combatants, proc);
	if(!result.count)
		return 0;
	else if(result.count == 1)
		return result.data[0];
	for(unsigned i = 0; i < result.count; i++)
		logs::add(i, result.data[i]->getname());
	return result.data[logs::input(intaractive, false, "��� ����� �����?")];
}

void creature::combatactions(creaturea& combatants, bool interactive)
{
	while(is(StandartAction))
	{
		for(auto i = 0; i < lenghtof(combat_action_data); i++)
		{
			auto& a = combat_action_data[i];
			auto action = getaction(a.action);
			if(!isallow(action))
				continue;
			if(a.self && !(this->*a.self)())
				continue;
			if(a.opponent && !match(this, combatants, a.opponent))
				continue;
			logs::add(i, a.text);
		}
		if(!logs::getcount())
			return;
		auto& a = combat_action_data[logs::input(interactive, false, "\n��� ����� ������ [%1]?", getname())];
		creature* opponent = 0;
		if(a.opponent)
			opponent = choose(this, combatants, a.opponent, interactive);
		if(interactive)
			logs::add("\n");
		auto action = getaction(a.action);
		use(action);
		switch(a.action)
		{
		case Attack:
			attack(opponent, interactive);
			break;
		case StandUp:
			set(StandAndReady);
			break;
		}
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
			p->setready();
			p->combatactions(source, interactive);
		}
	}
	logs::next();
}

