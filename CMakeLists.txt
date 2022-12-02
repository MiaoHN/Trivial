cmake_minimum_required(VERSION 3.10)

project(Trivial)

enable_testing()

if(WIN32)
	message(STATUS "Now is windows")
elseif(APPLE)
	message(STATUS "Now is Apple systens.")
elseif(UNIX)
	message(STATUS "Now is UNIX-like OS's.")
endif()

set(OUTPUT_BASE ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(trivial)
