cmake_minimum_required(VERSION 3.31)
project(elgamal_piso C)
include(CTest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3")

add_executable(elgamal_piso main.c)
add_executable(tests test.c)



target_link_libraries(tests gmp)

target_link_libraries(elgamal_piso gmp)
set_target_properties(elgamal_piso PROPERTIES UNITY_BUILD ON)

# test suite
add_test(NAME testGenEncDec512 COMMAND tests 512 100)