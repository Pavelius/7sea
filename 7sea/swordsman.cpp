#include "main.h"

static struct swordsman_i
{
	const char*		name[2];
} swordsman_data[] = {
	{{"", ""}},
	{{"Aldana", "�������"}},
	{{"Ambrogia", "���������"}},
	{{"Donowan", "�������"}},
	{{"Eisenfaust", "����������"}},
	{{"Leegstra", "�������"}},
	{{"Valroux", "��������"}},
};
assert_enum(swordsman, LastSwordsmansSchool);
getstr_enum(swordsman);