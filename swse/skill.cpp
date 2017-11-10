#include "main.h"

static struct skill_i
{
	const char*			name[2];
	char				class_skills[Soldier + 1];
	ability_s			ability;
} skill_data[] = {
	{{"Acrobatic", "����������"}, {1, 0, 1, 0, 0}, Dexterity},
	{{"Climb", "������"}, {0, 0, 0, 1, 1}, Strenght},
	{{"Deception", "�����"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Endurance", "������������"}, {1, 0, 0, 1, 1}, Constitution},
	{{"Gather Information", "��������� ����������"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Initiative", "����������"}, {1, 1, 1, 1, 1}, Dexterity},
	{{"Jump", "������"}, {1, 0, 0, 1, 1}, Strenght},
	{{"Buerocracy", "����������"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Galactic Lore", "������ ���������"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Life Sciences", "������������� �����"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Physical Sciences", "���������� �����"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Social Sciences", "���������� �����"}, {1, 1, 1, 1, 0}, Intellegence},
	{{"Tactics", "�������"}, {1, 1, 1, 1, 1}, Intellegence},
	{{"Technology", "����������"}, {0, 1, 0, 0, 0}, Intellegence},
	{{"Mechanics", "��������"}, {0, 0, 1, 1, 1}, Intellegence},
	{{"Perception", "��������������"}, {1, 1, 1, 1, 1}, Wisdow},
	{{"Persuasion", "���������"}, {0, 1, 1, 0, 0}, Charisma},
	{{"Pilot", "�����"}, {1, 1, 1, 1, 1}, Intellegence},
	{{"Ride", "���� ������"}, {0, 1, 0, 1, 0}, Dexterity},
	{{"Stealth", "����������"}, {0, 0, 1, 1, 0}, Dexterity},
	{{"Survival", "���������"}, {0, 0, 0, 1, 0}, Wisdow},
	{{"Swim", "��������"}, {0, 0, 0, 1, 1}, Strenght},
	{{"Treat Injury", "������ �������"}, {0, 1, 0, 0, 1}, Wisdow},
	{{"Use Computer", "������������ ���������"}, {0, 1, 1, 0, 1}, Intellegence},
	{{"Use Force", "������������ ����"}, {1, 0, 0, 0, 0}, Charisma},
};
assert_enum(skill, LastSkill);
getstr_enum(skill);

bool creature::isclass(skill_s id) const
{
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
	{
		if(classes[i] && skill_data[id].class_skills[i])
			return true;
	}
	return false;
}

ability_s game::getability(skill_s id)
{
	return skill_data[id].ability;
}