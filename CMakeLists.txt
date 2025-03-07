cmake_minimum_required(VERSION 3.16)
project(CoreWars)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Add subdirs
add_subdirectory(GUI)
add_subdirectory(Logic)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE GUI Logic)
