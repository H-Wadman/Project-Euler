cmake_minimum_required(VERSION 3.26)

project(72)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

add_compile_options(-Wall -g -fsanitize=address)
#add_compile_options(-O2)

add_link_options(-fsanitize=address)


add_executable(${PROJECT_NAME} 72.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
	"/opt/homebrew/Cellar/llvm/17.0.4/include/c++/v1/"
	"/usr/local/include"
  "/opt/homebrew/include/")
target_link_libraries(${PROJECT_NAME} PUBLIC
	"/usr/local/lib/libfilewrapper.a"
  "/opt/homebrew/lib/libgmp.a"
)
