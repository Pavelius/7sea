#include "main.h"

static const char* text_points[] = {"�����", "����", "����", "����", "����", "�����"};

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
		p = add(p, result, "�����������", getstr(i), player->get(i));
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
		p = add(p, result, "������", getstr(i), player->get(i));
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
		p = add(p, result, "������������", getstr(i), player->get(i), 2);
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
		szprint(p, "� ��� �������� [%1i] �����.", player->experience);
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
	nation = (nation_s)logs::input(interactive, true, "������ �� �����?");
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
		auto id = (trait_s)logs::input(interactive, true, "�������� �����������, � ������� �� ������ (�������� [%1i])", count--);
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
		logs::add("���� �������� ������� �����������?");
		logs::add(0, "���, ��� �������� �� ������� �����������.");
		if(experience >= 20)
			logs::add(1, "��. ���� �� ��� ��� �����������, ������� � ���� ������� ����������� [%1] �� ������� ������. ��� ����� [20] �����.", getstr(value));
		if(experience >= 40)
			logs::add(2, "��� ���� �������� ���� ������������, ������� � ���� ������ ��������� ����������� [%1]. ��� ����� [40] �����.", getstr(value));
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
		logs::add("�� ������� � ����� �������������� [%1]?", getstr(value));
		logs::add(0, "���, � ������� �������� ������� ������� �� ������� ������.");
		if(experience >= 25)
			logs::add(1, "��. � ����� � ����� �������������� [%1]. ��� ����� [25] �����.", getstr(value));
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
		logs::add("���� ����� �������� ������� ������ ����� [%1]?", getstr(nation));
		logs::add(0, "���, � ������� �����������, ������� ��� ����������.");
		if(experience >= cost)
			logs::add(1, "��. � ����� �� ������� ����� ������. ��� ����� [%1i] �����.", cost);
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
			logs::add(i, "%1 (����� [%2i] %3).", getstr(i), cost, maptbl(text_points, cost));
		}
		if(logs::getcount())
		{
			auto result = (advantage_s)logs::input(interactive, true, "��������� [����] ������������ �� ������ ����");
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
	auto result = (skill_s)logs::input(interactive, true, "��� �� �� ���������?");
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