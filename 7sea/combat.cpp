#include "main.h"
#include "stringcreator.h"
#include "command.h"

static const char* text_count[] = {"ниодного", "одного", "двоих", "троих", "четверых", "пятерых", "шестерых", "семерых", "всех"};

const unsigned combatant_count = 32;

static struct brute_i
{
	struct knackset
	{
		knack_s			id;
		char			value;
		operator bool() const { return value != 0; }
	};
	const char*			name[3];
	char				threat;
	knackset			skills[8];

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

static char			round, phase;

struct combatant
{
	brute_i*		brute;
	hero*			player;
	char			actions[10];
	int				count;
	side_s			side;

	operator bool() const { return count != 0; }

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

	const char* getA() const
	{
		if(player)
			return player->getA();
		if(count)
			return "";
		return "и";
	}

	const char* getAS() const
	{
		if(player)
			return player->getAS();
		if(count)
			return "ся";
		return "ись";
	}

	bool ishero() const
	{
		return player != 0;
	}

	bool isenemy(const combatant* p) const
	{
		return side != p->side;
	}

	bool isenemyhero(const combatant* p) const
	{
		if(!p->ishero())
			return false;
		return isenemy(p);
	}

	knack_s getdefence() const
	{
		return Footwork;
	}

	int getpassivedefence() const
	{
		if(brute)
			return (1 + brute->threat) * 5;
		auto knack = getdefence();
		return (1 + player->get(knack)) * 5;
	}

	void useaction()
	{
		memcpy(actions, actions + 1, sizeof(actions) - 1);
		actions[sizeof(actions) - 1] = 0;
	}

