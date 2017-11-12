#include "main.h"

static void print_rolled(char* result, const char* title, char* values, bool show_names = false)
{
	auto p = result;
	auto pb = p;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
	{
		if(values[i] == 0)
			continue;
		if(p == result)
		{
			zcat(p, title);
			zcat(p, ": ");
			p = zend(p);
			pb = p;
		}
		if(pb != p)
		{
			zcat(p, ", ");
			p = zend(p);
		}
		if(show_names)
			szprint(p, "%1 %2i", getstr(i), values[i]);
		else
			sznum(p, values[i]);
		p = zend(result);
	}
	if(p!=result)
		zcat(p, ".");
}

static void print_skills(char* result, const char* title, creature* player)
{
	auto p = result;
	auto pb = p;
	for(auto i = FirstSkill; i <= LastSkill; i = (feat_s)(i + 1))
	{
		if(player->is(i))
			continue;
		if(p == result)
		{
			zcat(p, title);
			zcat(p, ": ");
			p = zend(p);
			pb = p;
		}
		if(pb != p)
		{
			zcat(p, ", ");
			p = zend(p);
		}
		szprint(p, "%1", getstr(i));
		p = zend(result);
	}
	if(p != result)
		zcat(p, ".");
}

class_s creature::chooseclass(bool interactive)
{
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	return (class_s)logs::input(interactive, false, "Выбрайте [класс]:");
}

specie_s creature::choosespecie(bool interactive)
{
	for(auto i = Human; i <= Wookie; i = (specie_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	return (specie_s)logs::input(interactive, false, "Выбрайте [расу]:");
}

gender_s creature::choosegender(bool interactive)
{
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	return (gender_s)logs::input(interactive, false, "Выбрайте [пол]:");
}

static int compare_result(const void* v1, const void* v2)
{
	return *((char*)v2) - *((char*)v1);
}

void creature::chooseskill(bool interactive, int count)
{
	while(count > 0)
	{
		for(auto i = FirstSkill; i <= LastSkill; i = (feat_s)(i + 1))
		{
			if(is(i))
				continue;
			if(!isclass(i))
				continue;
			logs::add(i, getstr(i));
		};
		logs::sort();
		auto result = (feat_s)logs::input(interactive, true, "Выбирайте навык (осталось [%1i])", count--);
		set(result);
	}
}

static char roll_4d6()
{
	char temp[4];
	for(auto& e : temp)
		e = (rand() % 6) + 1;
	qsort(temp, sizeof(temp) / sizeof(temp[0]), sizeof(temp[0]), compare_result);
	return temp[0] + temp[1] + temp[2];
}

void creature::chooseabilities(bool interactive)
{
	char temp[6];
	memset(abilities, 0, sizeof(abilities));
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		temp[i] = roll_4d6();
	qsort(temp, sizeof(temp) / sizeof(temp[0]), sizeof(temp[0]), compare_result);
	while(temp[0])
	{
		logs::add("\n"); print_rolled(logs::getptr(), "Вы выбросили", temp, false);
		logs::add("\n"); print_rolled(logs::getptr(), "Вы распределили", abilities, true);
		for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		{
			if(abilities[i])
				continue;
			logs::add(i, getstr(i));
		};
		auto result = (ability_s)logs::input(interactive, true, "Куда вы хотите поставить [%1i]?", temp[0]);
		abilities[result] = temp[0];
		memcpy(temp, temp + 1, 5); temp[5] = 0;
	}
}

creature* creature::create(bool interactive, bool setplayer)
{
	auto p2 = choosespecie(interactive);
	auto p1 = choosegender(interactive);
	auto p3 = chooseclass(interactive);
	return create(p2, p1, p3,
		interactive,
		setplayer);
}

creature* creature::create(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer)
{
	auto p = creatures.add();
	p->chooseabilities(interactive);
	p->gender = gender;
	p->set(specie);
	p->set(cls);
	p->chooseskill(interactive, p->getskills());
	if(p->getheroiclevel())
		p->hits = game::getdice(cls) * 3;
	p->name = game::getrandomname(specie, gender);
	if(setplayer)
		zcat(players, p);
	return p;
}