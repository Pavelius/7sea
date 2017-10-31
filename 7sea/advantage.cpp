#include "main.h"

struct advantage_i
{
	const char*		name[2];
	char			cost;
} advantage_data[] = {
	{{"Able drinker", "Способность пить"}, 1},
	{{"Academy", "Военная академия"}, 4},
	{{"Appearance", "Внешность"}},
	{{"Castillian Education", "Кастильское образование"}, 10},
	{{"Citation", "Награда"}, 4},
	{{"Connections", "Связи"}},
	{{"Combat Reflexes", "Боевые рефлексы"}, 3},
	{{"Commissions", "Военное звание"}},
	{{"Dangerous beauty", "Убийственная красота"}, 5},
	{{"Dracheneisen", "Дракенайзен"}},
	{{"Faith", "Вера"}},
	{{"Foul Weather Jack", "Джек Плохая погода"}, 5},
	{{"Indomitable will", "Железная воля"}, 3},
	{{"Inheritance", "Собственность"}},
	{{"Keen Sences", "Острые чувства"}},
	{{"Large", "Большой"}, 5},
	{{"Left-handed", "Левша"}},
	{{"Legendary finess", "Легендарное мастерство"}},
	{{"Linguist", "Лингвист"}},
	{{"Trade guild", "Гильдия торговцев"}},
	{{"Noble", "Дворянин"}},
	{{"Ordained", "Духовный сан"}},
	{{"Patron", "Покровитель"}},
	{{"Scoundrel", "Негодяй"}},
	{{"Servants", "Слуги"}},
	{{"Small", "Карлик"}, 2},
	{{"Toughness", "Живучий"}, 5},
	{{"University", "Университет"}, 3},
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