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
	General, RacialFeat,
	JediConsular, JediGuardian, JediSentinel, LightsaberCombat,
	Influence, Inspiration, Leadership, Lineage,
};
enum skill_s : char {
	Acrobatic, Climb, Deception, Endurance, GatherInformation,
	Initiative, Jump, Buerocracy, GalacticLore, LifeSciences,
	PhysicalSciences, SocialSciences, Tactics, Technology, Mechanics,
	Perception, Persuasion, Pilot, Ride, Stealth,
	Survival, Swim, TreatInjury, UseComputer, UseForce,
	FirstSkill = Acrobatic, LastSkill = UseForce,
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
typedef adat<feat_s, 8>		feata;
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
struct creature
{
	struct location*		location;
	char					index;
	operator bool() const { return specie != NoSpecies; }
	static creature*		create(struct location* pv = 0, bool interactive = false, bool setplayer = false);
	static creature*		create(specie_s specie, gender_s gender, class_s cls, struct location* pv, bool interactive, bool setplayer);
	int						get(class_s id) const { return classes[id]; }
	int						getbonus(ability_s id) const;
	bool					is(feat_s id) const;
	bool					is(skill_s id) const;
	bool					isclass(skill_s id) const;
	void					set(class_s id, bool interactive = true);
	void					set(feat_s id, bool interactive = true);
	void					set(gender_s id);
	void					set(skill_s id, bool value = true);
	void					set(specie_s id);
private:
	char					abilities[6];
	char					classes[Beast + 1];
	unsigned char			feats[LastFeat / 8 + 1];
	unsigned char			skills[LastSkill / 8 + 1];
	gender_s				gender;
	specie_s				specie;
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
	int						getskillpoints(class_s id);
}
extern adat<creature, 512>	creatures;
feata&						getfeats(class_s id);