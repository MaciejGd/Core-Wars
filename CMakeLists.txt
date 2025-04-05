cmake_minimum_required(VERSION 3.16)
project(CoreWars)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Add subdirs
add_subdirectory(GUI)
add_subdirectory(Logic)
set(CMAKE_BUILD_TYPE Debug)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/operator_tests/inc/
)

file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/operator_tests/src/*.cpp
)
file(GLOB HDR_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/TestSuite/operator_tests/inc/*.h
)

add_executable(main
    main.cpp
    ${SRC_FILES}
    ${HDR_FILES}
)

target_include_directories(main PUBLIC ${INCLUDE_DIRS})
target_link_libraries(main PRIVATE GUI Logic)
