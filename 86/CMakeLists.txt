cmake_minimum_required(VERSION 3.30)
project(euler_86 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

find_library(fmt "fmt")

add_executable(solution main.cpp)

target_include_directories(solution PRIVATE "/opt/homebrew/include/")
target_link_libraries(solution PRIVATE "${fmt}")

if(NOT CMAKE_BUILD_TYPE STREQUAL "rel")
    target_link_options(solution PRIVATE -fsanitize=address,undefined)
    target_compile_options(solution PRIVATE -Wall -Wextra -g -fsanitize=address,undefined -fno-omit-frame-pointer -fcolor-diagnostics)
else()
    target_compile_options(solution PRIVATE -O3)
endif()
