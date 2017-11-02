#include "main.h"
#include "stringcreator.h"
#include "command.h"

enum side_s : char {
	PartySide, EnemySide,
};
enum combat_command_s {
	FirstAction, LastAction = FirstAction + 32,
};

static char			round, phase;

struct knackset
{
	knack_s			id;
	char			value;
	operator bool() const { return value != 0; }
};
static struct brute_i
{
	const char*		name[3];
	char			threat;
	knackset		skills[8];

	int get(knack_s id) const
	{
		for(auto& e : skills)
		{
			if(e.id == id)
				return e.value;
			if(!e)
				break;
		}
		return 0;
	}

} brute_data[] = {
	{{"Cardinal's mens", "Люди кардинала", "Человек кардинала"}, 3, {Footwork, -1, Sprinting, 1}}
};

struct combatant
{
	char		actions[10];
	brute_i*	brute;
	int			count;
	hero*		player;
	side_s		side;

	operator bool() const { return count!=0; }

	int get(trait_s id) const
	{
		if(player)
			return player->get(id);
		else
			return brute->threat;
	}

	int get(knack_s id) const
	{
		if(player)
			return player->get(id);
		else
			return brute->get(id);
	}

	int getactions() const
	{
		auto result = 0;
		for(auto e : actions)
		{
			if(e == 0)
				break;
			result += e;
		}
		return result;
	}

	void clear()
	{
		memset(this, 0, sizeof(*this));
	}

	const char* getname() const
	{
		if(player)
			return player->getname();
		return brute->name[1];
	}

	void useaction()
	{
		memcpy(actions, actions + 1, sizeof(actions) - 1);
		actions[sizeof(actions) - 1] = 0;
	}

};
static adat<combatant, 32> combatants;

struct action
{
	combatant*		player;
	trait_s			trait;
	knack_s			knack;
	char			raises;
	combatant*		enemy;
	action()
	{
		memset(this, 0, sizeof(*this));
	}
};
static adat<action,32>	actions;

static int compare_dices(const void* p1, const void* p2)
{
	return *((char*)p1) - *((char*)p2);
}

static void add(hero* object, side_s side = PartySide)
{
	auto p = combatants.add();
	if(!p)
		return;
	p->clear();
	p->player = object;
	p->count = 1;
	p->side = side;
}

static void add(brute_i* object, side_s side = EnemySide)
{
	auto p = combatants.add();
	if(!p)
		return;
	p->clear();
	p->brute = object;
	p->count = 6;
	p->side = side;
}

static combatant* choose(bool interactive, combatant** targets)
{
	if(targets[0] == 0)
		return 0;
	if(targets[1] == 0)
		return targets[0];
	for(auto i = 0; targets[i]; i++)
		logs::add(i, targets[i]->getname());
	auto i = logs::input(interactive, true, "Укажите [цель]:");
	return targets[i];
}

static void add(combatant* actor, trait_s trait, knack_s knack, bool interactive, combatant** enemies, char raises, combatant* target, const char* format, ...)
{
	auto p = actions.add();
	logs::addv(actions.count - 1 + FirstAction, format, xva_start(format));
}

static action getaction(int id)
{
	actions.count = 0;
	return actions.data[id - FirstAction];
}

static void make_move(combatant* player)
{
	bool interactive = (player->player && player->player->isplayer());
	combatant* enemies[sizeof(combatants) / sizeof(combatants[0]) + 1]; enemies[0] = 0;
	for(auto& e : combatants)
	{
		if(player->side != e.side)
			zcat(enemies, &e);
	}
	if(!enemies[0])
		return;
	auto attack_knack = AttackFencing;
	auto defence_knack = Footwork;
	add(player, Finesse, attack_knack, interactive, enemies, 0, 0, "Атаковать врага [рапирой].");
	if(player->get(Riposte))
		add(player, Finesse, attack_knack, interactive, enemies, 0, 0, "Атаковать врага [рапирой].");
	if(player->get(Beat))
		add(player, Finesse, Beat, interactive, enemies, 0, 0, "Нанести мощнейший удар, который пробьет защиту врага.");
	if(player->get(PommelStrike))
		add(player, Finesse, PommelStrike, interactive, enemies, 0, 0, "Нанести неожиданный удар ручкой оружия в лицо.");
	auto id = logs::input(interactive, true, "Что будет делать [%1]?", player->getname());
	if(id >= FirstAction && id <= LastAction)
	{
		auto ac = getaction(id);
		if(!ac.enemy)
			ac.enemy = choose(interactive, enemies);
		player->useaction();
	}
}

static void roll_initiative()
{
	for(auto& e : combatants)
	{
		if(!e)
			continue;
		memset(e.actions, 0, sizeof(e.actions));
		auto panache = e.get(Panache);
		for(auto i = 0; i < panache; i++)
			e.actions[i] = 1 + rand() % 10;
		qsort(e.actions, panache, sizeof(e.actions[0]), compare_dices);
	}
}

static void resolve_round()
{
	roll_initiative();
	for(phase = 1; phase <=10; phase++)
	{
		for(auto& e : combatants)
		{
			if(!e)
				continue;
			if(e.actions[0] != phase)
				continue;
			make_move(&e);
		}
	}
}

static bool is_combat_continue()
{
	auto side = combatants[0].side;
	for(auto& e : combatants)
	{
		if(e.side != side)
			return true;
	}
	return false;
}

void game::combat()
{
	logs::state push;
	logc.information = "%round\n%combatants";
	round = 1; phase = 0;
	add(players[0], PartySide);
	add(players[1], PartySide);
	add(brute_data, EnemySide);
	while(is_combat_continue())
	{
		resolve_round();
		round++;
	}
};

static void print_round(char* result)
{
	szprint(result, "##Раунд %1i, фаза %2i", round, phase);
}

static void print_combatant(char* result, combatant& e)
{
	zcat(result, e.getname());
	if(e.actions[0])
	{
		zcat(result, ": ");
		auto p = zend(result);
		for(auto e : e.actions)
		{
			if(!e)
				break;
			if(p[0])
				zcat(p, ", ");
			sznum(zend(p), e);
		}
		zcat(result, ".");
	}
}

static void print_combatants(char* result)
{
	result[0] = 0;
	for(auto& e : combatants)
	{
		if(result[0])
			zcat(result, "\n");
		print_combatant(zend(result), e);
	}
}

static stringcreator::plugin::element elements[] = {
	{"round", print_round},
	{"combatants", print_combatants},
};
static stringcreator::plugin plugin(elements, sizeof(elements));