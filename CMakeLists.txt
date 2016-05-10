cmake_minimum_required (VERSION 3.5)
project (hash-table)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

set(
  SOURCE_FILES
  src/main.c
  src/table.c
)

set(EXECUTABLE_NAME hash-table)

include_directories(include)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

