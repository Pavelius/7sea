#include "main.h"

static struct sorcery_i
{
	const char*		name[2];
} sorcery_data[] = {
	{{"",""}},
	{{"Glamour", "Гламур"}},
	{{"Porte", "Порте"}},
	{{"Pyeryem", "Пирием"}},
	{{"Laerdom", "Лаэдрон"}},
	{{"Sorte", "Сорте"}},
};
assert_enum(sorcery, LastSorcery);
getstr_enum(sorcery);