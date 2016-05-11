cmake_minimum_required (VERSION 3.5)
project (hash-table)

include_directories(include)

add_executable(hash-table
  src/main.c
  src/table.c
  include/table.h
)

