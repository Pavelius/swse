#include "main.h"

static struct class_i
{
	const char*			name[2];
	char				dice;
} class_data[] = {
	{{"Jedi", "Джедай"}, 10},
	{{"Noble", "Аристократ"}},
	{{"Scoundrel", "Негодяй"}},
	{{"Scout", "Скаут"}, 10},
	{{"Soldier", "Солдат"}, 10},
	{{"Non-Hero", "Не герой"}},
	{{"Beast", "Бестия"}},
};
assert_enum(class, Beast);
getstr_enum(class);

void creature::set(class_s id, bool interactive)
{
	classes[id]++;
}

int creature::getskillpoints() const
{

}