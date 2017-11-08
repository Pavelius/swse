#include "main.h"

static struct specie_i
{
	const char*			name[2];
	char				abilities[6];
	adat<feat_s, 8>		feats;
} specie_data[] = {
	{{"No species", "Нет расы"}},
	{{"Human", "Человек"}, {0, 0, 0, 0, 0, 0}},
	{{"Bothan", "Ботан"}, {0, 2, -2, 0, 0, 0}, {1, {IronWill}}},
	{{"Cerean", "Цереан"}, {0, -2, 0, 2, 2, 0}},
	{{"Duros", "Дурос"}, {0, 2, -2, 2, 0, 0}},
	{{"Ewoks", "Эвок"}, {-2, 2, 0, 0, 0, 0}},
	{{"Gammorean", "Гамореанец"}, {2, -2, 0, -2, 0, 0}},
	{{"Gungans", "Гунган"}, {0, 2, 0, -2, 0, -2}},
	{{"Ithorians", "Иторианец"}, {0, -2, 0, 0, 2, 2}},
	{{"KelDor", "Келдорианец"}, {0, 2, -2, 0, 2, 0}},
	{{"Mon Calamari", "Мон Каламарец"}, {0, 0, -2, 2, 2, 0}},
	{{"Quarren", "Кваррен"}, {0, 0, 2, 0, -2, -2}},
	{{"Rodians", "Родиан"}, {0, 2, 0, 0, -2, -2}},
	{{"Sullustans", "Суллустанец"}, {0, 2, -2, 0, 0, 0}},
	{{"Trandoshans", "Трандошанец"}, {2, -2, 0, 0, 0, 0}},
	{{"Twileks", "Тви\'лек"}, {0, 0, 0, -2, 0, 2}},
	{{"Zabrak", "Забрак"}, {0, 0, 0, 0, 0, 0}},
	{{"Wookie", "Вуки"}, {4, -2, 2, 0, -2, -2}},
};

void creature::set(specie_s id, bool value)
{
	type = id;
	for(auto i = Strenght; i <= Charisma; i = (ability_s)(i + 1))
		abilities[i] += specie_data[id].abilities[i];
}