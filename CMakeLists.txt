cmake_minimum_required(VERSION 3.28)
file(GLOB SOURCES ./src/*.c)

project(hazbuild)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})
