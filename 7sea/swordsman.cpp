#include "main.h"

static struct swordsman_i
{
	const char*		name[2];
} swordsman_data[] = {
	{{"", ""}},
	{{"Aldana", "Альдана"}},
	{{"Ambrogia", "Амброджия"}},
	{{"Donowan", "Донован"}},
	{{"Eisenfaust", "Эйзенфауст"}},
	{{"Leegstra", "Лигстра"}},
	{{"Valroux", "Валроукс"}},
};
assert_enum(swordsman, LastSwordsmansSchool);
getstr_enum(swordsman);