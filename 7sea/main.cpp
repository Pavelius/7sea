#include "main.h"

int	main(int argc, char *argv[])
{
	auto hero_size = sizeof(hero);
	logs::open("7 sea");
	hero player, enemy;
	auto ptr = logs::getptr();
	player.create(false);
	player.set(AttackFencing, 1);
	enemy.create(false);
	game::combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}