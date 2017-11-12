#include "main.h"

static struct class_i
{
	const char*			name[2];
	char				dice;
	char				skills;
	feata				starting_feats;
} class_data[] = {
	{{"Jedi", "Джедай"}, 10, 2, {3, {ForceSensitivity, WeaponProficiencyLightsabers, WeaponProficiencySimpleWeapons}}},
	{{"Noble", "Аристократ"}, 6, 6, {3, {Linguist, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}}},
	{{"Scoundrel", "Негодяй"}, 6, 4, {3, {PointBlankShoot, WeaponProficiencyPistols, WeaponProficiencySimpleWeapons}}},
	{{"Scout", "Скаут"}, 8, 5, {4, {ShakeItOff, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}}},
	{{"Soldier", "Солдат"}, 10, 3, {5, {ArmourProficienceLight, ArmourProficienceMedium, WeaponProficiencyPistols, WeaponProficiencyRifles, WeaponProficiencySimpleWeapons}}},
	{{"Non-Hero", "Не герой"}, 6},
	{{"Beast", "Бестия"}, 10},
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

feata& game::getfeats(class_s id)
{
	return class_data[id].starting_feats;
}

int game::getdice(class_s id)
{
	return class_data[id].dice;
}