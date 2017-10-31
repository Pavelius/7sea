#include "main.h"

static struct trait_i
{
	const char*		name[2];
} trait_data[] = {
	{{"Brawn", "Мощь"}},
	{{"Finesse", "Мастерство"}},
	{{"Resolve", "Стойкость"}},
	{{"Wits", "Разум"}},
	{{"Panache", "Характер"}},
};
assert_enum(trait, Panache);
getstr_enum(trait);