#include "main.h"

static adat<creature, 256> creatures;

static void print_ability(unsigned char* ability)
{
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
	{
		if(i != Strenght)
			logs::add(", ");
		logs::add("%1 %2i", getstr(i), ability[i]);
	}
}

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

void creature::chooseclass(bool interactive)
{
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	auto result = (class_s)logs::input(interactive, false, "Выбрайте [класс]:");
	set(result);
}

void creature::choosegender(bool interactive)
{
	logs::add(Male, "Мужчина");
	logs::add(Female, "Женщина");
	logs::sort();
	gender = (gender_s)logs::input(interactive, false, "Выбрайте [пол]:");
}

static int compare_result(const void* v1, const void* v2)
{
	return *((char*)v2) - *((char*)v1);
}

void creature::chooseskill(bool interactive, int count)
{
	while(count > 0)
	{
		for(auto i = FirstSkill; i <= LastSkill; i = (skill_s)(i + 1))
		{
			if(is(i))
				continue;
			if(!isclass(i))
				continue;
			logs::add(i, getstr(i));
		};
		logs::sort();
		auto result = (skill_s)logs::input(interactive, true, "Выбирайте навык (осталось [%1i])", count--);
		set(result);
	}
}

void creature::chooseabilities(bool interactive)
{
	char temp[6];
	memset(abilities, 0, sizeof(abilities));
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		temp[i] = (rand() % 6) + (rand() % 6) + (rand() % 6) + 3;
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
	auto p = creatures.add();
	p->choosegender(interactive);
	p->chooseclass(interactive);
	p->chooseabilities(interactive);
	auto sp = p->getbonus(Intellegence);
	p->chooseskill(interactive, sp);
	return p;
}