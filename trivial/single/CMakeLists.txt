set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/single)

link_libraries(m)

add_executable(zigzag zigzag.cpp)
add_executable(eight_digits eight_digits.c)

if(UNIX)
endif()