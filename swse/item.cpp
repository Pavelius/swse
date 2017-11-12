#include "main.h"

static struct item_i
{
	struct weapon
	{
		dice			damage;
		item_s			ammo;
	};
	struct armor
	{
		char			defences[Will+1];
	};
	const char*			name[2];
	const char*			descritpion;
	feat_s				group;
	int					cost;
	int					weight;
	weapon				weapon_stats;
	armor				armor_stats;
} item_data[] = {
	{{"", ""}, ""},
	//
	{{"Vibro Dagger", "�����-������"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Vibro Blade", "�����-���"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Vibro boatan", "�����-����"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Power spear", "������� �����"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Power staff", "�������-�����"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Vibro axe", "�����-�����"}, "", WeaponProficiencyAdvancedMeleeWeapons},
	{{"Atlati", "������"}, "", WeaponProficiencyExoticWeapons},
	{{"Emfy staff", "����-�����"}, "", WeaponProficiencyExoticWeapons},
	{{"Cesta", "�����"}, "", WeaponProficiencyExoticWeapons},
	{{"Light dagger", "�������� ������"}, "", WeaponProficiencyLightsabers},
	{{"Light saber", "�������� ���"}, "", WeaponProficiencyLightsabers},
	{{"Light saber, double", "�������� ���, �������"}, "", WeaponProficiencyLightsabers},
	// ������� ������
	{{"Knife", "���"}, "", WeaponProficiencySimpleWeapons},
	{{"Club", "������"}, "", WeaponProficiencySimpleWeapons},
	{{"Baton", "���������� �����"}, "", WeaponProficiencySimpleWeapons},
	{{"Mace", "������"}, "", WeaponProficiencySimpleWeapons},
	{{"Spear", "�����"}, "", WeaponProficiencySimpleWeapons},
	{{"Boatan", "���� �� ��������"}, "", WeaponProficiencySimpleWeapons},
	{{"Staff", "�����"}, "", WeaponProficiencySimpleWeapons},
	{{"Gauntlets", "��������"}, "", WeaponProficiencySimpleWeapons},
	{{"Gauntlets", "��������"}, "", WeaponProficiencySimpleWeapons},
	// ������������� ������
	{{"Firebat", "�������"}, "", WeaponProficiencyHeavyWeapons},
	{{"Plasmogun", "���������"}, "", WeaponProficiencyHeavyWeapons},
	{{"Granade Launcher", "����������"}, "", WeaponProficiencyHeavyWeapons},
	{{"Blaster Machinegun", "������� �������� �������"}, "", WeaponProficiencyHeavyWeapons},
	{{"Blaster Cannon", "�������� �����"}, "", WeaponProficiencyHeavyWeapons},
	{{"Rocket Launcher", "���������"}, "", WeaponProficiencyHeavyWeapons},
	{{"Blaster Turrel E-web", "�������� ��������� E-Web"}, "", WeaponProficiencyHeavyWeapons},
	{{"Mini Blaster", "����-�������"}, "", WeaponProficiencyPistols},
	{{"Blaster", "�������"}, "", WeaponProficiencyPistols},
	{{"Sport Blaster", "���������� �������"}, "", WeaponProficiencyPistols},
	{{"Ion Blaster", "���������� �������"}, "", WeaponProficiencyPistols},
	{{"Gun", "��������"}, "", WeaponProficiencyPistols},
	{{"Heavy Blaster", "������� �������"}, "", WeaponProficiencyPistols},
	{{"Blaster Shotgun", "�������� �������"}, "", WeaponProficiencyRifles},
	{{"Blaster Rifle", "�������� ��������"}, "", WeaponProficiencyRifles},
	{{"Sport Blaster Rifle", "���������� �������� ��������"}, "", WeaponProficiencyRifles},
	{{"Ion Rifle", "���������� ��������"}, "", WeaponProficiencyRifles},
	{{"Rifle", "��������"}, "", WeaponProficiencyRifles},
	{{"Blaster Minigun", "�������� �������"}, "", WeaponProficiencyRifles},
	{{"Heavy Blaster Rifle", "������� �������� ��������"}, "", WeaponProficiencyRifles},
	{{"Plasma Sphere", "���������� ���"}, "", WeaponProficiencySimpleWeapons},
	{{"Grenade", "���������� �������"}, "", WeaponProficiencySimpleWeapons},
	{{"Grenade, ion", "���������� �������"}, "", WeaponProficiencySimpleWeapons},
	{{"Grenade, shock", "���������� �������"}, "", WeaponProficiencySimpleWeapons},
	{{"Thermal detonator", "���������� ���������"}, "", WeaponProficiencySimpleWeapons},
	{{"Sling", "�����"}, "", WeaponProficiencySimpleWeapons},
	{{"Bow", "���"}, "", WeaponProficiencySimpleWeapons},
	{{"Net", "����"}, "", WeaponProficiencySimpleWeapons},
	// ����������
	{{"Trotil", "����������"}, "", WeaponProficiencySimpleWeapons},
	{{"Detonator", "���������"}, "", WeaponProficiencySimpleWeapons},
	// ������ �����
	{{"Blast helmet and vest", "���� � ������"}, "", ArmourProficienceLight},
	{{"Flight suit", "������ ������"}, "", ArmourProficienceLight},
	{{"Armor, jumping", "����� � ��������� ����������"}, "", ArmourProficienceLight},
	{{"Flight suit, armored", "������ ������, �������������"}, "", ArmourProficienceLight},
	{{"Vondoon crabshell armor", "����������� �������� �����"}, "", ArmourProficienceLight},
	{{"Armor, trooper", "����� ����������"}, "", ArmourProficienceLight},
	// ������� �����
	{{"Ceremonial armour", "�������������� �����"}, "", ArmourProficienceMedium},
	{{"Power suit", "������-�����"}, "", ArmourProficienceMedium},
	{{"Combat armour", "������ �����"}, "", ArmourProficienceMedium},
	// ������� �����
	{{"Space suit, armored", "������������� ����������� ��������"}, "", ArmourProficienceHeavy},
	{{"Combat armor, heavy", "������� ������ �����"}, "", ArmourProficienceHeavy},
	// ����������
	{{"Portable computer", "���������� ���������"}, ""},
	{{"Code cylinder", "�������������� �������"}, ""},
	{{"Credit chip", "��������� ��������"}, ""},
	{{"Holoproject", "������������"}, ""},
	{{"Data card", "������"}, ""},
	{{"Data pad", "��������� ���������"}, ""},
	// ���������� �����������
	{{"Electro binocular", "�������-�������"}, "������� ��������� �������� ���������� � ����������, �������, ������� ��������, � ����� �������� ��������� ������� �������. ��������� ����� ���������� �� -1 �� ������ 10 ���������, ������ -5 �� ������ 10 ���������."},
	{{"Glow rod", "���������� �����"}, "���������� ����������, ������� ���������� �����, ���������� ��� ��������� 6 ���������."},
	{{"Fusion latern", "������� �������"}, "������� ������������ ���� � �����. �������� 6 ��������� �������."},
	{{"Audio-recorder", "��������"}, "������ 100 ����� ����� � �������� ��������."},
	{{"Holo-recorder", "������������"}, "������ 1 ��� ������������ ����������."},
	{{"Video-recorder", "�����������"}, "������ 10 ����� ����� � �������� ��������."},
	{{"Sensor pack", "����������� �����"}, "����������� ������� � ��������, ������������� ���������� � �����������. ��������� ����������� ��������� � �������� 1 ���������� �� ������� ���� �����, �������������, �������� ��� ������ �����."},
	// �����
	{{"Comlink", "�������"}, ""},
	{{"Pocket decipher", "��������� ��������"}, "������� ����������, ������� ����� ���� ���������� � ������������ � ���������� ����������, ����� ��� �������."},
	{{"Voxbox", "��������� ����"}, ""},
};
assert_enum(item, VoxBox);
getstr_enum(item);

int item::getreflexes() const
{
	return 0;
}

const dice& item::getdice() const
{
	return item_data[type].weapon_stats.damage;
}

bool item::ismelee() const
{
	return type <= GlovesMedium;
}

bool item::isweapon() const
{
	if(type == NoItem)
		return false;
	return type <= Net;
}

void item::clear()
{
	type = NoItem;
	count = 0;
}

void item::setcount(int count)
{
	if(!count)
		clear();
	else
	{
		if(count > 256)
			count = 256;
		this->count = count - 1;
	}
}