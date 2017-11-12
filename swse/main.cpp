#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("SW");
	location test;
	creature::create(Human, Male, Soldier, false, true);
	game::combat(true);
	test.create();
	test.acting();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	//1srand((unsigned)time(0));
	srand(120);
	return main(0, 0);
}