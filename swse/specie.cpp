#include "main.h"

static struct specie_i
{
	const char*			name[2];
	char				abilities[6];
	adat<feat_s, 8>		feats;
} specie_data[] = {
	{{"No species", "��� ����"}},
	{{"Human", "�������"}, {0, 0, 0, 0, 0, 0}},
	{{"Bothan", "�����"}, {0, 2, -2, 0, 0, 0}, {1, {IronWill}}},
	{{"Cerean", "������"}, {0, -2, 0, 2, 2, 0}},
	{{"Duros", "�����"}, {0, 2, -2, 2, 0, 0}},
	{{"Ewoks", "����"}, {-2, 2, 0, 0, 0, 0}},
	{{"Gammorean", "����������"}, {2, -2, 0, -2, 0, 0}},
	{{"Gungans", "������"}, {0, 2, 0, -2, 0, -2}},
	{{"Ithorians", "���������"}, {0, -2, 0, 0, 2, 2}},
	{{"KelDor", "�����������"}, {0, 2, -2, 0, 2, 0}},
	{{"Mon Calamari", "��� ���������"}, {0, 0, -2, 2, 2, 0}},
	{{"Quarren", "�������"}, {0, 0, 2, 0, -2, -2}},
	{{"Rodians", "������"}, {0, 2, 0, 0, -2, -2}},
	{{"Sullustans", "�����������"}, {0, 2, -2, 0, 0, 0}},
	{{"Trandoshans", "�����������"}, {2, -2, 0, 0, 0, 0}},
	{{"Twileks", "���\'���"}, {0, 0, 0, -2, 0, 2}},
	{{"Zabrak", "������"}, {0, 0, 0, 0, 0, 0}},
	{{"Wookie", "����"}, {4, -2, 2, 0, -2, -2}},
};

void creature::set(specie_s id, bool value)
{
	type = id;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] += specie_data[id].abilities[i];
}