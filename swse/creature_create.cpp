#include "main.h"

void creature::chooseclass(bool interactive)
{
	for(auto i = Jedi; i <= Soldier; i = (class_s)(i + 1))
		logs::add(i, getstr(i));
	logs::sort();
	auto result = (class_s)logs::input(interactive, false, "�������� [�����]:");
	set(result);
}

void creature::choosegender(bool interactive)
{
	logs::add(Male, "�������");
	logs::add(Female, "�������");
	logs::sort();
	gender = (gender_s)logs::input(interactive, false, "�������� [���]:");
}

void creature::set(class_s id, bool interactive)
{
}