#include "main.h"

static struct specie_i
{
	const char*			name[2];
	char				abilities[6];
} specie_data[] = {
	{{"No species", "Нет расы"}},
	{{"Human", "Человек"}, {}},
	{{"Bothan", "Ботан"}, {}},
	{{"Cerean", "Цереан"}, {}},
	{{"Duros", "Дурос"}, {}},
	{{"Ewoks", "Эвок"}, {}},
	{{"Gammorean", "Гамореанец"}, {}},
	{{"Gungans", "Гунган"}, {}},
	{{"Ithorians", "Иторианец"}, {}},
	{{"KelDor", "Келдорианец"}, {}},
	{{"Mon Calamari", "Мон Каламарец"}, {}},
	{{"Quarren", "Кваррен"}, {}},
	{{"Rodians", "Родиан"}, {}},
	{{"Sullustans", "Суллустанец"}, {}},
	{{"Trandoshans", "Трандошанец"}, {}},
	{{"Twileks", "Тви\'лек"}, {}},
	{{"Zabrak", "Забрак"}, {}},
	{{"Wookie", "Вуки"}, {}},
};
