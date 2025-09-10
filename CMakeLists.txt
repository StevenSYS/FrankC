cmake_minimum_required(VERSION 3.11)

project(FrankC LANGUAGES C VERSION 1.21)

option(BUILD_FOR_DOS "Build ${PROJECT_NAME} for DOS using DJGPP" OFF)
option(BUILD_SHARED_LIBS "Build shared version of libFrank" OFF)
option(BUILD_ONLY_LIBRARY "Build only libFrank" OFF)
option(BUILD_FOR_I586 "Build ${PROJECT_NAME} for i586 (Intel Pentium) or higher" OFF)
# Windows Compiler Options
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Windows Compiler Only)" OFF)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O2")
if (NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

if(BUILD_FOR_I586)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i586 -fcf-protection=none")
endif()

if(BUILD_FOR_DOS)
	set(CMAKE_C_COMPILER "i586-pc-msdosdjgpp-gcc")
elseif(WIN32 AND BUILD_USING_MSVCRT20)
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(NOT WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be compiling for Windows")
endif()

if(NOT BUILD_ONLY_LIBRARY)
	file(GLOB SOURCE_FILES "src/*.c")
endif()

if(BUILD_SHARED_LIBS AND BUILD_FOR_DOS)
	message(FATAL_ERROR "You can't build a shared library when compiling for DOS")
endif()

add_library(Frank src/libFrank/frank.c)

if(NOT BUILD_ONLY_LIBRARY)
	configure_file(src/progInfo.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/progInfo.h @ONLY)
	
	add_executable(${PROJECT_NAME} ${SOURCE_FILES})
	target_link_libraries(${PROJECT_NAME} Frank)
	if(BUILD_FOR_DOS)
		set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
	endif()
	set_property(TARGET ${PROJECT_NAME} PROPERTY BUILD_RPATH ".")
	target_include_directories(${PROJECT_NAME} PRIVATE src/)
endif()