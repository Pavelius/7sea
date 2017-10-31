#include "main.h"

struct advantage_i
{
	const char*		name[2];
	char			cost[4];
} advantage_data[] = {
	{{"Able drinker", "Способность пить"}, {1}},
	{{"Academy", "Военная академия"}},
	{{"Appearance", "Внешность"}},
	{{"Castillian Education", "Кастильское образование"}},
	{{"Citation", "Награда"}},
	{{"Connections", "Связи"}},
	{{"Combat Reflexes", "Боевые рефлексы"}, {3}},
	{{"Commissions", "Военное звание"}},
	{{"Dangerous beauty", "Убийственная красота"}},
	{{"Dracheneisen", "Дракенайзен"}},
	{{"Faith", "Вера"}},
	{{"Foul Weather Jack", "Джек Плохая погода"}},
	{{"Indomitable will", "Железная воля"}},
	{{"Inheritance", "Собственность"}},
	{{"Keen Sences", "Острые чувства"}},
	{{"Large", "Большой"}},
	{{"Left-handed", "Левша"}},
	{{"Legendary finess", "Легендарное мастерство"}},
	{{"Linguist", "Лингвист"}},
	{{"Trade guild", "Гильдия торговцев"}},
	{{"Noble", "Дворянин"}},
	{{"Ordained", "Духовный сан"}},
	{{"Patron", "Покровитель"}},
	{{"Scoundrel", "Негодяй"}},
	{{"Servants", "Слуги"}},
	{{"Small", "Карлик"}},
	{{"Toughness", "Живучий"}},
	{{"University", "Университет"}},
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