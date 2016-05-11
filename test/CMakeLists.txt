cmake_minimum_required (VERSION 3.5)
project (hash-table)

include_directories(include)

add_executable(Test src/test.c)

# Check
find_library (CHECK check)
if (CHECK)
  target_link_libraries(Test check)
  message (STATUS "Using Check ${CHECK}")
else()
  message (SEND_ERROR "Check is required")
endif()
