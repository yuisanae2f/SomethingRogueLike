cmake_minimum_required(VERSION 3.10)
include(./_.cmake)

ae2f_CoreLibFetch(ae2f Core main)

project(idk LANGUAGES C CXX)

configure_file(
	"${PROJECT_SOURCE_DIR}/auto/str.h"
	"${PROJECT_SOURCE_DIR}/include/str.auto.h"
)

add_library(
	_INTERFACE
	INTERFACE
	"include/unit.h"
)

target_link_libraries(_INTERFACE INTERFACE Core)

add_library(
	_LIB
	"source/lib.c"
)

target_include_directories(_LIB PUBLIC "include")

find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(
	_LIB PUBLIC 
	OpenGL::OpenGL 
	Vulkan::Vulkan
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
