cmake_minimum_required(VERSION 3.26)

project(77 VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror -g -fsanitize=address)
    add_link_options(-fsanitize=address)
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-g -O2)
endif()

add_compile_options(-fconstexpr-steps=100000000)

add_executable(${PROJECT_NAME} 77.cpp)

set(MYLIBS "/Users/hannes/Coding/Cpp/myLibs")

find_library(HWUTIL NAMES hwutil PATHS ${MYLIBS}/lib/)
message("hwutil path found: ${HWUTIL}")

target_include_directories(${PROJECT_NAME} PUBLIC
    "/opt/homebrew/Cellar/llvm/17.0.4/include/c++/v1/"
    "${MYLIBS}/include")
