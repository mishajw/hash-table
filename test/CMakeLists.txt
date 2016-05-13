enable_testing()

find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CHECK_LIBRARIES} hash_table_lib)

include_directories(include, ../main/include)
add_executable(hash_table_test src/test.c)
target_link_libraries(hash_table_test ${LIBS})

add_test(hash_table_test ${CMAKE_CURRENT_BINARY_DIR}/hash_table_test)

