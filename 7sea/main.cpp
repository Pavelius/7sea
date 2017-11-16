#include "main.h"

int	main(int argc, char *argv[])
{
	auto hero_size = sizeof(hero);
	logs::open("7 sea");
	hero party[2];
	party[0].create(Castille, false, true);
	party[0].set(AttackFencing, 2);
	party[1].create(Avalon, false, true);
	party[1].set(AttackHeavyWeapon, 1);
	hero::combat();
	return 0;
}

int _stdcall WinMain(void* ci, void* pi, char* cmd, int sw)
{
	srand((unsigned)time(0));
	//srand(120);
	return main(0, 0);
}