#include "main.h"

static struct specie_i
{
	const char*			name[2];
	char				abilities[6];
	feata				starting_feats;
	char				bonus_skills, bonus_feats;
} specie_data[] = {
	{{"No species", "��� ����"}},
	{{"Human", "�������"}, {0, 0, 0, 0, 0, 0}, {}, 1, 1},
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
assert_enum(specie, Wookie);
getstr_enum(specie);

void creature::set(specie_s id)
{
	specie = id;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] += specie_data[id].abilities[i];
	for(auto e : specie_data[id].starting_feats)
	{
		if(is(e))
			continue;
		set(e);
	}
}

int	creature::getskills() const
{
	auto result = 0;
	for(auto e = Jedi; e <= Soldier; e = (class_s)(e + 1))
	{
		if(!get(e))
			continue;
		result += game::getskillpoints(e);
	}
	result += getbonus(Intellegence);
	result += specie_data[specie].bonus_skills;
	return result;
}