set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/json)

add_executable(test_json test/test.cpp)
target_include_directories(test_json PUBLIC source)