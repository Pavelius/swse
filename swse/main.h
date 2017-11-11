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
#define lenghtof(t) (sizeof(t)/sizeof(t[0]))

enum ability_s : char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma
};
enum class_s : char {
	Jedi, Noble, Scoundrel, Scout, Soldier, NonHero, Beast,
};
enum specie_s : char {
	NoSpecies,
	Human, Bothan, Cerean, Duros, Ewoks, Gammorean, Gungans, Ithorians,
	KelDor, MonCalamari, Quarren, Rodians, Sullustans, Txrandoshans, Twileks, Zabrak,
	Wookie,
	FirstSpecies = Human, LastSpecies = Wookie
};
enum talent_s : char {
	General, Skills, RacialFeat,
	JediConsular, JediGuardian, JediSentinel, LightsaberCombat,
	Influence, Inspiration, Leadership, Lineage,
};
enum feat_s : unsigned short {
	// Jedi
	AdeptNegotiator, ForcePersuasion, MasterNegotiator, SkilledAdvisor,
	AcrobaticRecovery, BattleMeditation, ElusiveTarget, ForceIntuition, Resilience,
	ClearMind, DarkSideSence, DarkSideScourge, ForceHaze, ResistDarkSide,
	Block, Deflect, LightsaberDefence, LightsaberDefenceII, LightsaberDefenceIII, WeaponSpecializationLightsaber, LightSaberThrow, RedirectShot,
	// Noble
	Presence, DemandSurrender, ImprovedWeakenResolve, WeakenResolve,
	BolsterAlly, IgniteFerver, InspireConfidence, InspireHaste, InspireZeal,
	BornLeader, Coordinate, DistantCommand, FearlessLeader, Rally, Trust,
	Connections, Educated, SpontaneousSkill, Wealth,
	// General Feats
	AcrobaticStrike, ArmourProficienceLight, ArmourProficienceMedium, ArmourProficienceHeavy,
	BanthaRush, BurstFire, CarefulShoot, ChargingFire,
	Cleave, CombatReflexes, CoordinatedAttack, Crush, CyberneticSurgery,
	Deadeye, Dodge, DoubleAttack, DreadfulRage, DualWeaponMastery,
	ExtraRage, ExtraSecondWind,
	FarShoot, ForceBoon, ForceSensitivity, ForceTraining,
	ImprovedCharge, ImprovedDefences, ImprovedDisarm, ImprovedDamageThreshold, Linguist,
	MartialArts, MeleeDefence, MightySwing,
	Mobility, Pin, PointBlankShoot, PowerAttack, PowerfulCharge,
	PreciseShoot, QuickDraw, RapidShoot, RapidStrike, RunningAttack,
	ShakeItOff,
	Sniper,
	SkillFocusAcrobatic, SkillFocusClimb, SkillFocusDeception, SkillFocusEndurance, SkillFocusGatherInformation,
	SkillFocusInitiative, SkillFocusJump, SkillFocusBuerocracy, SkillFocusGalacticLore, SkillFocusLifeSciences,
	SkillFocusPhysicalSciences, SkillFocusSocialSciences, SkillFocusTactics, SkillFocusTechnology, SkillFocusMechanics,
	SkillFocusPerception, SkillFocusPersuasion, SkillFocusPilot, SkillFocusRide, SkillFocusStealth,
	SkillFocusSurvival, SkillFocusSwim, SkillFocusTreatInjury, SkillFocusUseComputer, SkillFocusUseForce,
	StrongInTheForce,
	SurgicalExpertise, Throw, Toughness, Trip, TripleAttack,
	TripleCrit, VehicularCombat, WeaponFiness,
	WeaponProficiencyAdvancedMeleeWeapons, WeaponProficiencyExoticWeapons,
	WeaponProficiencyHeavyWeapons, WeaponProficiencyLightsabers, WeaponProficiencyPistols,
	WeaponProficiencyRifles, WeaponProficiencySimpleWeapons,
	WhirlwindAttack,
	Acrobatic, Climb, Deception, Endurance, GatherInformation,
	Initiative, Jump, Buerocracy, GalacticLore, LifeSciences,
	PhysicalSciences, SocialSciences, Tactics, Technology, Mechanics,
	Perception, Persuasion, Pilot, Ride, Stealth,
	Survival, Swim, TreatInjury, UseComputer, UseForce,
	FirstSkill = Acrobatic, LastSkill = UseForce,
	// Races feats
	Primitive, LowlightVision, Darkvision,
	ExpertSwimmer, ExpertPilot, ExpertClimber, Sneaky, SurvivalInstinct, IntuitiveInitiative, KeenForceSence, HeightenAwareness, Deceptive, ExtraordinaryRecuperation,
	HoldBreath, BreathUnderwater, Bellow, LimbRegeneration, NaturalArmour,
	IronWill, GreatFortitude, LightingReflexes, SuperiorDefences,
	Rage, Scent,
	FirstFeat = AdeptNegotiator, LastFeat = Scent,
};
enum gender_s : unsigned char {
	Male, Female,
};
enum morph_s : unsigned char {
	Masculine, Feminine, Neuter
};
enum defence_s : unsigned char {
	Reflexes, Fortitude, Will
};
enum item_s : unsigned char {
	NoItem,
	Vibrodagger, Vibroblade, Vibrobayonet, ForcePike, Electrostaff, VibroAxe, Atlati, Amphistaff, Cesta,
	LightSaberShort, LightSaber, LightSaberDouble,
	Knife, Club, StunBatton, Mace, Spear, Bayonet, QuaterStaff, GlovesSmall, GlovesMedium,
	FlameThrower, BowCaster, // Exotic Ranged
	GrenadeLauncher, BlasterHeavyRepeating, BlasterCannon, MissileLauncher, BlasterEWebRepeating, // Heavy weapon
	BlasterPistolHoldOut, BlasterPistol, BlasterPistolSport, IonPistol, SlugthrowerPistol, BlasterPistolHeavy, // Pistols
	BlasterCarbine, BlasterRifle, BlasterRifleSport, IonRifle, SlugthrowerRifle, BlasterLightReapeating, BlasterRifleHeavy, // Rifles
	EnegryBall, GrenadeFrag, GrenadeIon, GrenadeStun, ThermalDetonator,
	Sling, Bow, Net, // Simple ranged
	ExplosiveCharge, Detonite, // Explosives
	BlastHelmetAndVest, FlightSuitPadded, CombatJumpSuit, FlightSuitArmored, VonduunCrabshell, StormtrooperArmour,
	CeremonialArmour, CorelianPowerSuit, BattleArmour,
	ArmouredSpacesuit, BattleArmourHeavy,
	PortableComputer, CodeCylinder, CreditChip, Holoprojector, DataCard, DataPad,
	Electrobinocular, GlowRod, FusionLatern, AudioRecorder, HoloRecorder, VideoRecorder, SensorPack,
	Comlink, PocketScrambler, VoxBox,
};
enum wear_s : unsigned char {
	MeleeWeapon, RangedWeapon, ThrownWeapon, Armor, Equipment,
};
enum side_s : unsigned char {
	PartySide, EnemySide,
};
typedef adat<feat_s, 8>				feata;
typedef adat<struct creature*, 64>	creaturea;
struct item
{
	item_s					type;
	operator bool() const { return type != NoItem; }
	int						getreflexes() const;
	const dice&				getdice() const;
};
struct location
{
	struct scene
	{
		char				size;
		const char*			description[2];
	};
	struct place
	{
		struct scenery*		type;
		unsigned short		flags;
		const char*			getname() const;
		const char*			getnameto() const;
	};
	scene*					type;
	place					places[4];
	//
	void					acting();
	void					clear();
	void					create();
	void					getdescription(char* result, struct creature** source, unsigned source_index);
};
struct attackinfo
{
	char					bonus;
	dice					damage;
	char					critical_range;
	char					critical_multiply;
};
struct creature
{
	item					wears[Armor + 1];
	item					gears[8];
	operator bool() const { return specie != NoSpecies; }
	void					attack(wear_s id, creature* enemy, bool interactive);
	void					combatactions(creaturea& enemies, bool interactive);
	static creature*		create(bool interactive = false, bool setplayer = false);
	static creature*		create(specie_s specie, gender_s gender, class_s cls, bool interactive, bool setplayer);
	void					damage(int count, bool interactive);
	int						get(feat_s id) const;
	int						get(class_s id) const { return classes[id]; }
	int						get(defence_s id) const;
	const char*				getA() const { return gender == Female ? "а" : ""; }
	bool					getattackinfo(wear_s id, attackinfo& e) const;
	int						getbaseattack() const;
	int						getbonus(ability_s id) const;
	void					getenemies(creaturea& result, const creaturea& source) const;
	int						getheroiclevel() const;
	const char*				getname() const { return "ѕитер"; }
	int						getinitiative() const { return initiative; }
	side_s					getside() const { return side; }
	bool					is(feat_s id) const;
	bool					isactive() const;
	bool					isclass(feat_s id) const;
	void					remove(feat_s id);
	int						roll(feat_s id, int dc = 0, bool interactive = true) const;
	int						roll(int bonus, int dc, bool interactive, int* dice_rolled) const;
	void					rollinitiative();
	void					set(class_s id, bool interactive = true);
	void					set(feat_s id, bool interactive = true);
	void					set(gender_s id);
	void					set(specie_s id);
	void					set(side_s id);
private:
	char					abilities[6];
	char					classes[Beast + 1];
	unsigned char			feats[LastFeat / 8 + 1];
	gender_s				gender;
	specie_s				specie;
	short					hits;
	char					initiative;
	side_s					side;
	//
	void					chooseabilities(bool interactive);
	static class_s			chooseclass(bool interactive);
	static gender_s			choosegender(bool interactive);
	void					chooseskill(bool interactive, int count);
	static specie_s			choosespecie(bool interactive);
	int						getskills() const;
};
namespace game
{
	void					combat(bool interactive);
	ability_s 				getability(feat_s id);
	int						getskillpoints(class_s id);
}
extern adat<creature, 512>	creatures;
extern creature*			players[6];
feata&						getfeats(class_s id);