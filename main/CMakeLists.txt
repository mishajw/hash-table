cmake_minimum_required (VERSION 3.5)
project (hash-table)

include_directories(include)

add_library(hash-table-lib
  src/main.c
  src/table.c
  include/table.h
)

