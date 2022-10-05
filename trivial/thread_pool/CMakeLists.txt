set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/thread_pool)

add_executable(test_threadpool source/main.cpp)
target_link_libraries(test_threadpool PUBLIC pthread)
target_include_directories(test_threadpool PUBLIC source)