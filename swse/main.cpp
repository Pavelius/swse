#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("SW");
	location test;
	creature::create(false, true);
	test.create();
	test.acting();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}