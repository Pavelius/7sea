#include "main.h"

int	main(int argc, char *argv[])
{
	auto hero_size = sizeof(hero);
	logs::open("7 sea");
	hero player;
	player.create(false);
	player.roll(true, 5, 3, 0);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	return main(0, 0);
}