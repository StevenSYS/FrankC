cmake_minimum_required(VERSION 3.11)

project(Frank LANGUAGES C VERSION 1.22)

set(
	FRANK_INCLUDE_DIRS
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	PARENT_SCOPE
)

option(BUILD_SHARED_LIBS "Build the libraries as shared libraries" ON)
option(BUILD_FOR_I586 "Build ${PROJECT_NAME} for i586 (Intel Pentium) or higher" OFF)
# Windows Compiler Options
option(BUILD_USING_MSVCRT20 "Build ${PROJECT_NAME} using msvcrt20 (Windows Compiler Only)" OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-O2")
if (NOT CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -s")
endif()

if(BUILD_FOR_I586)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i586 -fcf-protection=none")
endif()

if(WIN32)
	if(BUILD_USING_MSVCRT20)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcrtdll=msvcrt20")
	endif()
elseif(WIN32 AND BUILD_USING_MSVCRT20)
	message(FATAL_ERROR "To build using msvcrt20 you must be using a Windows C compiler")
endif()

file(GLOB LIBFRANK_SOURCE_FILES "src/*.c")
file(GLOB LIBFRANK_HEADER_FILES "src/*.h")

add_library(${PROJECT_NAME} ${LIBFRANK_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
set_target_properties(
	${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER "${LIBFRANK_HEADER_FILES}"
)

install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION "lib"
	PUBLIC_HEADER DESTINATION "include"
)