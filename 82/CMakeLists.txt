cmake_minimum_required(VERSION 3.28)
project(euler_81 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if (NOT ("${CMAKE_BUILD_TYPE}" STREQUAL "Release"))
    set(DOCTEST_CONFIG "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
    add_compile_options(-Wall -Wextra -Werror -g -fno-omit-frame-pointer -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
else ()
    set(DOCTEST_CONFIG "DOCTEST_CONFIG_DISABLE")
endif ()

configure_file(doctest_config.in ${CMAKE_SOURCE_DIR}/doctest_config.hpp)

add_executable(main main.cpp)
target_include_directories(main PRIVATE /opt/homebrew/include/doctest/)
