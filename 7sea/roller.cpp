#include "main.h"

enum result_aciton_s {
	KeepResult, UseDramaDice,
};

static int compare_dices(const void* p1, const void* p2)
{
	return *((int*)p2) - *((int*)p1);
}

static char* add_result(char* result, int keep, const int* dices)
{
	for(int i = 0; i < 10; i++)
	{
		if(!dices[i])
			break;
		if(i)
			zcat(result, ", ");
		bool grayed = (i >= keep);
		if(grayed)
			zcat(result, "[~");
		sznum(zend(result), dices[i]);
		if(grayed)
			zcat(result, "]");
	}
	return zend(result);
}

static char* print_result(char* p, const int* dices, int keep, int value, int bonus)
{
	zcpy(p, "Результат: ");
	add_result(zend(p), keep, dices);
	zcat(p, ". ");
	szprint(zend(p), "В сумме [%1i]. ", value);
	return p;
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

roller::roller()
{
	memset(this, 0, sizeof(*this));
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
	if(keep > roll)
		keep = roll;
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

char* roller::getheader(char* temp) const
{
	temp[0] = 0;
	if(player)
		szprint(zend(temp), "%1 бросает", player->getname());
	else
		zcat(temp, "Бросьте");
	switch(type)
	{
	case TraitRoll:
		szprint(zend(temp), " [%1]", getstr(trait));
		break;
	case TraitAndKnackRoll:
		szprint(zend(temp), " [%1] + [%2]", getstr(trait), getstr(knack));
		break;
	}
	if(target_number)
		szprint(zend(temp), " против сложности [%1i]", target_number);
	zcat(temp, ". ");
	auto pp = print_result(zend(temp), dices, keep, result, bonus);
	return temp;
}

void roller::usedrama()
{
	if(!player)
		return;
	player->usedrama();
	auto r = rolldice(true);
	result += r;
	dices[0] += r;
}

bool roller::standart(bool interactive)
{
	char temp[512];
	if(!interactive)
		return result >= target_number;
	while(true)
	{
		if(result >= target_number)
			logs::add(KeepResult, "Принять [+удачный] результат");
		else
			logs::add(KeepResult, "Принять [-не удачный] результат");
		if(player->getdrama())
			logs::add(UseDramaDice, "Использовать кубик драмы (осталось [%1i])", player->getdrama());
		auto id = (result_aciton_s)logs::input(true, true, getheader(temp));
		switch(id)
		{
		case KeepResult:
			return result >= target_number;
		case UseDramaDice:
			usedrama();
			break;
		}
	}
}