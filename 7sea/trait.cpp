#include "main.h"

static struct trait_i
{
	const char*		name[2];
} trait_data[] = {
	{{"Brawn", "����"}},
	{{"Finesse", "����������"}},
	{{"Resolve", "���������"}},
	{{"Wits", "�����"}},
	{{"Panache", "��������"}},
};
assert_enum(trait, Panache);
getstr_enum(trait);