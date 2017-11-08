#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("SW");
	creature::create(true, true);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}