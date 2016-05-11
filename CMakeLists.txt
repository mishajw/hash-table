cmake_minimum_required (VERSION 3.5)
project (hash-table)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

add_subdirectory(main)

enable_testing()
add_subdirectory(test)

