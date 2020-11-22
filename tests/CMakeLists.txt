# add_executable(lite_test1 test_one.cpp)
add_executable(lite_test2 test_two.cpp)
target_link_libraries(lite_test2 hypmath)

add_library(hyptester tester.cpp)
add_subdirectory(unit_tests)
