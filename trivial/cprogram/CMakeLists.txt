set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_BASE}/cprogram)

link_libraries(m)

add_executable(reverse_words reverse_words.c)
add_executable(min_common_value min_common_value.c)
add_executable(bookshop bookshop.c)
