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

static char* print_creatures(char* result, creature** source, unsigned source_count)
{
	if(source_count == 0)
		return result;

	return zend(result);
}

void location::getdescription(char* result, creature** source, unsigned source_index)
{
	szprint(zend(result), "Вы зашли в %1. ", type->description[0]);
	result = look(zend(result), "Прямо возле вас было %2. ", this, 0);
	result = look(zend(result), "Посреди %1 находилась %2. ", this, 1);
	result = look(zend(result), "в дальней части находилось %2. ", this, 2);
}

static unsigned select(creature** result, unsigned count, creature** source, unsigned source_count, location* parent, char index)
{
	auto p = result;
	auto pe = result + count;
	for(unsigned i = 0; i<source_count; i++)
	{
		if(!source[i])
			continue;
		if(source[i]->location != parent)
			continue;
		if(index!=-1 && source[i]->index != index)
			continue;
		if(p<pe)
			*p++ = source[i];
	}
	return p - result;
}

static unsigned select(creature** result, unsigned count, location* parent)
{
	auto p = result;
	auto pe = result + count;
	for(auto& e : creatures)
	{
		if(!e)
			continue;
		if(e.location != parent)
			continue;
		if(p<pe)
			*p++ = &e;
	}
	return p - result;
}

void location::acting()
{
	creature* source[64];
	unsigned source_count = select(source, sizeof(source) / sizeof(source[0]), this);
	bool interactive = true;
	auto position = 0;
	while(true)
	{
		getdescription(logs::getptr(), source, source_count);
		logs::add(1, "Всем двигаться к %1.", places[0].getname());
		auto id = logs::input(interactive, true, "Что будете делать?");
	}
}