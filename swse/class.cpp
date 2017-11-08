#include "main.h"

static struct class_i
{
	const char*			name[2];
	char				dice;
	char				skills;
	feata				starting_feats;
} class_data[] = {
	{{"Jedi", "������"}, 10, 2, {3, {ForceSensitivity, WeaponProficiencyLightsabers, WeaponProficiencySimpleWeapons}}},
	{{"Noble", "����������"}, 6, 6, {3, {Linguist, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}}},
	{{"Scoundrel", "�������"}, 6, 4, {3, {PointBlankShoot, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}}},
	{{"Scout", "�����"}, 8, 5, {4, {ShakeItOff, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}}},
	{{"Soldier", "������"}, 10, 3, {5, {ArmourProficienceLight, ArmourProficienceMedium, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}}},
	{{"Non-Hero", "�� �����"}, 6},
	{{"Beast", "������"}, 10},
};
assert_enum(class, Beast);
getstr_enum(class);

void creature::set(class_s id, bool interactive)
{
	classes[id]++;
	for(auto e : class_data[id].starting_feats)
	{
		if(is(e))
			continue;
		set(e);
	}
}

int game::getskillpoints(class_s id)
{
	return class_data[id].skills;
}

feata& getfeats(class_s id)
{
	return class_data[id].starting_feats;
}