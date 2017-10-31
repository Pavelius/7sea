#include "main.h"

struct advantage_i
{
	const char*				name[2];
	char					cost;
	adat<skill_s, 4>		skills;
	adat<advantage_s, 4>	deny;
} advantage_data[] = {
	{{"Able drinker", "Способность пить"}, 1},
	{{"Academy", "Военная академия"}, 4},
	{{"Appearance", "Внешность"}, 5},
	{{"Castillian Education", "Кастильское образование"}, 10},
	{{"Citation", "Награда"}, 4, {}, {1, Scoundrel}},
	{{"Combat Reflexes", "Боевые рефлексы"}, 3},
	{{"Commissions", "Военное звание"}, 4},
	{{"Dangerous beauty", "Убийственная красота"}, 5},
	{{"Dracheneisen", "Дракенайзен"}, 20},
	{{"Foul Weather Jack", "Джек Плохая погода"}, 5},
	{{"Indomitable will", "Железная воля"}, 3},
	{{"Keen Sences", "Острые чувства"}, 2},
	{{"Large", "Большой"}, 5, {}, {1, Small}},
	{{"Linguist", "Лингвист"}, 2},
	{{"Noble", "Дворянин"}, 10},
	{{"Ordained", "Духовный сан"}, 4, {1, Scholar}},
	{{"Scoundrel", "Негодяй"}, 3, {1, Streetwise}, {1, Citation}},
	{{"Small", "Карлик"}, 2, {}, {1, Large}},
	{{"Toughness", "Живучий"}, 5},
	{{"University", "Университет"}, 3},
};
assert_enum(advantage, LastAdvantage);
getstr_enum(advantage);

int	hero::getcost(advantage_s id) const
{
	switch(id)
	{
	case DracheneisenNoble: return (nation == Eisen) ? advantage_data[id].cost : 0;
	case CastilliansEducation: return (nation == Castille) ? advantage_data[id].cost : 0;
	case Noble: return issorcery() ? 5 : 10;
	default: return advantage_data[id].cost;
	}
}