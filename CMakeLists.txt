cmake_minimum_required (VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")
project(hash_table_lib)

add_subdirectory(main)

enable_testing()
add_subdirectory(test)

