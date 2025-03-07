cmake_minimum_required(VERSION 3.16)
project(Logic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(SRC_DIRS
#     ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/Platform/src
# )

set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/inc
)

file(GLOB SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/src/*.cpp
)
file(GLOB HDR_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Instructions/inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Platform/inc/*.h
)

add_library(Logic STATIC
    ${SRC_FILES}
    ${HDR_FILES}
)

#set_source_files_properties(${SRC_FILES} PROPERTIES LANGUAGE CXX)
message(STATUS "Source files: ${SRC_FILES}")
message(STATUS "Header files: ${HDR_FILES}")

target_include_directories(Logic PUBLIC ${INCLUDE_DIRS})


