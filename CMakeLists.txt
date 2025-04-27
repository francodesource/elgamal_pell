cmake_minimum_required(VERSION 3.31)
project(elgamal_piso C)
include(CTest)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3")

# Setting result path
set(RESULT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/results")
add_compile_definitions(RESULT_PATH="${RESULT_PATH}")

file(GLOB SOURCES  "src/*.c")

add_executable(elgamal_piso main.c ${SOURCES})
add_executable(test_piso test/test_piso.c ${SOURCES})
add_executable(test_proj test/test_proj.c ${SOURCES})
add_executable(benchmarks benchmarks.c ${SOURCES})

target_link_libraries(elgamal_piso gmp)
target_link_libraries(test_piso gmp)
target_link_libraries(test_proj gmp)
target_link_libraries(benchmarks gmp)

# test suite

# PROJ
add_test(NAME testProjGED8    COMMAND test_proj 8 10000)
add_test(NAME testProjGED16   COMMAND test_proj 16 10000)
add_test(NAME testProjGED32   COMMAND test_proj 32 10000)
add_test(NAME testProjGED64   COMMAND test_proj 64 10000)
add_test(NAME testProjGED128  COMMAND test_proj 128 1000)
add_test(NAME testProjGED256  COMMAND test_proj 256 1000)
add_test(NAME testProjGED1024 COMMAND test_proj 1024 1000)
add_test(NAME testProjGED1536 COMMAND test_proj 1536 100)
add_test(NAME testProjGED3840 COMMAND test_proj 3840 100)
add_test(NAME testProjGED7680 COMMAND test_proj 7680 10)

# PISO
# unknown sizes
add_test(NAME testPisoGED128 COMMAND tests 128 1000)
add_test(NAME testPisoGED256 COMMAND tests 256 1000)
# known sizes
add_test(NAME testPisoGED512  COMMAND tests 512 1000)
add_test(NAME testPisoGED1024 COMMAND tests 1024 1000)
add_test(NAME testPisoGED1536 COMMAND tests 1536 100)
add_test(NAME testPisoGED3840 COMMAND tests 3840 100)
add_test(NAME testPisoGED7680 COMMAND tests 7680 10)
