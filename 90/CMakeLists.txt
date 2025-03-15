cmake_minimum_required(VERSION 3.30)
project(pe90 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Wall -Wextra -Werror -g -fsanitize=address,undefined -fno-omit-frame-pointer -ferror-limit=0)
    add_link_options(-fsanitize=address)
    set (DOCTEST_CONFIG "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
else ()
    add_compile_options(-O3)
    set(DOCTEST_CONFIG "DOCTEST_CONFIG_DISABLE")
endif ()

configure_file(cmake_defs.in "${CMAKE_CURRENT_BINARY_DIR}/cmake_defs.hpp")

add_executable(main main.cpp)
target_include_directories(main PRIVATE "/opt/homebrew/include/doctest/" "${CMAKE_BINARY_DIR}")
