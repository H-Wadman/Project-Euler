cmake_minimum_required(VERSION 3.28)
project(pe22 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if (NOT (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_compile_options(-g -Wall -Wextra -Werror -fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
    set(DOCTEST_CONFIG "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
else ()
    set(DOCTEST_CONFIG "DOCTEST_CONFIG_DISABLE")
endif ()

configure_file(doctestconfig.in doctestconfig.hpp)

# Libraries for main

add_executable(main main.cpp)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR} "/opt/homebrew/include/")

find_library(PRIMESIEVE NAMES primesieve libprimesieve libprimesieve-dev)
target_link_libraries(main PRIVATE ${PRIMESIEVE})
