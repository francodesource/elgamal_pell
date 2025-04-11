cmake_minimum_required(VERSION 3.31)
project(elgamal_piso C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3")

add_executable(elgamal_piso main.c)
target_link_libraries(elgamal_piso gmp)