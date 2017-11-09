#include "main.h"

static location::scene location_data[] = {
	{3, {"большой ангар", "ангара"}},
};
static struct scenery
{
	morph_s					morph;
	const char*				description[3];
} scenery_data[] = {
	{Feminine, {"лестница, ведущая вниз", "лестнице", "лестницу"}},
	{Neuter, {"множество контейнеров разных размеров", "контейнерам", "контейнеры"}},
	{Neuter, {"несколько столов, на которых стояла компьютерная техника", "столам", "столы"}},
	{Masculine, {"разобранный боевой робот", "остаткам робота", "остатки робота"}},
	{Masculine, {"генераторы силовой установки", "генераторам", "генераторы"}},
};

const char* location::place::getname() const
{
	return type->description[0];
}

const char* location::place::getnameto() const
{
	return type->description[1];
}

void location::clear()
{
	memset(this, 0, sizeof(*this));
}

void location::create()
{
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	places[0].type = scenery_data + (rand() % (sizeof(scenery_data) / sizeof(scenery_data[0])));
	places[1].type = scenery_data + (rand() % (sizeof(scenery_data) / sizeof(scenery_data[0])));
	places[2].type = scenery_data + (rand() % (sizeof(scenery_data) / sizeof(scenery_data[0])));
}

char* look(char* result, const char* format, location* p, short unsigned index)
{
	szprint(result, format, p->type->description[0], p->places[index].getname());
	return zend(result);
}

void location::getdescription(char* result)
{
	szprint(zend(result), "Вы зашли в %1. ", type->description[0]);
	result = look(zend(result), "Прямо возле вас было %2. ", this, 0);
	result = look(zend(result), "Посреди %1 находилась %2. ", this, 1);
	result = look(zend(result), "в дальней части находилось %2. ", this, 2);
}

void location::acting()
{
	bool interactive = true;
	auto position = 0;
	while(true)
	{
		getdescription(logs::getptr());
		logs::add(1, "Всем двигаться к %1.", places[0].getname());
		auto id = logs::input(interactive, true, "Что будете делать?");
	}
}