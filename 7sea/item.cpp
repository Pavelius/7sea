#include "main.h"

static struct item_i
{
	struct weapon_i
	{
		knack_s			attack;
		knack_s			parry;
		damageinfo		damage;
	};
	const char*			name[2];
	weapon_i			weapon;
} item_data[] = {
	{{"",""}, {AttackImprovisedWeapon, ParryImprovisedWeapon, {0, 2}}},
	//Pistol, Bow, Rapier, Sword, Axe, Spear,
	{{"Pistol", ""}, {AttackFirearms, NoKnack, {5,3}}},
	{{"Bow", ""}, {AttackBow, NoKnack, {2, 2}}},
	{{"Rapier", ""}, {AttackFencing, ParryFencing, {2, 2}}},
	{{"Sword", ""}, {AttackHeavyWeapon, ParryHeavyWeapon, {3, 2}}},
	{{"Axe", ""}, {AttackHeavyWeapon, ParryHeavyWeapon, {3, 2}}},
	{{"Spear", ""}, {AttackPolearm, ParryPolearm, {2, 2}}},
};
assert_enum(item, Spear);
getstr_enum(item);

const damageinfo& item::getdamage() const
{
	return item_data[type].weapon.damage;
}