#include "main.h"

struct advantage_i
{
	const char*		name[2];
	char			cost[4];
} advantage_data[] = {
	{{"Able drinker", "����������� ����"}, {1}},
	{{"Academy", "������� ��������"}},
	{{"Appearance", "���������"}},
	{{"Castillian Education", "����������� �����������"}},
	{{"Citation", "�������"}},
	{{"Connections", "�����"}},
	{{"Combat Reflexes", "������ ��������"}, {3}},
	{{"Commissions", "������� ������"}},
	{{"Dangerous beauty", "������������ �������"}},
	{{"Dracheneisen", "�����������"}},
	{{"Faith", "����"}},
	{{"Foul Weather Jack", "���� ������ ������"}},
	{{"Indomitable will", "�������� ����"}},
	{{"Inheritance", "�������������"}},
	{{"Keen Sences", "������ �������"}},
	{{"Large", "�������"}},
	{{"Left-handed", "�����"}},
	{{"Legendary finess", "����������� ����������"}},
	{{"Linguist", "��������"}},
	{{"Trade guild", "������� ���������"}},
	{{"Noble", "��������"}},
	{{"Ordained", "�������� ���"}},
	{{"Patron", "�����������"}},
	{{"Scoundrel", "�������"}},
	{{"Servants", "�����"}},
	{{"Small", "������"}},
	{{"Toughness", "�������"}},
	{{"University", "�����������"}},
};

int	hero::getcost(advantage_s id, int level) const
{
	switch(id)
	{
	case Noble:
		return issorcery() ? 5 : 10;
	default:
		return advantage_data[id].cost[level];
	}
}