#include "main.h"

static struct skill_i
{
	const char*			name[2];
	char				class_skills[Soldier + 1];
} skill_data[] = {
	{{"Acrobatic", "Акробатика"}, {1, 0, 1, 0, 0}},
	{{"Climb", "Лазить"}, {0, 0, 0, 1, 1}},
	{{"Deception", "Обман"}, {0, 1, 1, 0, 0}},
	{{"Endurance", "Выносливость"}, {1, 0, 0, 1, 1}},
	{{"Gather Information", "Добывание информации"}, {0, 1, 1, 0, 0}},
	{{"Initiative", "Инициатива"}, {1, 1, 1, 1, 1}},
	{{"Jump", "Прыжки"}, {1, 0, 0, 1, 1}},
	{{"Buerocracy", "Бюрократия"}, {1, 1, 1, 1, 0}},
	{{"Galactic Lore", "Знание галактики"}, {1, 1, 1, 1, 0}},
	{{"Life Sciences", "Биологические науки"}, {1, 1, 1, 1, 0}},
	{{"Physical Sciences", "Физические науки"}, {1, 1, 1, 1, 0}},
	{{"Social Sciences", "Социальные науки"}, {1, 1, 1, 1, 0}},
	{{"Tactics", "Тактика"}, {1, 1, 1, 1, 1}},
	{{"Technology", "Технологии"}, {0, 1, 0, 0, 0}},
	{{"Mechanics", "Механика"}, {0, 0, 1, 1, 1}},
	{{"Perception", "Внимательность"}, {1, 1, 1, 1, 1}},
	{{"Persuasion", "Убеждение"}, {0, 1, 1, 0, 0}},
	{{"Pilot", "Пилот"}, {1, 1, 1, 1, 1}},
	{{"Ride", "Езда верхом"}, {0, 1, 0, 1, 0}},
	{{"Stealth", "Скрытность"}, {0, 0, 1, 1, 0}},
	{{"Survival", "Выживание"}, {0, 0, 0, 1, 0}},
	{{"Swim", "Плавание"}, {0, 0, 0, 1, 1}},
	{{"Treat Injury", "Лечить ранения"}, {0, 1, 0, 0, 1}},
	{{"Use Computer", "Использовать компьютер"}, {0, 1, 1, 0, 1}},
	{{"Use Force", "Использовать силу"}, {1, 0, 0, 0, 0}},
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