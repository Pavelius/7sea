#include "main.h"

enum result_aciton_s {
	KeepResult, UseDramaDice,
};

static int fatedice;

static int compare_dices(const void* p1, const void* p2)
{
	return *((char*)p2) - *((char*)p1);
}

static char rolldice(bool explode)
{
	auto result = (rand() % 10) + 1;
	if(explode && result==10)
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

static int rolldices(char* result, int roll, int keep, int bonus, bool explode)
{
	memset(result, 0, 10 * sizeof(result[0]));
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
	// Too small dice count
	if(roll == 0)
	{
		result[0] = rand() % 10;
		result[1] = 0;
		return result[0];
	}
	// Roll dices
	for(int i = 0; i < roll; i++)
		result[i] = rolldice(explode);
	qsort(result, roll, sizeof(result[0]), compare_dices);
	// Get total result
	for(int i = 0; i<keep; i++)
		bonus += result[i];
	return bonus;
}

static char* add_result(char* result, int keep, char* dices)
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

static char* print_result(char* p, char* dices, int keep, int value, int bonus)
{
	zcpy(p, "Результат: ");
	add_result(zend(p), keep, dices);
	zcat(p, ". ");
	szprint(zend(p), "В сумме [%1i]. ", value);
	return p;
}

static char* print_result(char* p, char* dices, int keep, int value, int bonus, hero* player, trait_s trait, knack_s knack, int tn)
{
	szprint(p, "%1 бросает [%2]+[%3] против сложности [%4i]. ", player->getname(), getstr(trait), getstr(knack), tn);
	auto pp = print_result(zend(p), dices, keep, value, bonus);
	return p;
}

void hero::clear()
{
	memset(this, 0, sizeof(*this));
}

void hero::endsession()
{
	experience += dramadice;
	dramadice = traits[0];
	for(auto i = FirstTrait; i <= LastTrait; i = (trait_s)(i + 1))
	{
		if(dramadice > traits[i])
			dramadice = traits[i];
	}
}

void hero::usedrama()
{
	if(dramadice)
	{
		dramadice--;
		fatedice++;
	}
}

bool hero::roll(bool interactive, trait_s trait, knack_s knack, int target_number, int roll_bonus, int keep_bonus, int bonus, int* return_result)
{
	char temp[512];
	char dices[10];
	char roll_result;
	auto k = get(trait);
	auto r = k + get(knack);
	auto result = rolldices(dices, r, k, bonus, !iscripled());
	if(!interactive)
		return result>=target_number;
	while(true)
	{
		if(result>=target_number)
			logs::add(KeepResult, "Принять [+удачный] результат");
		else
			logs::add(KeepResult, "Принять [-не удачный] результат");
		if(dramadice)
			logs::add(UseDramaDice, "Использовать кубик драмы (осталось [%1i])", dramadice);
		auto id = (result_aciton_s)logs::input(true, true, print_result(temp, dices, k, result, bonus, this, trait, knack, target_number));
		switch(id)
		{
		case KeepResult:
			if(return_result)
				*return_result = result;
			return result>=target_number;
		case UseDramaDice:
			usedrama();
			roll_result = rolldice(true);
			result += roll_result;
			dices[0] += roll_result;
			break;
		}
	}
}