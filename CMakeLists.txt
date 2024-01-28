cmake_minimum_required(VERSION 3.27)
project(Linal)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)

add_library(Linal STATIC library.cpp)
add_executable(GTest_run test.cpp)
target_link_libraries(GTest_run Linal gtest gtest_main)
target_include_directories(GTest_run PRIVATE ${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
