#include "main.h"

static struct class_i
{
	const char*			name[2];
	char				dice;
} class_data[] = {
	{{"Jedi", "������"}, 10},
	{{"Noble", "����������"}},
	{{"Scoundrel", "�������"}},
	{{"Scout", "�����"}, 10},
	{{"Soldier", "������"}, 10},
	{{"Non-Hero", "�� �����"}},
	{{"Beast", "������"}},
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