add_subdirectory(leetcode)
add_subdirectory(json)
add_subdirectory(thread_pool)
add_subdirectory(single)
add_subdirectory(cprogram)

if(UNIX)
  # add_subdirectory(coroutine)
  add_subdirectory(cpplog)
else()
  message(STATUS "coroutine not loaded")
  message(STATUS "cpplog not loaded")
endif()