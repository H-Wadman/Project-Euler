cmake_minimum_required(VERSION 3.26)

project(75 VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror -g -fsanitize=address)
    add_link_options(-fsanitize=address)
    set(DOCTEST "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-O2)
    set(DOCTEST "DOCTEST_CONFIG_DISABLE")
endif()

configure_file(optdoc.hpp.in optdoc.hpp)

add_executable(${PROJECT_NAME} 75.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


target_include_directories(${PROJECT_NAME} PUBLIC
    "/opt/homebrew/include/"
    "/opt/homebrew/Cellar/llvm/17.0.4/include/c++/v1/")

