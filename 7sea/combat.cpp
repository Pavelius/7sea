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
	char			actions[10];
	brute_i*		brute;
	int				count;
	hero*			player;
	side_s			side;

	operator bool() const { return count != 0; }
	typedef bool (combatant::*isproc)() const;
	typedef bool (combatant::*isprocp)(const combatant* p) const;
	typedef int (combatant::*getproc)() const;

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

	bool ishero() const
	{
		return player != 0;
	}

	bool isfencing() const
	{
		return player != 0 && true;
	}

	bool isenemy(const combatant* p) const
	{
		return side != p->side;
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
		return (1 + player->get(knack));
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

static combatant* choose(bool interactive, combatant** targets, combatant::getproc gettn)
{
	if(targets[0] == 0)
		return 0;
	if(targets[1] == 0)
		return targets[0];
	for(auto i = 0; targets[i]; i++)
	{
		if(gettn)
			logs::add(i, "%1 (сложность [%2i])", targets[i]->getname(), (targets[i]->*gettn)());
		else
			logs::add(i, targets[i]->getname());
	}
	auto i = logs::input(interactive, true, "Укажите [цель]:");
	return targets[i];
}

static bool ishero(const combatant* p)
{
	return p->player != 0;
}

static bool isfencing(const combatant* p)
{
	return p->player && true;
}

static combatant** select(combatant** result, combatant** source, combatant::isproc validate, unsigned count = combatant_count - 1)
{
	auto ps = result;
	auto pe = result + count;
	for(auto p = source; *p; p++)
	{
		if(validate && !((*p)->*validate)())
			continue;
		if(ps < pe)
			*ps++ = *p;
	}
	*ps = 0;
	return result;
}

static combatant** select(combatant** result, combatant::isprocp validate, const combatant* param, unsigned count = combatant_count - 1)
{
	auto ps = result;
	auto pe = result + count;
	for(auto& e : combatants)
	{
		if(!(e.*validate)(param))
			continue;
		if(ps < pe)
			*ps++ = &e;
	}
	*ps = 0;
	return result;
}

static bool has(combatant** enemies, combatant::isproc validate)
{
	combatant* result[2]; select(result, enemies, validate, 1);
	return result[0] != 0;
}

static combatant* getenemy(bool interactive, combatant** enemies, knack_s knack, knack_s attack_knack)
{
	if(knack == attack_knack)
		return choose(interactive, enemies, &combatant::getpassivedefence);
	combatant* source[32];
	return choose(interactive, select(source, enemies, &combatant::ishero), &combatant::getpassivedefence);
}

static struct action
{
	trait_s				trait;
	knack_s				knack;
	const char*			text;
	bool				hostile;
	combatant::isproc	validate;
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
	{Finesse, Beat, "Нанести сильный удар, который враг не сможет блокировать.", true, &combatant::ishero},
	{Finesse, Bind, "Скрутить оружие врага.", true, &combatant::isfencing},
	{Finesse, CorpseACorpse, "Сойтись в близкой схватке, тело к телу.", true, &combatant::ishero},
	{Finesse, Feint, "Выполнить обманную атаку.", true, &combatant::ishero},
	{Finesse, Lunge, "Нанести сокрушительный удар, который нанесет много урона.", true, &combatant::ishero},
	{Finesse, PommelStrike, "Нанести удар гардой в лицо.", true, &combatant::ishero},
	{Finesse, Togging, "Выполнить яркий и вызывающий трюк, который обозлит или унизит врага.", true, &combatant::ishero},
};

static void make_move(combatant* player)
{
	char temp[512];
	bool interactive = (player->player && player->player->isplayer());
	combatant* enemies[combatant_count + 1];
	select(enemies, &combatant::isenemy, player, sizeof(enemies) / sizeof(enemies[0]) - 1);
	auto enemies_count = zlen(enemies);
	if(!enemies[0])
		return;
	logs::add("\n");
	if(player->ishero())
	{
		for(unsigned i = 0; i < sizeof(action_data) / sizeof(action_data[0]); i++)
		{
			// Проверим есть ли навык
			if(!player->get(action_data[i].knack))
				continue;
			// Если есть особые условия проверим их
			if(action_data[i].validate && !has(enemies, action_data[i].validate))
				continue;
			logs::add(i, action_data[i].text);
		}
		auto id = (knack_s)logs::input(interactive, false, "Что будет делать [%1]?", player->getname());
		auto& a = action_data[id];
		auto enemy = choose(interactive, select(enemies, enemies, action_data[id].validate), &combatant::getpassivedefence);
		roller dr;
		dr.player = player->player;
		dr.trait = a.trait;
		dr.knack = a.knack;
		dr.keep = player->get(dr.trait);
		dr.roll = dr.keep + player->get(dr.knack);
		dr.target_number = enemy->getpassivedefence();
		if(enemy->ishero())
		{
			dr.rolldices();
			if(dr.standart(interactive))
				enemy->damage(5);
		}
		else
		{
			logs::add(0, "Вырубить одного из них. Сложность [%1i].", dr.target_number);
			if(enemy->count > 1)
				logs::add(1, "Вырубить сразу [двух] за раз. Сложность [%1i].", dr.target_number + 5 * 1);
			if(enemy->count > 2)
				logs::add(2, "Вырубить сразу [трех] за раз. Сложность [%1i].", dr.target_number + 5 * 2);
			if(enemy->count > 3)
				logs::add(3, "Вырубить сразу [четырех] за раз. Сложность [%1i].", dr.target_number + 5 * 3);
			dr.target_number = enemy->getpassivedefence();
			auto raises = logs::input(interactive, false, dr.getpromt(temp, false));
			dr.target_number += 5 * raises;
			dr.rolldices();
			auto killed = raises + 1;
			if(dr.result >= dr.target_number)
			{
				enemy->count -= killed;
				logs::add("%1 атаковал%2 %3 и уложил%2 %4.", player->getname(), player->getA(), enemy->getname(), maptbl(text_count, killed));
			}
			else
				logs::add("%1 атаковал%2 %3, но не смог никого одолеть.", player->getname(), player->getA(), enemy->getname(), maptbl(text_count, killed));
		}
	}
	else
	{
		auto enemy = enemies[rand() % zlen(enemies)];
		logs::add("%1 набросились на %2.", player->getname(), enemy->getname());
		roller dr;
		dr.roll = player->brute->threat;
		dr.keep = player->count;
		dr.target_number = player->getpassivedefence();
		dr.rolldices();
		if(enemy->ishero())
		{
			if(dr.result >= dr.target_number)
				enemy->damage(dr.result - dr.target_number);
		}
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