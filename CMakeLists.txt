cmake_minimum_required(VERSION 3.31)
project(elgamal_piso C)
include(CTest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3")

file(GLOB SOURCES  "src/*.c")
file(GLOB RES  "results/*.c")
add_executable(elgamal_piso main.c ${SOURCES} ${RES})
add_executable(tests test.c ${SOURCES} ${RES})
add_executable(benchmarks benchmarks.c ${SOURCES} ${RES})

target_link_libraries(elgamal_piso gmp)
target_link_libraries(tests gmp)
target_link_libraries(benchmarks gmp)

# test suite
# unknown sizes
add_test(NAME testGenEncDec128 COMMAND tests 128 1000)
add_test(NAME testGenEncDec256 COMMAND tests 256 1000)

# known sizes
add_test(NAME testGenEncDec512 COMMAND tests 512 1000)
add_test(NAME testGenEncDec1024 COMMAND tests 1024 1000)
add_test(NAME testGenEncDec1536 COMMAND tests 1536 100)
add_test(NAME testGenEncDec3840 COMMAND tests 3840 100)
add_test(NAME testGenEncDec7680 COMMAND tests 7680 10)
