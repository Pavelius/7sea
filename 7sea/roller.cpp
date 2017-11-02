#include "main.h"

roller::roller()
{
	memset(this, 0, sizeof(*this));
}

static int compare_dices(const void* p1, const void* p2)
{
	return *((char*)p2) - *((char*)p1);
}

static char rolldice(bool explode)
{
	auto result = (rand() % 10) + 1;
	if(explode && result == 10)
	{
		while(true)
		{
			auto r = (rand() % 10) + 1;
			result += r;
			if(result > 100)
				return 100;
			if(r != 10)
				break;
		}
	}
	return result;
}

void roller::rolldices()
{
	memset(dices, 0, sizeof(dices));
	if(roll < 0)
		roll = 0;
	// Roll dices more than 10
	if(roll > 10)
	{
		keep += roll - 10;
		roll = 10;
	}
	// Keep dices more than 10
	if(keep > 10)
	{
		bonus += (keep - 10) * 10;
		keep = 10;
	}
	// Keep dices correct
	if(roll < keep)
		roll = keep;
	result = bonus;
	if(roll == 0)
	{
		// Too small dice count
		dices[0] = rand() % 10;
		dices[1] = 0;
		result += dices[0];
	}
	else
	{
		// Roll dices
		for(int i = 0; i < roll; i++)
			dices[i] = rolldice(explose);
		qsort(dices, roll, sizeof(dices[0]), compare_dices);
		// Get total result
		for(int i = 0; i<keep; i++)
			result += dices[i];
	}
}