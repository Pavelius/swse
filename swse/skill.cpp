#include "main.h"

static struct skill_i
{
	const char*			name[2];
	char				class_skills[Soldier + 1];
} skill_data[] = {
	{{"Acrobatic", "����������"}, {1, 0, 1, 0, 0}},
	{{"Climb", "������"}, {0, 0, 0, 1, 1}},
	{{"Deception", "�����"}, {0, 1, 1, 0, 0}},
	{{"Endurance", "������������"}, {1, 0, 0, 1, 1}},
	{{"Gather Information", "��������� ����������"}, {0, 1, 1, 0, 0}},
	{{"Initiative", "����������"}, {1, 1, 1, 1, 1}},
	{{"Jump", "������"}, {1, 0, 0, 1, 1}},
	{{"Buerocracy", "����������"}, {1, 1, 1, 1, 0}},
	{{"Galactic Lore", "������ ���������"}, {1, 1, 1, 1, 0}},
	{{"Life Sciences", "������������� �����"}, {1, 1, 1, 1, 0}},
	{{"Physical Sciences", "���������� �����"}, {1, 1, 1, 1, 0}},
	{{"Social Sciences", "���������� �����"}, {1, 1, 1, 1, 0}},
	{{"Tactics", "�������"}, {1, 1, 1, 1, 1}},
	{{"Technology", "����������"}, {0, 1, 0, 0, 0}},
	{{"Mechanics", "��������"}, {0, 0, 1, 1, 1}},
	{{"Perception", "��������������"}, {1, 1, 1, 1, 1}},
	{{"Persuasion", "���������"}, {0, 1, 1, 0, 0}},
	{{"Pilot", "�����"}, {1, 1, 1, 1, 1}},
	{{"Ride", "���� ������"}, {0, 1, 0, 1, 0}},
	{{"Stealth", "����������"}, {0, 0, 1, 1, 0}},
	{{"Survival", "���������"}, {0, 0, 0, 1, 0}},
	{{"Swim", "��������"}, {0, 0, 0, 1, 1}},
	{{"Treat Injury", "������ �������"}, {0, 1, 0, 0, 1}},
	{{"Use Computer", "������������ ���������"}, {0, 1, 1, 0, 1}},
	{{"Use Force", "������������ ����"}, {1, 0, 0, 0, 0}},
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