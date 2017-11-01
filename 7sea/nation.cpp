#include "main.h"

static struct nation_i
{
	const char*		name[2];
	trait_s			trait;
	sorcery_s		sorcery;
	swordsman_s		swordsman;
	const char*		text;
} nation_data[] = {
	{{"Avalon", "Авалон"}, Resolve, Glamour, Donowan, "Зеленая и зачарованная земля. Представляет собой союз трех королевств, недавно появившийся на горизонте тэйянской политики."},
	{{"Castille", "Кастилия"}, Finesse, NoSorcery, Aldana, "Штаб-квартира ватицинской церкви. Эта плодородная земля недавно пала под натиском армий Монтеня, обрушившихся на нее с севера."},
	{{"Eisen", "Эйзен"}, Brawn, NoSorcery, Eisenfaust, "Некогда гордая страна, пытающая восстановиться после разрушительной Войны Креста."},
	{{"Montaigne", "Монтань"}, Panache, Porte, Valroux, "Одна из самых могущественных стран Тэйи, мировой лидер в культуре и искусстве. Его народ задыхается под пятой Императора."},
	{{"Ussura", "Уссура"}, Resolve, Pyeryem, NoSwordsman, "Пустынная и дикая страна, люди которой до сих пор живут тем же укладом, что и их предки много веков назад."},
	{{"Vendel", "Вендель"}, Wits, Laerdom, NoSwordsman, "Сообщество островов, разделенных между гильдиями, пытающимися взять под контроль всю экономику Тэйи, и кровожадными варварами, отказывающимися расстаться с прошлым."},
	{{"Vodacce", "Водачче"}, Wits, Sorte, NoSwordsman, "Бывшая колыбель цивилизации, разделенная между семью торговыми принцами, чьи изощренные интриги достигают любого, даже самого далекого уголка Тэйи."},
	{{"Crescent", "Крещенский"}, Wits, NoSorcery},
	{{"Hight Eisen", "Высший эйзенский"}, Wits, NoSorcery},
	{{"Teodoran", "Теодоран"}, Wits, NoSorcery},
	{{"Thean", "Теянский"}, Wits, NoSorcery}
};
assert_enum(nation, LastLanguage);
getstr_enum(nation);
getinf_enum(nation);

sorcery_s hero::getsorcery() const
{
	return nation_data[nation].sorcery;
}

swordsman_s hero::getswordsman() const
{
	return nation_data[nation].swordsman;
}

void hero::set(nation_s value)
{
	traits[nation_data[value].trait]++;
}