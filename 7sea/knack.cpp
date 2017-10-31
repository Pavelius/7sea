#include "main.h"

static struct knack_i
{
	const char*			name[2];
} knack_data[] = {
	{{"Composer", "����������"}},
	{{"Drawing", "���������"}},
	{{"Musician", "��������"}},
	{{"Sculpting", "���������"}},
	{{"Singing", "�����"}},
	{{"Writing", "������"}},
	{{"Dancing", "�����"}},
	{{"Etiquette", "������"}},
	{{"Fashion", "�����"}},
	{{"Oratory", "����������"}},
	{{"Gambling", "�������� ����"}},
	{{"Quack", "������������"}},
	{{"Shadowing", "������"}},
	{{"Stealth", "����������"}},
	{{"Diagnosis", "�������"}},
	{{"First aid", "������ ������"}},
	{{"First aid", "������ �����"}},
	{{"Skinning", "����������"}},
	{{"Survival", "���������"}},
	{{"Tracking", "������ ������"}},
	{{"Trail signs", "������ ������"}},
	{{"Traps", "�������"}},
	{{"Blacksmith", "������"}},
	{{"Butcher", "������"}},
	{{"Cooking", "�����"}},
	{{"Fletcher", "���������"}},
	{{"Furrier", "�������"}},
	{{"Innkeeper", "����������"}},
	{{"Jeweler", "������"}},
	{{"Miller", "�������"}},
	{{"Potter", "������"}},
	{{"Acting", "���� ����"}},
	{{"Balance", "����������"}},
	{{"Climbing", "�������"}},
	{{"Knotwork", "����"}},
	{{"Rigging", "�������"}},
	{{"History", "�������"}},
	{{"Mathematics", "����������"}},
	{{"Philosophy", "���������"}},
	{{"Research", "������������"}},
	{{"Menital task", "������������ ������"}},
	{{"Unobrusive", "������������"}},
	{{"Socializing", "�������"}},
	{{"Street navigation", "������� ���������"}},
	{{"Attack (bow)", "����� (���)"}},
	{{"Footwork", "������ ���"}},
	{{"Sprinting", "���������"}},
	{{"Throwing", "�������"}},
	{{"Parry (buckler)", "���������� (���)"}},
	{{"Strategy", "���������"}},
	{{"Tactics", "�������"}},
	{{"Attack (�rossbow)", "����� (�������)"}},
	{{"Attack (dirty fighting)", "����� (������� ���)"}},
	{{"Attack (fencing)", "����� (����������)"}},
	{{"Parry (fencing)", "���������� (����������)"}},
	{{"Attack (firearms)", "����� (������������� ������)"}},
	{{"Attack (heavy weapon)", "����� (������� ������)"}},
	{{"Parry (heavy weapon)", "���������� (������� ������)"}},
	{{"Attack (knife)", "����� (���)"}},
	{{"Parry (knife)", "���������� (���)"}},
	{{"Attack (panzerhand)", "����� (����������)"}},
	{{"Parry (panzerhand)", "���������� (����������)"}},
	{{"Attack (polearm)", "����� (�����)"}},
	{{"Parry (polearm)", "���������� (�����)"}},
	{{"Attack (pugilism)", "����� (�����)"}},
	{{"Jab", "����� ������"}},
	{{"Ride", "���� ������"}},
	{{"Grapple", "������"}},
	// Advanced knacks
	{{"Diplomacy", "����������"}},
	{{"Gaming", "����"}},
	{{"Gossip", "�����"}},
	{{"Lip reading", "������ �� �����"}},
	{{"Mooch", "��������������"}},
	{{"Politics", "��������"}},
	{{"Scheming", "�������"}},
	{{"Sedution", "�����������"}},
	{{"Sincerity", "�����������"}},
	{{"Ambush", "������"}},
	{{"Cheating", "���������"}},
	{{"Lockpicking", "����� ������"}},
	{{"Pickpocket", "��������� �����"}},
	{{"Prestidigitation", "������"}},
	{{"Scrounging", "������ ������"}},
	{{"Dentist", "�������"}},
	{{"Examiner", "������������"}},
	{{"Surgery", "��������"}},
	{{"Veterinarian", "���������"}},
	{{"Animal Training", "����������� ��������"}},
	{{"Accounting", "�����������"}},
	{{"Appraising", "������"}},
	{{"Bartending", "����������"}},
	{{"Haggling", "�����������"}},
	{{"Circus", "������"}},
	{{"Cold Read", "����������� ��������"}},
	{{"Disguise", "����������"}},
	{{"Storytelling", "����������"}},
	{{"Cartography", "�����������"}},
	{{"Leaping", "������"}},
	{{"Navigation", "���������"}},
	{{"Pilot", "���������������"}},
	{{"Sea lore", "������ ����"}},
	{{"Swimming", "��������"}},
	{{"Weather", "����������� ������"}},
	{{"Astronomy", "����������"}},
	{{"Law", "�����"}},
	{{"Natural Philosophy", "����������� ���������"}},
	{{"Occult", "���������"}},
	{{"Theology", "��������"}},
	{{"Drive �arriage", "���������� �������"}},
	{{"Seneschal", "��������"}},
	{{"Valet", "����������"}},
	{{"Bribery", "������"}},
	{{"Conceal", "������ �������"}},
	{{"Cryptography", "����������"}},
	{{"Forgery", "��������"}},
	{{"Hand Signs", "���� ������"}},
	{{"Interrogation", "������"}},
	{{"Poison", "��"}},
	{{"Shopping", "������ ���������"}},
	{{"Underworld Lore", "������ ���"}},
	{{"Horse Archery", "�������� � ����"}},
	{{"Trick Shooting", "�������� ��������"}},
	{{"Snapshot", "������� ���������"}},
	{{"Break Fall", "������ �������"}},
	{{"Long-distance Running", "��� �� ������� ���������"}},
	{{"Lifting", "�������� ��������"}},
	{{"Rolling", "�������������"}},
	{{"Swinging", "����� �� ��������"}},
	{{"Side-step", "����� �����"}},
	{{"Attack (Buckler)", "����� (���)"}},
	{{"Artillery", "���������"}},
	{{"Gunnery", "�����"}},
	{{"Incitation", "�������������"}},
	{{"Leadership", "���������"}},
	{{"Logistic", "���������"}},
	{{"Reload (Crossbow)", "����������� (�������)"}},
	{{"Attack (Improvised Weapon)", "����� (����������������� ������)"}},
	{{"Eye Gouge", "���� � ����"}},
	{{"Kick", "�����"}},
	{{"Parry (Improvised Weapon)", "����������� (����������������� ������)"}},
	{{"Throat Strike", "���� � �����"}},
	{{"Throw (Improvised Weapon)", "������� (����������������� ������)"}},
	{{"Reload (Firearms)", "����������� (������������� ������)"}},
	{{"Throw (Knife)", "������� (���)"}},
	{{"Uppercut", "��������"}},
	{{"Set Defence", "�������� ������"}},
	{{"Ear Clap", "������ �� ����"}},
	{{"Mounting", "����������� � �����"}},
	{{"Trick Riding", "�������� ����"}},
	{{"Bear Hug", "��������"}},
	{{"Break", "������� ������"}},
	{{"Escape", "���� �� �������"}},
	{{"Head Butt", "���� �������"}},
	// ����� ���� ����������
	{{"Beat", "������ ����"}},
	{{"Bind", "������ ������"}},
	{{"Corpse-a-Corpse", "������� ���"}},
	{{"Disarm", "��������������"}},
	{{"Double parry", "������� �����������"}},
	{{"Feint", "����"}},
	{{"Lunge", "����������� �����"}},
	{{"Pommel strike", "���� ������"}},
	{{"Riposte", "�������� ����"}},
	{{"Togging", "����� �����"}},
	{{"Find weakness", "����� ���������"}},
	// Glamour
	{{"The Green Man", "������� �������"}},
	{{"The Honored Hunter", "������� �������"}},
	{{"Jack", "����"}},
	{{"The Robin Good Fellow", "����� - ������ ����"}},
	{{"Thomas", "�����"}},
	// Laerdom
	{{"Anger", "����"}},
	{{"Calm", "�����������"}},
	{{"Empathy", "�������������"}},
	{{"Flesh", "�����"}},
	{{"Fury", "������"}},
	{{"Gateway", "�����"}},
	{{"Gloom", "����"}},
	{{"Greatness", "�������"}},
	{{"Harvest", "������"}},
	{{"Hatred", "���������"}},
	{{"Intensity", "�������������"}},
	{{"Journey", "����������"}},
	{{"Mountain", "����"}},
	{{"Mystery", "�����"}},
	{{"Omen", "��������"}},
	{{"Passion", "�������"}},
	{{"Ruin", "�����"}},
	{{"Skill", "������"}},
	{{"Solitude", "�����������"}},
	{{"Strength", "����"}},
	{{"Unbound", "�������"}},
	{{"Warrior", "����"}},
	{{"Wealth", "���������"}},
	{{"Wholeness", "�����������"}},
	// Porte
	{{"Attunement", "���������"}},
	{{"Blooding", "�������� �����"}},
	{{"Bring", "������������"}},
	{{"Pocket", "������"}},
	{{"Walk", "������"}},
	// Pyeryem
	{{"Speak", "��������"}},
	{{"Man", "�������"}},
	{{"Cat", "���"}},
	{{"Goshawk", "����������"}},
	{{"Bear", "�������"}},
	{{"Mouse", "����"}},
	{{"Otter", "�����"}},
	{{"Owl", "����"}},
	{{"Rabbit", "������"}},
	{{"Fox", "����"}},
	{{"Leopard", "�������"}},
	{{"Wolf", "����"}},
	// Sorte
	{{"Arcana", "�����"}},
	{{"Coins", "������"}},
	{{"Cups", "����"}},
	{{"Staves", "������"}},
	{{"Swords", "����"}},
};
assert_enum(knack, LastSorte);
getstr_enum(knack);