#include "main.h"

int	main(int argc, char *argv[])
{
	logs::open("7 sea");
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	return main(0, 0);
}