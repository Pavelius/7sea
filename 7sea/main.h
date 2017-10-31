#include "adat.h"
#include "crt.h"
#include "dice.h"
#include "logs.h"

#pragma once

#define assert_enum(name, last) static_assert(sizeof(name##_data) / sizeof(name##_data[0]) == last + 1,\
	"Invalid count of " #name " elements")
#define getstr_enum(ename) template<> const char* getstr<ename##_s>(ename##_s value) { return ename##_data[value].name[1]; }
#define maptbl(t, id) (t[imax(0, imin(id, (int)(sizeof(t)/sizeof(t[0]))))])

enum trait_s : unsigned char {
	Brawn, Finesse, Resolve, Wits, Panache,
	FirstTrait = Brawn, LastTrait = Panache,
};
enum skill_s : unsigned char {
	Artist, Courtier, Criminal, Doctor, Hunter, Merchant, Performer, Sailor, Scholar, Servant, Spy, Streetwise,
	Archer, Athlete, Buckler, Commander, Crossbow, DirtyFighting, Fencing,
	Firearms, HeavyWeapon, Knife, PanzerhandSkill, Polearm, Pugilism, Rider, Wrestling,
};
enum advantage_s : unsigned char {
	AbleDrinker, Academy, Appearance, CastilliansEducation,
	Citation, Connections, CombatReflexes, Commissions,
	DangerousBeauty, DracheneisenNoble, Faith, FoulWeatherJack,
	IndomitableWill, Inheritance, KeenSences,
	Large, LeftHanded, LegendaryFiness, Linguist,
	MembershipTradeGuild, Noble, Ordained, Patron, Scoundrel, Servants, Small,
	Toughness, University,
	FirstAdvantage = AbleDrinker, LastAdvantage = University,
};
enum knack_s : unsigned char {
	Composer, Drawing, Musician, Sculpting, Singing, Writing,
	Dancing, Etiquette, Fashion, Oratory,
	Gambling, Quack, Shadowing, Stealth,
	Diagnosis, FirstAid,
	Fishing, Skinning, Survival, Tracking, TrailSigns, Traps,
	Blacksmith, Butcher, Cooking, Fletcher, Furrier, Glassblower, Innkeeper, Jeweler, Potter,
	Acting,
	Balance, Climbing, Knotwork, Rigging,
	History, Mathematics, Philosophy, Research,
	MenitalTask, Unobrusive,
	Socializing, StreetNavigation,
	AttackBow,
	Footwork, Sprinting, Throwing,
	ParryBuckler,
	Strategy, Tactics,
	AttackCrossbow,
	AttackDirtyFighting,
	AttackFencing, ParryFencing,
	AttackFirearms,
	AttackHeavyWeapon, ParryHeavyWeapon,
	AttackKnife, ParryKnife,
	AttackPanzerhand, ParryPanzerhand,
	AttackPolearm, ParryPolearm,
	AttackPugilism, Jab,
	Ride,
	Grapple,
	FirstKnack = Composer, LastKnack = Grapple,
	// Advenced knacks
	Diplomacy, Gaming, Gossip, LipReading, Mooch, Politics, Scheming, Sedution, Sincerity,
	Ambush, Cheating, Lockpicking, Pickpocket, Prestidigitation, Scrounging,
	Dentist, Examiner, Surgery, Veterinarian,
	AnimalTraining,
	Accounting, Appraising, Bartending, Haggling,
	Circus, ColdRead, Disguise, Storytelling,
	Cartography, Leaping, Navigation, Pilot, SeaLore, Swimming, Weather,
	Astronomy, Law, NaturalPhilosophy, Occult, Theology,
	DriveCarriage, Seneschal, Valet,
	Bribery, Conceal, Cryptography, Forgery, HandSigns, Interrogation, Poison,
	Shopping, UnderworldLore,
	HorseArchery, Snapshot, TrickShooting,
	BreakFall, LongDistanceRunning, Lifting, Rolling, Swinging, SideStep,
	AttackBuckler,
	Artillery, Gunnery, Incitation, Leadership, Logistic,
	ReloadCrossbow,
	AttackImprovisedWeapon, EyeGouge, Kick, ParryImprovisedWeapon, ThroatStrike, ThrowImprovisedWeapon,
	ReloadFirearms,
	ThrowKnife,
	Uppercut,
	SetDefence,
	EarClap,
	Mounting, TrickRiding,
	BearHug, Break, Escape, HeadButt,
	FirstAdvancedKnack = Diplomacy, LastAdvancedKnack = HeadButt,
	// Swordsman's knacks
	Beat, Bind, CorpseACorpse, Disarm, DoubleParry,
	Feint, Lunge, PommelStrike, Riposte, Togging, FindWeakness,
	FirstSwordsmansKnack = Beat, LastSwordsmansKnack = FindWeakness,
	// Glamour knacks
	GlamourGreenMan, GlamourHonoredHunter, GlamourJack, GlamourRobinGoodFellow, GlamourThomas,
	FirstGlamour = GlamourGreenMan, LastGlamour = GlamourThomas,
	// Laerdom knacks
	LaerdomAnger, LaerdomCalm, LaerdomEmpathy, LaerdomFlesh, LaerdomFury,
	LaerdomGateway, LaerdomGloom, LaerdomGreatness, LaerdomHarvest, LaerdomHatred,
	LaerdomIntensity, LaerdomJourney, LaerdomMountain, LaerdomMystery, LaerdomOmen,
	LaerdomPassion, LaerdomRuin, LaerdomSkill, LaerdomSolitude, LaerdomStrength,
	LaerdomUnbound, LaerdomWarrior, LaerdomWealth, LaerdomWholeness,
	FirstLaerdom = LaerdomAnger, LastLaerdom = LaerdomWholeness,
	// Porte knacks
	PorteAttunement, PorteBlooding, PorteBring, PortePocket, PorteWalk,
	FirstPorte = PorteAttunement, LastPorte = PorteWalk,
	// Pyeryem knacks
	PyeryemSpeak, PyeryemMan, PyeryemCat, PyeryemGoshawk, PyeryemBear, PyeryemMouse,
	PyeryemOtter, PyeryemOwl, PyeryemRabbit, PyeryemFox, PyeryemLeopard, PyeryemWolf,
	FirstPyeryem = PyeryemSpeak, LastPyeryem = PyeryemWolf,
	// Sorte knacks
	SorteArcana, SorteCoins, SorteCups, SorteStaves, SorteSwords,
	FirstSorte = SorteArcana, LastSorte = SorteSwords,
	FirstSorceryKnack = FirstGlamour, LastSorceryKnack = LastSorte,
};
enum background_s : unsigned char {
	Amnesia, Cursed, Debt, Defeated, Fear, Hunted, Hunting, LostLove, MistakenIdentify,
	Nemesis, Obligation, Rivalry, Romance, TrueIdentify, Vendetta, Vow,
	FirstBackground = Amnesia, LastBackground = Vow,
};
enum sorcery_s : unsigned char {
	Glamour, Porte, Pyeryem, Laerdom, Sorte,
	FirstSorcery = Glamour, LastSorcery = Sorte,
};
enum ship_s : unsigned char {
	Sloop, Caravela, Frigata, Galeon, Linkor,
	FirstShipType = Sloop, LastShipType = Linkor,
};
enum cargo_s : unsigned char {
	Woods, Ore, Glass, Paper, Leather, Iron, Gold,
	FirstMaterial = Woods, LastMaterial = Gold,
};
enum modification_s : unsigned char {
	HiddenTowline, Oars, ProwRam, ReinforcedMasts,
	ConcealedGunports, Overgunned, SilkSails, SturdyHull, WellTrainedCrew, WideRudder,
	Decoration, ExtendedKeel, Lucky, SmugglingCompartments,
	ExtraCargoSpace, ExtraCrewQuarters, GoodCaptain, NarrowHull,
	BoardingParty, ExtraBoardingGuns, FriendlySpirit, SlightDraft, SwivelCannon,
	FirstModifications = HiddenTowline, LastModifications = SwivelCannon,
	FlimsyMasts, Old, Sluggish,
	BrittleHull, LeakyHull, PoorlyTrainedCrew, SmallKeel, SmallRudder, TatteredSails, Undergunned,
	FirstFlaws = FlimsyMasts, LastFlaws = Undergunned,
};
enum location_s : unsigned char {
	CitySanFeodoro, CityFalconsPoint, CitySanAugustin, CityLaReinaDelMar, CitySanJuan,
	CityLaBucca,
	CitySanFelipe, CityRioja, CityAvila, CitySanEliseo, CityPuertoDeSur, CityLaPasiego, CityTarango,
	CitySanCristobal, CitySanGustavo,
	CityVaticin,
	FirstCity = CitySanFeodoro, LastCity = CityVaticin,
};
enum nation_s : unsigned char {
	Avalon, Castille, Eisen, Montaigne, Ussura, Vendel, Vodacce,
	FirstNation = Avalon, LastNation = Vodacce,
	Crescent, HightEisen, Teodoran, Thean,
	FirstLanguage = Avalon, LastLanguage = Thean,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum swordsman_s : unsigned char {
	Aldana, Donowan, Eisenfaust, Valroux, Leegstra, Ambrogia,
	FirstSwordsmansSchool = Aldana, LastSwordsmansSchool = Ambrogia,
};
enum family_s : unsigned char {
	NoFamily,
	Gaegos, Ochoa, Ordunio, Sandoval, Soldano, Torres, Zepeda,
	Asedo, Arsingierro, Avilla, Beharanno, Garsia, Grihalwa, Gusman, Lopez, Montoya, Nunyes, Ontiveros, Ramirez, Rioha, Rios, Rivera, Rodriges, Vaskes, Wellaskes, Yanches,
	AvalonLock, AvalonHood, AvalonGreen, AvalonDoors, AvalonSmith,
	MacAllister, MacDuff, MacBride, MacCordum, MacDonald, MacIchern, MacIntire, MacLaud,
	OBannon, OTool,
	AllaisDuCrieus, DuMontaigne, FlauberDuDore, RicheDuParroise, LevequeDAur,
};
struct hero
{
	nation_s			nation;
	family_s			family;
	gender_s			gender;
	short				experience;
	operator bool() const { return traits[0]!=0; }
	void				chooseadvantage(bool interactive);
	void				choosetraits(bool interactive);
	void				clear();
	const char*			getname() const { return "Óëüðèê"; }
	int					get(advantage_s id) const { return advantages[id]; }
	int					get(trait_s id) const { return traits[id]; }
	int					get(knack_s id) const { return knacks[id]; }
	int					getcost(advantage_s id, int level) const;
	bool				issorcery() const { return sorcery != 0; }
	bool				isswordsman() const { return swordsman != 0; }
private:
	char				swordsman, sorcery;
	char				advantages[LastAdvantage + 1];
	char				traits[LastTrait + 1];
	char				knacks[LastSorte + 1];
};
extern adat<hero, 64>	heroes;
extern hero*			players[6];