cmake_minimum_required(VERSION 3.16)
project(Logic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(SRC_DIRS
#     ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/Platform/src
# )
# enable symbols for debugging
set(CMAKE_BUILD_TYPE Debug)



set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Operations/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Parameters/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/AbstractSyntaxTree/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../logger/
)

file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Parameters/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Operations/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/src/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/AbstractSyntaxTree/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/src/*.cpp
)
file(GLOB HDR_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Operations/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/Parameters/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/AbstractSyntaxTree/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/inc/*.h
)

add_library(Logic STATIC
    ${SRC_FILES}
    ${HDR_FILES}
)

#set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE CXX)
# message(STATUS "Source files: ${SRC_FILES}")
# message(STATUS "Header files: ${HDR_FILES}")

target_include_directories(Logic PUBLIC ${INCLUDE_DIRS})


