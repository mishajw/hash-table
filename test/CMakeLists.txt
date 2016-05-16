enable_testing()

# check lib
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})

# pthread lib
find_package (Threads)

# Add all libs
set(LIBS ${LIBS} ${CHECK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} hash_table_lib)

include_directories(include, ../main/include)
add_executable(hash_table_test src/test.c)
target_link_libraries(hash_table_test ${LIBS})

add_test(hash_table_test ${CMAKE_CURRENT_BINARY_DIR}/hash_table_test)

