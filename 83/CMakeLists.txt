cmake_minimum_required(VERSION 3.30)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

project(euler_83 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# add_library(mod_test)
#
# target_sources(mod_test
#     PUBLIC
#         FILE_SET CXX_MODULES FILES
#             mod_test.cppm
# )

find_library(fmt "fmt")

add_executable(solution main.cpp)
target_include_directories(solution PRIVATE "/opt/homebrew/include/")

target_link_libraries(solution PRIVATE "${fmt}")

target_compile_options(solution PRIVATE -Wall -Wextra -fsanitize=address,undefined -fno-omit-frame-pointer -g -fcolor-diagnostics)
target_link_options(solution PRIVATE -fsanitize=address,undefined)
