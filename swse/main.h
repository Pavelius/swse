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

enum feat_s : unsigned short {

};