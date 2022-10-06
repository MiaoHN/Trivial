set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/coroutine)

include_directories(source)

add_executable(test_ucontext test/test_ucontext.cpp)

add_executable(test_coroutine test/test_coroutine.cpp source/coroutine.cpp source/scheduler.cpp)