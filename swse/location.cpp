#include "main.h"

static location::scene location_data[] = {
	{3, {"������� �����", "������"}},
};
static struct scenery
{
	morph_s					morph;
	const char*				description[3];
} scenery_data[] = {
	{Feminine, {"��������, ������� ����", "��������", "��������"}},
	{Neuter, {"��������� ����������� ������ ��������", "�����������", "����������"}},
	{Neuter, {"��������� ������, �� ������� ������ ������������ �������", "������", "�����"}},
	{Masculine, {"����������� ������ �����", "�������� ������", "������� ������"}},
	{Masculine, {"���������� ������� ���������", "�����������", "����������"}},
	{Masculine, {"��� � ��������", "����", "���"}},
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

static unsigned select(scenery** result, unsigned count)
{
	auto p = result;
	auto pe = result + count;
	for(auto& e : scenery_data)
	{
		if(p < pe)
			*p++ = &e;
	}
	return p - result;
}

void location::create()
{
	scenery* source[32];
	auto source_count = select(source, lenghtof(source)); zshuffle(source, source_count);
	clear();
	type = location_data + (rand() % (sizeof(location_data) / sizeof(location_data[0])));
	places[0].type = source[0];
	places[1].type = source[1];
	places[2].type = source[2];
}

static void show_figure(char* result, creature* p)
{
	szprint(result, "����� �����%1 %2.", p->getA(), p->getname());
}

char* look(char* result, const char* format, creature** source, unsigned source_count, location* p, char index)
{
	//creature* figures[32];
	//auto figures_count = select(figures, sizeof(figures) / sizeof(figures[0]), source, source_count, p, index);
	szprint(result, format, p->type->description[0], p->places[index].getname());
	return zend(result);
}

void location::getdescription(char* result, creature** source, unsigned source_count)
{
	szprint(zend(result), "�� ����� � %1. ", type->description[0]);
	result = look(zend(result), "����� ����� ��� ���� %2. ", source, source_count, this, 0);
	result = look(zend(result), "������� %1 ���������� %2. ", source, source_count, this, 1);
	result = look(zend(result), "� ������� ����� ���������� %2. ", source, source_count, this, 2);
}

void location::acting()
{
	bool interactive = true;
	auto position = 0;
	while(true)
	{
		getdescription(logs::getptr(), 0, 0);
		logs::add(1, "���� ��������� � %1.", places[0].getname());
		auto id = logs::input(interactive, true, "��� ������ ������?");
	}
}