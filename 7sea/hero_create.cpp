#include "main.h"

static const char* text_points[] = {"очков", "очко", "очка", "очка", "очка", "очков"};

static char* add(char* p, char* result, const char* title, const char* name, int value, int minimal_number = 1)
{
	if(!value)
		return p;
	if(p == result)
		szprint(p, "%1: ", title);
	else
		zcat(p, ", ");
	p = szprint(zend(p), (value>=minimal_number) ? "%1 %2i" : "%1", name, value);
	return zend(p);
}

static char* add_traits(char* result, hero* player, const char* end)
{
	auto p = result;
	for(auto i = FirstTrait; i <= LastTrait; i = (trait_s)(i + 1))
		p = add(p, result, "Особенности", getstr(i), player->get(i));
	if(p != result)
	{
		zcat(p, end);
		p = zend(p);
	}
	return p;
}

static char* add_knacks(char* result, hero* player, const char* end)
{
	auto p = result;
	for(auto i = FirstKnack; i <= LastKnack; i = (knack_s)(i + 1))
		p = add(p, result, "Навыки", getstr(i), player->get(i));
	if(p != result)
	{
		zcat(p, end);
		p = zend(p);
	}
	return p;
}

static char* add_advantages(char* result, hero* player, const char* end)
{
	auto p = result;
	for(auto i = FirstAdvantage; i <= LastAdvantage; i = (advantage_s)(i + 1))
		p = add(p, result, "Преемущества", getstr(i), player->get(i), 2);
	if(p != result)
	{
		zcat(p, end);
		p = zend(p);
	}
	return p;
}

static void add_hero(char* result, hero* player)
{
	auto p = add_traits(result, player, "\n");
	p = add_advantages(p, player, "\n");
	p = add_knacks(p, player, "\n");
	if(player->experience)
		szprint(p, "У вас осталось [%1i] очков.", player->experience);
}

static void print_hero(hero* player)
{
	char temp[2048]; temp[0] = 0;
	add_hero(temp, player);
	logs::add(temp);
}

void hero::choosenation(bool interactive)
{
	print_hero(this);
	for(auto i = FirstNation; i <= LastNation; i = (nation_s)(i + 1))
		logs::add(i, "[%1]: %2", getstr(i), getinfo(i));
	nation = (nation_s)logs::input(interactive, true, "Откуда вы родом?");
}

void hero::choosetraits(bool interactive)
{
	auto count = 2;
	memset(traits, 2, sizeof(traits));
	while(count > 0)
	{
		print_hero(this);
		for(auto i = FirstTrait; i <= LastTrait; i = (trait_s)(i + 1))
		{
			if(traits[i] >= 3)
				continue;
			logs::add(i, "[%1]. %2", getstr(i), getinfo(i));
		}
		auto id = (trait_s)logs::input(interactive, true, "Выберите особенность, в которых вы сильны (осталось [%1i])", count--);
		traits[id]++;
	}
	experience = 100 - 8 * (5 + 2);
}

void hero::chooseadvantage(bool interactive)
{
	if(getsorcery())
	{
		auto value = getsorcery();
		print_hero(this);
		logs::add("Ваши родители владели волшебством?");
		logs::add(0, "Нет, мои родители не владели волшебством.");
		if(experience >= 20)
			logs::add(1, "Да. Один из них был волшебником, поэтому я буду владеть волшебством [%1] на базовом уровне. Это стоит [20] очков.", getstr(value));
		if(experience >= 40)
			logs::add(2, "Оба моих родителя были волшебниками, поэтому я буду весьма способным волшебником [%1]. Это стоит [40] очков.", getstr(value));
		sorcery = logs::input();
		switch(sorcery)
		{
		case 1: experience -= 20; break;
		case 2: experience -= 40; break;
		}
	}
	if(getswordsman())
	{
		auto value = getswordsman();
		print_hero(this);
		logs::add("Вы входите в школу фехтовальщиков [%1]?", getstr(value));
		logs::add(0, "Нет, я получил обучение военным навыкам на базовом уровне.");
		if(experience >= 25)
			logs::add(1, "Да. Я вхожу в школу фехтовальщиков [%1]. Это стоит [25] очков.", getstr(value));
		swordsman = logs::input();
		switch(swordsman)
		{
		case 1: experience -= 25; break;
		}
	}
	if(true)
	{
		print_hero(this);
		auto cost = getcost(Noble);
		logs::add("Ваша семья является знатной семьей нации [%1]?", getstr(nation));
		logs::add(0, "Нет, я простой ремесленник, рабочий или крестьянин.");
		if(experience >= cost)
			logs::add(1, "Да. Я родом из знатной семьи дворян. Это стоит [%1i] очков.", cost);
		if(logs::input())
		{
			advantages[Noble] = 1;
			experience -= cost;
		}
	}
	if(true)
	{
		print_hero(this);
		for(auto i = (advantage_s)FirstAdvantage; i <= LastAdvantage; i = (advantage_s)(i+1))
		{
			if(i == Noble)
				continue;
			if(get(i))
				continue;
			auto cost = getcost(i);
			if(!cost || cost>experience)
				continue;
			logs::add(i, "%1 (стоит [%2i] %3).", getstr(i), cost, maptbl(text_points, cost));
		}
		if(logs::getcount())
		{
			auto result = (advantage_s)logs::input(interactive, true, "Выбирайте [одно] преемущество из списка ниже");
			experience -= getcost(result);
			set(result);
		}
	}
}

void hero::chooseskills(bool interactive)
{
	print_hero(this);
	for(auto i = Artist; i <= Streetwise; i = (skill_s)(i + 1))
		logs::add(i, getstr(i));
	auto result = (skill_s)logs::input(interactive, true, "Кто вы по профессии?");
	set(result, interactive);
}

void hero::create(bool interactive)
{
	clear();
	choosenation(interactive);
	choosetraits(interactive);
	set(nation);
	chooseadvantage(interactive);
	chooseskills(interactive);
}