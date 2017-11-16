#include "adat.h"
#include "crt.h"
#include "dice.h"
#include "logs.h"

#pragma once

#define assert_enum(name, last) static_assert(sizeof(name##_data) / sizeof(name##_data[0]) == last + 1,\
	"Invalid count of " #name " elements")
#define getstr_enum(ename) template<> const char* getstr<ename##_s>(ename##_s value) { return ename##_data[value].name[1]; }
#define getinf_enum(ename) template<> const char* getinfo<ename##_s>(ename##_s value) { return ename##_data[value].text; }
#define maptbl(t, id) (t[imax(0, imin(id, (int)(sizeof(t)/sizeof(t[0])-1)))])

enum trait_s : unsigned char {
	Brawn, Finesse, Resolve, Wits, Panache,
	FirstTrait = Brawn, LastTrait = Panache,
};
enum skill_s : unsigned char {
	Artist, Courtier, Criminal, Doctor, Hunter, Merchant, Performer, Sailor, Scholar, Servant, Spy, Streetwise,
	Archer, Athlete, Buckler, Commander, Crossbow, DirtyFighting, Fencing,
	Firearms, HeavyWeapon, Knife, PanzerhandSkill, Polearm, Pugilism, Rider, Wrestling,
	FirstSkill = Artist, LastSkill = Wrestling,
};
enum advantage_s : unsigned char {
	AbleDrinker, Academy, Appearance, CastilliansEducation,
	Citation, CombatReflexes, Commissions,
	DangerousBeauty, DracheneisenNoble, FoulWeatherJack,
	IndomitableWill, KeenSences,
	Large, Linguist,
	Noble, Ordained, Scoundrel, Small,
	Toughness, University,
	FirstAdvantage = AbleDrinker, LastAdvantage = University,
};
enum knack_s : unsigned char {
	NoKnack,
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
	NoSorcery,
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
	NoSwordsman,
	Aldana, Ambrogia, Donowan, Eisenfaust, Leegstra, Valroux,
	FirstSwordsmansSchool = Aldana, LastSwordsmansSchool = Valroux,
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
enum side_s : char {
	PartySide, EnemySide,
};
enum dice_s : char {
	DramaDice, ReputationDice, GlamourDice, 
	FirstDice = DramaDice, LastDice = GlamourDice,
};
enum item_s : char {
	NoItem,
	Pistol, Bow, Rapier, Sword, Axe, Spear,
};
struct damageinfo
{
	char				roll;
	char				keep;
};
struct item
{
	item_s				type;
	item() : type(NoItem) {}
	item(item_s type) : type(type) {}
	const damageinfo&	getdamage() const;
};
struct hero
{
	nation_s			nation;
	family_s			family;
	gender_s			gender;
	short				experience;
	//
	operator bool() const { return traits[0]!=0; }
	//
	void				create(bool interactive, bool add_to_players = true);
	void				create(nation_s nation, bool interactive, bool add_to_players);
	bool				contest(bool interactive, trait_s trait, knack_s knack, int bonus, hero* opponent, trait_s opponent_trait, knack_s opponent_knack, int opponent_bonus);
	static void			combat();
	void				clear();
	void				damage(int wounds, bool interactive = true, int drama_per_wounds = 20);
	void				endsession();
	const char*			getname() const { return getname(name); }
	static short unsigned getnamerandom(gender_s gender, nation_s nation);
	static const char*	getname(short unsigned id);
	int					get(advantage_s id) const { return advantages[id]; }
	int					get(dice_s id) const;
	int					get(trait_s id) const { return traits[id]; }
	int					get(knack_s id) const { return knacks[id]; }
	const char*			getA() const { return (gender == Female) ? "а" : "";}
	const char*			getAS() const { return (gender == Female) ? "ась" : "ся"; }
	int					getcost(advantage_s id) const;
	int					getcost(skill_s value) const;
	int					getdramawounds() const { return dramawound; }
	int					getmaxdramawounds() const { return traits[Resolve]*2; }
	sorcery_s			getsorcery() const;
	swordsman_s			getswordsman() const;
	int					getwounds() const { return wounds; }
	static bool			iscivil(skill_s value);
	bool				iscripled() const { return dramawound >= traits[Resolve]; }
	bool				isplayer() const;
	bool				issorcery() const { return sorcery != 0; }
	bool				isswordsman() const { return swordsman != 0; }
	static int			roll(int roll, int keep);
	bool				roll(bool interactive, trait_s trait, knack_s knack, int target_number, int bonus = 0, int* result = 0);
	char*				sayroll(char* temp, trait_s trait, knack_s knack = NoKnack, int target_number = 0) const;
	void				set(knack_s id, int value) { knacks[id] = value; }
	void				setdramawounds(int value) { dramawound = value; }
	void				setwounds(int value) { wounds = value; }
	void				use(dice_s id);
private:
	char				advantages[LastAdvantage + 1];
	char				knacks[LastSorte + 1];
	char				traits[LastTrait + 1];
	unsigned char		dramawound, wounds;
	char				swordsman, sorcery;
	char				dices[LastDice + 1];
	short unsigned		name;
	//
	void				chooseadvantage(bool interactive, char* skills);
	void				choosecivilskills(bool interactive, char* skills);
	void				choosecombatskills(bool interactive, char* skills);
	void				choosegender(bool interactive);
	void				choosenation(bool interactive);
	void				choosesorcery(bool interactive);
	void				choosetraits(bool interactive);
	void				set(advantage_s value, bool interactive, char* skills);
	void				set(nation_s value);
	void				set(skill_s value, bool interactive, char* skills);
	void				set(swordsman_s value, bool interactive, char* skills);
	int					use(int* dices, dice_s id);
};
namespace logs
{
	struct state
	{
		const char*		information;
		state();
		~state();
	};
}
extern adat<hero, 64>	heroes;
extern logs::state		logc;
extern hero*			players[6];
template<class T> const char* getinfo(T e);