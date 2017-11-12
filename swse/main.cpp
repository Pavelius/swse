#include "main.h"

int	main(int argc, char *argv[])
{
	auto p1 = getstr(ForceTraining);
	auto p2 = getstr(DoubleAttack);
	logs::open("SW");
	location test;
	creature::create(true, true);
	//game::combat(true);
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