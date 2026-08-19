cmake_minimum_required(VERSION 3.16)
project(Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../Logic logic_build)
set(CMAKE_BUILD_TYPE Debug)

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/operator_tests/inc/
)

file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operator_tests/src/*.cpp
)
file(GLOB HDR_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/operator_tests/inc/*.h
)

add_executable(tests
    ${SRC_FILES}
    ${HDR_FILES}
)

target_include_directories(tests PUBLIC ${INCLUDE_DIRS})
target_link_libraries(tests PRIVATE Logic)
