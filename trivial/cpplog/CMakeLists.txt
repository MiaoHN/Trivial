set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/cpplog)
include_directories(source)
add_executable(test_log test/test_log.cpp source/log.cpp)
add_test(NAME test_log COMMAND test_log)