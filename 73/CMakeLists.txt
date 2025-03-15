cmake_minimum_required(VERSION 3.26)

project(73)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_compile_options(-O2)

link_directories(
	"/usr/local/lib"
	"/opt/homebrew/Cellar/llvm/17.0.4/lib/c++"
)

add_executable(${PROJECT_NAME} 73.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
	"/opt/homebrew/Cellar/llvm/17.0.4/include/c++/v1/"
	"/usr/local/include")
target_link_libraries(${PROJECT_NAME} PUBLIC
	"/usr/local/lib/libfilewrapper.a"
)
