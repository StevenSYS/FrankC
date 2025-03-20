cmake_minimum_required(VERSION 3.25)
set(PROGRAM_NAME "FrankC")

project(FrankC LANGUAGES C VERSION 1.1)

option(BUILD_FOR_DOS "Builds ${PROGRAM_NAME} for DOS using DJGPP" off)
option(BUILD_FOR_OLDWIN "Builds ${PROGRAM_NAME} using msvcrt20" off)
option(BUILD_SHARED_LIBS "Builds shared version of libFrank" off)

if(BUILD_FOR_DOS)
	set(CMAKE_C_COMPILER "i586-pc-msdosdjgpp-gcc")
	set(CMAKE_CXX_COMPILER "i586-pc-msdosdjgpp-g++")
elseif(BUILD_FOR_OLDWIN)
	set(CMAKE_C_FLAGS "-mcrtdll=msvcrt20 -march=i586")
endif()

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-s -O2")

file(GLOB SOURCE_FILES "src/*.c")

if(BUILD_SHARED_LIBS)
	add_library(Frank SHARED src/libFrank/frank.c)
else()
	add_library(Frank STATIC src/libFrank/frank.c)
endif()

configure_file(src/progInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/progInfo.h @ONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Frank)
if(BUILD_FOR_DOS)
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
endif()
target_include_directories(${PROJECT_NAME} PRIVATE src/)