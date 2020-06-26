# VECTOR
add_executable(vector_test vector_test.c)
target_link_libraries(vector_test LINK_PUBLIC VECTOR)
add_test(VECTOR vector_test)

# MAP
add_executable(map_test map_test.c)
target_link_libraries(map_test LINK_PUBLIC MAP)
add_test(MAP map_test)

# ALL
add_executable(test_main test_main.c)
target_link_libraries(test_main LINK_PUBLIC VECTOR ASM_INT)

## MAX
add_test(MAX test_main "${CMAKE_SOURCE_DIR}/examples/max.tas" "-100" "123456789")
set_tests_properties(MAX PROPERTIES PASS_REGULAR_EXPRESSION "The greater number is: 123456789\n")

## FIBONACCI
add_test(FIBONACCI test_main "${CMAKE_SOURCE_DIR}/examples/fibonacci.tas" "30" "90" "-1")
set_tests_properties(FIBONACCI PROPERTIES PASS_REGULAR_EXPRESSION "The required Fibonacci number is: 2880067194370816120\n")

## CHANGE_CASE
add_test(CHANGE_CASE test_main "${CMAKE_SOURCE_DIR}/examples/change_case.tas" "1234THISisAtest@#$")
set_tests_properties(CHANGE_CASE PROPERTIES PASS_REGULAR_EXPRESSION "1234thisISaTEST@#\\$\n")

## IS_LEAP
add_test(IS_LEAP test_main "${CMAKE_SOURCE_DIR}/examples/is_leap.tas" "1224" "1900" "2000" "2009" "2020" "-1")
set_tests_properties(IS_LEAP PROPERTIES PASS_REGULAR_EXPRESSION "Insert the year \\(negative to close\\): 1224 is a leap year\\.\nInsert the year \\(negative to close\\): 1900 is not a leap year\\.\nInsert the year \\(negative to close\\): 2000 is a leap year\\.\nInsert the year \\(negative to close\\): 2009 is not a leap year\\.\nInsert the year \\(negative to close\\): 2020 is a leap year\\.\n")
