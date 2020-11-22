cmake_minimum_required(VERSION 3.17)
project(hypersim)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/hypermath)
include_directories(tests)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(googletest_lib)
# add the lib subdirectories here

# NOTE: FLTK cannot be linked well

target_link_libraries(hypersim hypmath)
