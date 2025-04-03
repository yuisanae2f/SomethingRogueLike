cmake_minimum_required(VERSION 3.10)
include(./_.cmake)

ae2f_CoreLibFetch(ae2f Core main)

project(idk LANGUAGES C CXX)

set(STR_MAX 	16)			# max string
set(STRLONG_MAX	64)			# max string (long)
set(STR_CHAR_T	"char")			# char type
set(STAT_INT_T 	"unsigned short")	# int type for stat
set(STAT_MAX	1024)			# max for each stat

set(INV_MAX		3)
set(INVC_T		"unsigned char")
set(INV_ITEM_MAX	3)
set(INV_ITEMC_T		"unsigned char")
set(SKILL_MAX		3)
set(SKILLC_T		"unsigned char")

# Battle Fighter Max Count
set(BATTLE_FIGHTER_MAX 3)

# Battle Fighter Counter Type
set(BATTLE_FIGHTERC_T "unsigned char")

# Battle Max Team Count
set(BATTLE_TEAM_MAX 2)

# Battle Team Count Type
set(BATTLE_TEAMC_T "unsigned char")

# str.h
configure_file(
	"${PROJECT_SOURCE_DIR}/auto/str.h"
	"${PROJECT_SOURCE_DIR}/include/str.auto.h"
)

# stat.h
configure_file(
	"${PROJECT_SOURCE_DIR}/auto/stat.h"
	"${PROJECT_SOURCE_DIR}/include/stat.auto.h"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/auto/battle.h"
	"${PROJECT_SOURCE_DIR}/include/battle.auto.h"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/auto/skill.h"
	"${PROJECT_SOURCE_DIR}/include/skill.auto.h"
)

configure_file(
	"${PROJECT_SOURCE_DIR}/auto/inv.h"
	"${PROJECT_SOURCE_DIR}/include/inv.auto.h"
)



add_library(
	_INTERFACE
	INTERFACE
	"include/unit.h"
	"include/ArrLike.h"

	"auto/str.h"
	"include/str.auto.h"
	"include/str.h"

	"auto/stat.h"
	"include/stat.auto.h"
	"include/stat.h"

	"auto/battle.h"
	"include/battle.auto.h"
	"include/battle.h"

	"auto/skill.h"
	"include/skill.auto.h"
	"include/skill.h"

	"auto/inv.h"
	"include/inv.auto.h"
	"include/inv.h"
)

target_link_libraries(_INTERFACE INTERFACE Core)
target_include_directories(_INTERFACE INTERFACE "include")

add_library(
	_LIB INTERFACE
)


target_link_libraries(
	_LIB INTERFACE 
	_INTERFACE
)

add_executable(
	_BIN
	"source/main.c"
)

target_link_libraries(
	_BIN 
	PRIVATE 
	_LIB
)