	void damage(int wounds, int raises = 0)
	{
		if(brute)
			count -= 1 + raises;
		else
			player->damage(wounds, true);
		if(count < 0)
			count = 0;
	}

};
static adat<combatant, combatant_count> combatants;

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

static struct action
{
	trait_s				trait;
	knack_s				knack;
	const char*			text;
	bool				hostile;
	bool				heroonly;
	operator bool() const { return text != 0; }
} action_data[] = {
	{Finesse, AttackBow, "Пустить стрелу из [лука].", true},
	{Finesse, AttackCrossbow, "Выстрелить из [арбалета].", true},
	{Finesse, AttackDirtyFighting, "Ударить ногой в промежность или бросить песок в глаза.", true},
	{Finesse, AttackFencing, "Атаковать врага [рапирой].", true},
	{Finesse, AttackFirearms, "Выстрелить из [пистоля].", true},
	{Finesse, AttackHeavyWeapon, "Рубить всех врагов [мечом].", true},
	{Finesse, AttackKnife, "Тыкнуть во врага [ножем].", true},
	{Finesse, AttackPanzerhand, "Нанести удар [металической рукой].", true},
	{Finesse, AttackPolearm, "Сделать тычек [копьем].", true},
	{Finesse, AttackPugilism, "Нанести удары кулаком и ногами.", true},
	{Finesse, Beat, "Нанести сильный удар, который враг не сможет блокировать.", true, true},
	{Finesse, Bind, "Скрутить оружие врага.", true, true},
	{Finesse, CorpseACorpse, "Сойтись в близкой схватке, тело к телу.", true, true},
	{Finesse, Feint, "Выполнить обманную атаку.", true, true},
	{Finesse, Lunge, "Нанести сокрушительный удар, который нанесет много урона.", true, true},
	{Finesse, PommelStrike, "Нанести удар гардой в лицо.", true, true},
	{Finesse, Togging, "Выполнить яркий и вызывающий трюк, который обозлит или унизит врага.", true, true},
};

static unsigned select(combatant** result, unsigned result_count, const combatant* player, bool hostile, bool heroonly)
{
	auto p = result;
	auto pe = result + result_count;
	for(auto& e : combatants)
	{
		if(!e)
			continue;
		if(hostile && !player->isenemy(&e))
			continue;
		if(heroonly && !player->isenemyhero(&e))
			continue;
		if(p < pe)
			*p++ = &e;
		else
			break;
	}
	return p - result;
}

static bool has(const combatant* player, bool hostile, bool heroonly)
{
	combatant* result[1];
	return select(result, sizeof(combatants.data) / sizeof(combatants.data[0]), player, hostile, heroonly) != 0;
}

static combatant* choose(const combatant* player, bool interactive, bool hostile, bool heroonly, int (combatant::*gettn)() const)
{
	combatant* result[sizeof(combatants.data) / sizeof(combatants.data[0])];
	auto count = select(result, sizeof(combatants.data) / sizeof(combatants.data[0]), player, hostile, heroonly);
	if(count == 0)
		return 0;
	else if(count == 1)
		return result[0];
	for(unsigned i = 0; i<count; i++)
	{
		if(gettn)
			logs::add(i, "%1 (сложность [%2i])", result[i]->getname(), (result[i]->*gettn)());
		else
			logs::add(i, result[i]->getname());
	}
	auto i = logs::input(interactive, true, "Укажите [цель]:");
	return result[i];
}

static void make_move(combatant* player)
{
	char temp[512];
	bool interactive = (player->player && player->player->isplayer());
	if(player->ishero())
	{
		for(unsigned i = 0; i < sizeof(action_data) / sizeof(action_data[0]); i++)
		{
			if(!player->get(action_data[i].knack))
				continue;
			if(!has(player, action_data[i].hostile, action_data[i].heroonly))
				continue;
			logs::add(i, action_data[i].text);
		}
		auto& a = action_data[logs::input(interactive, false, "Что будет делать [%1]?", player->getname())];
		logs::add("\n");
		auto enemy = choose(player, interactive, a.hostile, a.heroonly, &combatant::getpassivedefence);
		auto roll_result = 0;
		auto hit = player->player->roll(true, a.trait, a.knack, enemy->getpassivedefence(), 0, &roll_result);
		auto tn = enemy->getpassivedefence();
		if(enemy->ishero())
		{
			if(hit)
				enemy->damage(5);
		}
		else
		{
			logs::add(0, "Вырубить одного из них. Сложность [%1i].", tn);
			if(enemy->count > 1)
				logs::add(1, "Вырубить сразу [двух] за раз. Сложность [%1i].", tn + 5 * 1);
			if(enemy->count > 2)
				logs::add(2, "Вырубить сразу [трех] за раз. Сложность [%1i].", tn + 5 * 2);
			if(enemy->count > 3)
				logs::add(3, "Вырубить сразу [четырех] за раз. Сложность [%1i].", tn + 5 * 3);
			auto raises = logs::input(interactive, false, player->player->sayroll(temp, a.trait, a.knack, 0));
			logs::add("\n");
			auto killed = 1 + raises;
			if(player->player->roll(true, a.trait, a.knack, tn + 5*raises))
			{
				enemy->damage(0, raises);
				logs::add("%1 атаковал%2 %3 и уложил%2 %4.", player->getname(), player->getA(), enemy->getname(), maptbl(text_count, killed));
			}
			else
				logs::add("%1 атаковал%2 %3, но не смог никого одолеть.", player->getname(), player->getA(), enemy->getname());
		}
	}
	else
	{
		auto enemy = choose(player, false, true, false, &combatant::getpassivedefence);
		auto tn = enemy->getpassivedefence();
		logs::add("\n");
		logs::add("%1 набросились на %2.", player->getname(), enemy->getname());
		int raises = (hero::roll(player->count, player->brute->threat) - tn)/5;
		if(raises >= 0)
		{
			int weapon = 6;
			int wounds = (1 + raises) * weapon;
			if(enemy->ishero())
				enemy->damage(wounds);
		}
		else
			logs::add("%1 удачно отбил%2.", player->getAS());
	}
	player->useaction();
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
	for(phase = 1; phase <= 10; phase++)
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
	logs::next();
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
	if(e.brute && e.count)
		szprint(zend(result), " (%1i)", e.count);
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