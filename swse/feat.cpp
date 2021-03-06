#include "main.h"

struct prerequisit_i
{
	adat<feat_s, 8>			feats;
	char					abilities[Charisma+1];
	char					base_attack_bonus;
};
static struct feat_i
{
	const char*				name[2];
	talent_s				tree;
	prerequisit_i			require;
} feat_data[] = {
	{{"", ""}},
	//
	{{"Adept negotiator"}, JediConsular},
	{{"Force persuasion"}, JediConsular, {{1, {AdeptNegotiator}}}},
	{{"Master negotiator"}, JediConsular, {{1, {AdeptNegotiator}}}},
	{{"Skilled advisor"}, JediConsular},
	{{"Acrobatic recovery"}, JediGuardian},
	{{"Battle Meditation"}, JediGuardian},
	{{"Elusive Target"}, JediGuardian},
	{{"Force Intuition"}, JediGuardian},
	{{"Resilience"}, JediGuardian},
	{{"Clear Mind"}, JediSentinel},
	{{"Dark Side Sence"}, JediSentinel},
	{{"Dark Side Scourge"}, JediSentinel, {{1, {DarkSideSence}}}},
	{{"Force Haze"}, JediSentinel},
	{{"Resist Dark Side"}, JediSentinel, {{1, {DarkSideSence}}}},
	{{"Block"}, LightsaberCombat},
	{{"Deflect"}, LightsaberCombat},
	{{"Lightsaber Defence"}, LightsaberCombat},
	{{"Lightsaber Defence II"}, LightsaberCombat, {{1, {LightsaberDefence}}}},
	{{"Lightsaber Defence III"}, LightsaberCombat, {{1, {LightsaberDefenceII}}}},
	{{"Weapon Specialization (Lightsaber)"}, LightsaberCombat},
	{{"Lightsaber Throw"}, LightsaberCombat},
	{{"Redirect Shot"}, LightsaberCombat, {{1, {Deflect}}, {}, 5}},
	//
	{{"Presence"}, Influence},
	{{"Demand Surrender"}, Influence, {{1, {Presence}}}},
	{{"Improved Weaken Resolve"}, Influence, {{2, {Presence, WeakenResolve}}}},
	{{"Weaken Resolve"}, Influence, {{1, {Presence}}}},
	{{"Bolster Ally"}, Inspiration},
	{{"Ignite Ferver"}, Inspiration, {{2, {BolsterAlly, InspireConfidence}}}},
	{{"Inspire Confidence"}, Inspiration},
	{{"Inspire Haste"}, Inspiration},
	{{"Inspire Zeal"}, Inspiration, {{3, {BolsterAlly, InspireConfidence, IgniteFerver}}}},
	{{"Born Leader"}, Leadership},
	{{"Coordinate"}, Leadership},
	{{"Distant Command"}, Leadership},
	{{"Fearless Leader"}, Leadership},
	{{"Rally"}, Leadership},
	{{"Trust"}, Leadership},
	{{"Connections"}, Lineage},
	{{"Educated"}, Lineage},
	{{"Spontaneous Skill"}, Lineage, {{1, {Educated}}}},
	{{"Wealth"}, Lineage},
	//
	{{"Acrobatic Strike", "������������� ����"}, General, {{1, {Acrobatic}}}},
	{{"Armour Proficience Light", "������� ������ �����"}, General},
	{{"Armour Proficience Medium", "������� ������� �����"}, General, {{1, {ArmourProficienceLight}}}},
	{{"Armour Proficience Heavy", "������� ������� �����"}, General, {{2, {ArmourProficienceLight, ArmourProficienceMedium}}}},
	{{"Bantha Rush", "������"}, General, {{0}, {13}, 1}},
	{{"Burst Fire", "�������� ��������� ���������"}, General, {{1, {WeaponProficiencyHeavyWeapons}}, {13}, 1}},
	{{"Careful Shoot", "���������� ��������"}, General, {{1, {PointBlankShoot}}, {}, 2}},
	{{"Charging Fire", "�������� ��� ���������"}, General},
	{{"Cleave", "����������"}, General},
	{{"Combat Reflexes", "������ ��������"}, General},
	{{"Coordinated Attack", "����������������� �����"}, General},
	{{"Crush", "��������"}, General},
	{{"Cybernetic Surgery", "��������������� ��������������"}, General},
	{{"Deadeye", "������� ����"}, General},
	{{"Dodge", "���������"}, General},
	{{"Double Attack", "������� �����"}, General},
	{{"Dreadful Rage", "������� ���������"}, General},
	{{"Dual weapon Mastery", "�������� ����� ��������"}, General},
	{{"Extra Rage", "�������������� ���������"}, General},
	{{"Extra Second Wind", "�������������� ������ �������"}, General},
	{{"Far Shoot", "������� �������"}, General},
	{{"Force Boon", "��������������� ����"}, General},
	{{"Force Sensitivity", "������� ����"}, General},
	{{"Force Training", "�������� ����"}, General},
	{{"Improved Charge", "���������� ���������"}, General},
	{{"Improved Defences", "���������� ������"}, General},
	{{"Improved Disarm", "���������� ��������������"}, General},
	{{"Improved Damage Threshold", "���������� ������������� �����"}, General},
	{{"Linguist", "��������"}, General},
	{{"Martial Arts", "���������� ���"}, General},
	{{"Martial Arts II", "���������� ��� II"}, General},
	{{"Martial Arts III", "���������� ��� III"}, General},
	{{"Melee Defence", "������ � ������� ���"}, General},
	{{"Mighty Swing", "������ ������"}, General},
	{{"Mobility", "�����������"}, General},
	{{"Pin", "������"}, General},
	{{"Point-blank Shoot", "������� ���������"}, General},
	{{"Power Attack", "������ �����"}, General},
	{{"Powerful Charge", "������ ���������"}, General},
	{{"Precise Shoot", "���������� �������"}, General},
	{{"Quick Draw", "������� ������������ ������"}, General},
	{{"Rapid Shoot", "���������� �������"}, General},
	{{"Rapid Strike", "���������� ����"}, General},
	{{"Running Attack", "����� �� ����"}, General},
	{{"Shake it off", "�������� �� �����"}, General},
	{{"Sniper", "�������"}, General},
	{{"Skill focus (Acrobatic)", "����� �� ����������"}, General},
	{{"Skill focus (Climb)", "����� �� �������"}, General},
	{{"Skill focus (Deception)", "����� �� ������"}, General},
	{{"Skill focus (Endurance)", "����� �� ������������"}, General},
	{{"Skill focus (Gather Information)", "����� �� ��������� ����������"}, General},
	{{"Skill focus (Initiative)", "����� �� ����������"}, General},
	{{"Skill focus (Jump)", "����� �� �������"}, General},
	{{"Skill focus (Buerocracy)", "����� �� ����������"}, General},
	{{"Skill focus (Galactic Lore)", "����� �� ������� ���������"}, General},
	{{"Skill focus (Life Sciences)", "����� �� ����� ������"}, General},
	{{"Skill focus (Physical Sciences)", "����� �� ���������� ������"}, General},
	{{"Skill focus (Social Sciences)", "����� �� ���������� ������"}, General},
	{{"Skill focus (Tactics)", "����� �� �������"}, General},
	{{"Skill focus (Technology)", "����� �� �����������"}, General},
	{{"Skill focus (Mechanics)", "����� �� ��������"}, General},
	{{"Skill focus (Perception)", "����� �� ����������"}, General},
	{{"Skill focus (Persuasion)", "����� �� ���������"}, General},
	{{"Skill focus (Pilot)", "����� �� �������������"}, General},
	{{"Skill focus (Ride)", "����� �� ���� ������"}, General},
	{{"Skill focus (Stealth)", "����� �� ����������"}, General},
	{{"Skill focus (Survival)", "����� �� ���������"}, General},
	{{"Skill focus (Swim)", "����� �� ��������"}, General},
	{{"Skill focus (Treat Injury)", "����� �� �������� �������"}, General},
	{{"Skill focus (Use Computer)", "����� �� ������������� ����������"}, General},
	{{"Skill focus (Use Force)", "����� �� ������������� ����"}, General},
	{{"Strong in the Force", "��������� � ����"}, General},
	{{"Surgical Expertise", "������������� �������"}, General},
	{{"Throw", "������"}, General},
	{{"Toughness", "���������"}, General},
	{{"Trip", "��������"}, General},
	{{"Triple attack", "������� �����"}, General},
	{{"Triple critical", "������� �����������"}, General},
	{{"Vehicular combat", "��� �� ����������"}, General},
	{{"Weapon finess", "����������"}, General},
	{{"Weapon proficiency (Advanced Melee Weapons)", "�������� ���������� ������� �������� ���"}, General},
	{{"Weapon proficiency (Exotic Weapons)", "�������� ������������ �������"}, General},
	{{"Weapon proficiency (Heavy Weapons)", "�������� ������� �������"}, General},
	{{"Weapon proficiency (Lightsabers)", "�������� �������� �����"}, General},
	{{"Weapon proficiency (Pistols)", "�������� �����������"}, General},
	{{"Weapon proficiency (Rifles)", "�������� ����������"}, General},
	{{"Weapon proficiency (Simple Weapons)", "�������� ������� �������"}, General},
	{{"Weapon focus (Advanced Melee Weapons)", "����� �� ���������� ������ �������� ���"}, General, {{1, {WeaponProficiencyAdvancedMeleeWeapons}}}},
	{{"Weapon focus (Exotic Weapons)", "����� �� ������������ ������"}, General, {{1, {WeaponProficiencyExoticWeapons}}}},
	{{"Weapon focus (Heavy Weapons)", "����� �� ������� ����������"}, General, {{1, {WeaponProficiencyHeavyWeapons}}}},
	{{"Weapon focus (Lightsabers)", "����� �� �������� ����"}, General, {{1, {WeaponProficiencyLightsabers}}}},
	{{"Weapon focus (Pistols)", "����� �� ����������"}, General, {{1, {WeaponProficiencyPistols}}}},
	{{"Weapon focus (Rifles)", "����� �� ���������"}, General, {{1, {WeaponProficiencyRifles}}}},
	{{"Weapon focus (Simple Weapons)", "����� �� ������� ������"}, General, {{1, {WeaponProficiencySimpleWeapons}}}},
	{{"Whirlwind attack", "����� ������"}, General},
	//
	{{"Acrobatic", "����������"}, Skills},
	{{"Climb", "������"}, Skills},
	{{"Deception", "�����"}, Skills},
	{{"Endurance", "������������"}, Skills},
	{{"Gather Information", "��������� ����������"}, Skills},
	{{"Initiative", "����������"}, Skills},
	{{"Jump", "������"}, Skills},
	{{"Buerocracy", "����������"}, Skills},
	{{"Galactic Lore", "������ ���������"}, Skills},
	{{"Life Sciences", "������������� �����"}, Skills},
	{{"Physical Sciences", "���������� �����"}, Skills},
	{{"Social Sciences", "���������� �����"}, Skills},
	{{"Tactics", "�������"}, Skills},
	{{"Technology", "����������"}, Skills},
	{{"Mechanics", "��������"}, Skills},
	{{"Perception", "��������������"}, Skills},
	{{"Persuasion", "���������"}, Skills},
	{{"Pilot", "�����"}, Skills},
	{{"Ride", "���� ������"}, Skills},
	{{"Stealth", "����������"}, Skills},
	{{"Survival", "���������"}, Skills},
	{{"Swim", "��������"}, Skills},
	{{"Treat Injury", "������ �������"}, Skills},
	{{"Use Computer", "������������ ���������"}, Skills},
	{{"Use Force", "������������ ����"}, Skills},
	//
	{{"Bonus Trained Skill", "�������������� �����"}, RacialFeat},
	{{"Bonus Feat", "�������������� �����������"}, RacialFeat},
	{{"Primitive", "�����������"}, RacialFeat},
	{{"Lowlight Vision", "������������� ������"}, RacialFeat},
	{{"Darkvision", "�����������"}, RacialFeat},
	{{"Expert Swimmer", "���������� ������"}, RacialFeat},
	{{"Expert Pilot", "���������� �����"}, RacialFeat},
	{{"Expert Climber", "������ �������"}, RacialFeat},
	{{"Sneaky", "��������"}, RacialFeat},
	{{"Survival Instinct", "�������� ���������"}, RacialFeat},
	{{"Intuitive Initiative", "����������� ����������"}, RacialFeat},
	{{"Keen Force Sence", "������ ������� ����"}, RacialFeat},
	{{"Heighten Awareness", "���������� ���������������"}, RacialFeat},
	{{"Deceptive", "���������� ����"}, RacialFeat},
	{{"Extraordinary Recuperation", "���������� ������������ ���"}, RacialFeat},
	{{"Hold Breath", "�������� �������"}, RacialFeat},
	{{"Breath Underwater", "����� ��� �����"}, RacialFeat},
	{{"Bellow", "���"}, RacialFeat},
	{{"Limb Regeneration", "����������� �����������"}, RacialFeat},
	{{"Natural Armour", "����������� �����"}, RacialFeat},
	{{"Iron Will", "�������� ����"}, RacialFeat},
	{{"Great Fortitude", "�������� ���������"}, RacialFeat},
	{{"Lighting Reflexes", "������������ ��������"}, RacialFeat},
	{{"Superior Defences", "������������ ������"}, RacialFeat},
	{{"Rage", "���������"}, RacialFeat},
	{{"Scent", "���"}, RacialFeat},
};
assert_enum(feat, Scent);
getstr_enum(feat);

bool creature::isallow(feat_s id) const
{
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
	{
		if(feat_data[id].require.abilities[i]
			&& abilities[i] < feat_data[id].require.abilities[i])
			return false;
	}
	for(auto e : feat_data[id].require.feats)
	{
		if(!is(e))
			return false;
	}
	return true;
}

unsigned creature::select(feat_s* result, unsigned result_count, talent_s talent) const
{
	auto p = result;
	auto pe = p + result_count;
	for(auto i = FirstFeat; i <= LastFeat; i = (feat_s)(i + 1))
	{
		if(feat_data[i].tree != talent)
			continue;
		if(is(i))
			continue;
		if(!isallow(i))
			continue;
		if(p < pe)
			*p++ = i;
		else
			break;
	}
	return p - result;
}