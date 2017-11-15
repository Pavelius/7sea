#include "main.h"

enum result_aciton_s {
	KeepResult, UseDramaDice,
};

static const char*	text_dramatic_wounds[] = {"драмматических ранение", "драмматическое ранение", "драмматических раны", "драмматических раны", "драмматических раны", "драмматических ран"};
static int			viledice;
hero*				players[6];

static int compare_dices(const void* p1, const void* p2)
{
	return *((int*)p2) - *((int*)p1);
}

static char* add_result(char* result, const int* dices, int keep)
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

static char* add_result(char* p, const int* dices, int keep, int result)
{
	zcpy(p, "Результат: ");
	p = add_result(zend(p), dices, keep);
	zcat(p, ". ");
	szprint(zend(p), "В сумме [%1i]. ", result);
	return zend(p);
}

static int rolldice(bool explode)
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

static int totaldices(int* dices, int keep, int bonus)
{
	for(int i = 0; i < keep; i++)
		bonus += dices[i];
	return bonus;
}

static int rolldices(int* dices, int& roll, int& keep, int& bonus, bool explose)
{
	memset(dices, 0, sizeof(int) * 32);
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
	if(roll == 0)
	{
		// Too small dice count
		dices[0] = rand() % 10;
		dices[1] = 0;
		return dices[0] + bonus;
	}
	else
	{
		// Roll dices
		for(int i = 0; i < roll; i++)
			dices[i] = rolldice(explose);
		qsort(dices, roll, sizeof(dices[0]), compare_dices);
		return totaldices(dices, keep, bonus);
	}
}

void hero::clear()
{
	memset(this, 0, sizeof(*this));
}

void hero::endsession()
{
	experience += dices[DramaDice];
	dices[DramaDice] = traits[0];
	for(auto i = FirstTrait; i <= LastTrait; i = (trait_s)(i + 1))
	{
		if(dices[DramaDice] > traits[i])
			dices[DramaDice] = traits[i];
	}
}

int hero::get(dice_s id) const
{
	switch(id)
	{
	case DramaDice:
		if(isplayer())
			return dices[DramaDice];
		else
			return viledice;
		break;
	default:
		return dices[DramaDice];
	}
}

void hero::use(dice_s id)
{
	switch(id)
	{
	case DramaDice:
		if(isplayer())
		{
			if(dices[DramaDice])
			{
				dices[DramaDice]--;
				viledice++;
			}
		}
		else
			viledice--;
		break;
	}
}

char* hero::sayroll(char* temp, trait_s trait, knack_s knack, int target_number) const
{
	temp[0] = 0;
	szprint(temp, "%1 бросает", getname());
	if(knack == NoKnack)
		szprint(zend(temp), " [%1]", getstr(trait));
	else
		szprint(zend(temp), " [%1] + [%2]", getstr(trait), getstr(knack));
	if(target_number)
		szprint(zend(temp), " против [%1i]", target_number);
	zcat(temp, ". ");
	return temp;
}

int hero::use(int* dices, dice_s id)
{
	use(id);
	auto r = rolldice(true);
	dices[0] += r;
	return r;
}

int hero::roll(int roll, int keep)
{
	int dices[32];
	auto bonus = 0;
	return rolldices(dices, roll, keep, bonus, true);
}

bool hero::roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus, int* return_result)
{
	int dices[32];
	auto keep = get(trait);
	auto roll = keep + get(knack);
	auto result = rolldices(dices, roll, keep, bonus, true);
	if(interactive)
	{
		auto content = logs::getptr();
		while(interactive)
		{
			logs::add("\n");
			sayroll(zend(content), trait, knack, target_number);
			add_result(zend(content), dices, keep, result);
			if(result >= target_number)
				logs::add(KeepResult, "Принять [+удачный] результат");
			else
				logs::add(KeepResult, "Принять [-не удачный] результат");
			if(get(DramaDice))
				logs::add(UseDramaDice, "Использовать кубик драмы (осталось [%1i])", get(DramaDice));
			auto id = (result_aciton_s)logs::input(true, false);
			content[0] = 0;
			switch(id)
			{
			case KeepResult:
				interactive = false;
				break;
			case UseDramaDice:
				result += use(dices, DramaDice);
				break;
			}
		}
	}
	if(return_result)
		*return_result = result;
	return result >= target_number;
}

void hero::damage(int wounds_count, bool interactive, int drama_per_wounds)
{
	wounds += wounds_count;
	int dices[32];
	auto bonus = 0;
	auto train = Brawn;
	auto keep = get(Brawn);
	auto roll = keep;
	auto result = rolldices(dices, roll, keep, bonus, true);
	if(interactive)
	{
		auto content = logs::getptr();
		while(interactive)
		{
			logs::add("\n");
			sayroll(zend(content), Brawn, NoKnack, wounds);
			add_result(zend(content), dices, keep, result);
			auto w = 1 + (wounds - result) / drama_per_wounds;
			if(result >= wounds)
				logs::add(KeepResult, "Оставить [%1i] свежих ранений.", wounds);
			else
				logs::add(KeepResult, "Получить [%1i] %2.", w, maptbl(text_dramatic_wounds, w));
			if(get(DramaDice))
				logs::add(UseDramaDice, "Использовать кубик драмы (осталось [%1i])", get(DramaDice));
			auto id = (result_aciton_s)logs::input(true, false);
			content[0] = 0;
			switch(id)
			{
			case KeepResult:
				interactive = false;
				break;
			case UseDramaDice:
				result += use(dices, DramaDice);
				break;
			}
		}
	}
	if(result < wounds)
	{
		auto count = 1 + (wounds - result) / drama_per_wounds;
		logs::add("%1 получил%2 [%3i] %4.", getname(), getA(), count, maptbl(text_dramatic_wounds, count));
		dramawound += count;
	}
	else
		logs::add("У %1 теперь [%2i] свежих ранений.", getname(), wounds);
}

bool hero::contest(bool interactive, trait_s trait, knack_s knack, int bonus, hero* opponent, trait_s opponent_trait, knack_s opponent_knack, int opponent_bonus)
{
	while(true)
	{
		auto p1_rs = 0;
		auto p2_rs = 0;
		auto p1_tn = opponent->get(opponent_trait) * 5;
		auto p2_tn = get(trait) * 5;
		roll(interactive && isplayer(), trait, knack, p1_tn, bonus, &p1_rs);
		opponent->roll(interactive && opponent->isplayer(), opponent_trait, opponent_knack, p2_tn, opponent_bonus, &p2_rs);
		if(p1_rs >= p1_tn && p2_rs < p2_tn)
			return true;
		if(p2_rs >= p2_tn && p1_rs < p1_tn)
			return false;
		if(p2_rs >= p2_tn && p1_rs >= p1_tn)
			return p1_rs >= p2_rs;
	}
}

bool hero::isplayer() const
{
	for(auto e : players)
	{
		if(e == this)
			return true;
	}
	return false;
}