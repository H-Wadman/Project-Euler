CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project(81 VERSION 1.0)

add_executable(${PROJECT_NAME} 81.cpp)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -Werror -g -fsanitize=address)
    add_link_options(-fsanitize=address)
    set(DOCTEST "DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN")
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    add_compile_options(-O3 -g)
    set(DOCTEST "DOCTEST_CONFIG_DISABLE")
endif()

configure_file(optdoc.hpp.in optdoc.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "/opt/homebrew/include/")
