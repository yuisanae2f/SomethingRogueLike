#ifndef Unit_h
#define Unit_h

#include <ae2f/Cast.h>
#include "./str.h"
#include "./stat.h"

typedef struct Unit {
	str_t name;
	strlong_t desc;
	Stat stat;
} Unit;

#endif
