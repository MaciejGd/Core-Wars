cmake_minimum_required(VERSION 3.16)

project(GUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "~/Qt/6.8.2/gcc_64/")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

file(GLOB SRC_FILES "src/*.cpp")
file(GLOB HDR_FILES "inc/*.h")

qt_add_library(GUI STATIC
    ${SRC_FILES}
    ${HDR_FILES}
)

target_link_libraries(GUI PUBLIC Qt::Widgets)

set(INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../logger
)


target_include_directories(GUI PUBLIC ${INCLUDE_DIRS})

set_target_properties(GUI PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)