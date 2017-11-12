#include "main.h"

static struct name_i
{
	specie_s		race;
	gender_s		gender;
	const char*		name;
} name_data[] = {
	{Human, Male, "������"},
	{Human, Male, "�����"},
	{Human, Male, "����"},
	{Human, Male, "���"},
	{Human, Male, "����"},
	{Human, Male, "����"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Male, "������"},
	{Human, Male, "���"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Male, "����"},
	{Human, Male, "���"},
	{Human, Male, "������"},
	{Human, Male, "����"},
	{Human, Male, "�����"},
	{Human, Male, "���"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Male, "������"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Male, "�����"},
	{Human, Male, "����"},
	{Human, Male, "������"},
	{Human, Female, "���"},
	{Human, Female, "����"},
	{Human, Female, "�����"},
};

static unsigned select(short unsigned* result, unsigned count, name_i* source, unsigned source_count, gender_s gender, specie_s* race)
{
	auto p = result;
	auto pe = p + count;
	for(unsigned i = 0; i < source_count; i++)
	{
		if(gender != source[i].gender)
			continue;
		if(race && *race!= source[i].race)
			continue;
		if(p < pe)
			*p++ = (short unsigned)i;
		else
			break;
	}
	return p - result;
}

short unsigned game::getrandomname(specie_s race, gender_s gender)
{
	short unsigned result[128];
	auto count = select(result, lenghtof(result), name_data, lenghtof(name_data), gender, &race);
	if(count)
		return result[rand() % count];
	count = select(result, lenghtof(result), name_data, lenghtof(name_data), gender, 0);
	if(count)
		return result[rand() % count];
	return 0;
}

const char* game::getname(short unsigned id)
{
	return name_data[id].name;
}