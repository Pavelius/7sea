#include "main.h"

static int		viledice;
hero*			players[6];

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

int hero::getdrama() const
{
	if(isplayer())
		return dramadice;
	else
		return viledice;
}

void hero::usedrama()
{
	if(isplayer())
	{
		if(dramadice)
		{
			dramadice--;
			viledice++;
		}
	}
	else
		viledice--;
}

bool hero::roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus)
{
	roller e;
	e.player = this;
	e.trait = trait;
	e.knack = knack;
	e.keep = get(trait);
	e.roll = e.keep + get(knack);
	e.bonus = bonus;
	e.target_number = target_number;
	e.rolldices();
	return e.makeroll(interactive);
}

bool hero::contest(bool interactive, trait_s trait, knack_s knack, int bonus, hero* opponent, trait_s opponent_trait, knack_s opponent_knack, int opponent_bonus)
{
	while(true)
	{
		roller e1;
		e1.player = this;
		e1.trait = trait;
		e1.knack = knack;
		e1.keep = get(trait);
		e1.roll = e1.keep + get(knack);
		e1.bonus = bonus;
		e1.target_number = opponent->get(opponent_trait) * 5;
		e1.rolldices();
		e1.makeroll(interactive && isplayer());
		roller e2;
		e2.player = opponent;
		e2.trait = opponent_trait;
		e2.knack = opponent_knack;
		e2.keep = opponent->get(trait);
		e2.roll = e2.keep + opponent->get(knack);
		e2.bonus = opponent_bonus;
		e2.target_number = get(trait) * 5;
		e2.makeroll(interactive && opponent->isplayer());
		if(e1.result >= e1.target_number && e2.result < e2.target_number)
			return true;
		if(e2.result >= e2.target_number && e1.result < e1.target_number)
			return false;
		if(e2.result >= e2.target_number && e1.result >= e1.target_number)
			return e1.result>e2.target_number;
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