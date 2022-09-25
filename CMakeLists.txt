cmake_minimum_required(VERSION 3.10)

project(Trivial)

if(WIN32)
  set(PLATFROM_WINDOWS)
	message(STATUS "Now is windows")
elseif(APPLE)
	message(STATUS "Now is Apple systens.")
elseif(UNIX)
  set(PLATFROM_UNIX)
	message(STATUS "Now is UNIX-like OS's.")
endif()

add_subdirectory(trivial)