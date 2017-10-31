#include "main.h"

struct advantage_i
{
	const char*		name[2];
	char			cost;
} advantage_data[] = {
	{{"Able drinker", "����������� ����"}, 1},
	{{"Academy", "������� ��������"}, 4},
	{{"Appearance", "���������"}},
	{{"Castillian Education", "����������� �����������"}, 10},
	{{"Citation", "�������"}, 4},
	{{"Connections", "�����"}},
	{{"Combat Reflexes", "������ ��������"}, 3},
	{{"Commissions", "������� ������"}},
	{{"Dangerous beauty", "������������ �������"}, 5},
	{{"Dracheneisen", "�����������"}},
	{{"Faith", "����"}},
	{{"Foul Weather Jack", "���� ������ ������"}, 5},
	{{"Indomitable will", "�������� ����"}, 3},
	{{"Inheritance", "�������������"}},
	{{"Keen Sences", "������ �������"}},
	{{"Large", "�������"}, 5},
	{{"Left-handed", "�����"}},
	{{"Legendary finess", "����������� ����������"}},
	{{"Linguist", "��������"}},
	{{"Trade guild", "������� ���������"}},
	{{"Noble", "��������"}},
	{{"Ordained", "�������� ���"}},
	{{"Patron", "�����������"}},
	{{"Scoundrel", "�������"}},
	{{"Servants", "�����"}},
	{{"Small", "������"}, 2},
	{{"Toughness", "�������"}, 5},
	{{"University", "�����������"}, 3},
};

int	hero::getcost(advantage_s id) const
{
	switch(id)
	{
	case Noble: return issorcery() ? 5 : 10;
	case CastilliansEducation: return (nation == Castille) ? advantage_data[id].cost : 0;
	default: return advantage_data[id].cost;
	}
}