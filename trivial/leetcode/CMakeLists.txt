set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/leetcode)

file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

include_directories(include)

foreach(SOURCE_FILE IN ITEMS ${CPP_SOURCES})
  STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" OUTPUT_NAME ${SOURCE_FILE})
  add_executable(${OUTPUT_NAME} ${SOURCE_FILE})
endforeach()