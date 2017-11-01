#include "main.h"

int	main(int argc, char *argv[])
{
	auto hero_size = sizeof(hero);
	logs::open("7 sea");
	hero player;
	player.create(false);
	player.set(AttackFencing, 1);
	player.roll(true, Finesse, AttackFencing, 25, 5*1);
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	return main(0, 0);
}