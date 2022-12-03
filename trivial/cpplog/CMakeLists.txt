set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/cpplog)
include_directories(source)

file(GLOB CPPLOG_SOURCE "source/*.cpp")

add_executable(test_log test/test_log.cpp ${CPPLOG_SOURCE})
add_test(NAME test_log COMMAND test_log)