cmake_minimum_required(VERSION 3.28)
project(hazard_engine VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

configure_file(./src/cmake_macros.h.in ../src/cmake_macros.h)

set(HAZBUILD_SRC ./src/main.c ./src/hazeng.c ./src/hazbuild.c)
set(HARVHAZ1_SRC ./src/main.c ./src/hazeng.c ./src/harvhaz1.c ./src/haz_actor.c)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(harvhaz1 ${HARVHAZ1_SRC})
target_link_libraries(harvhaz1 ${SDL2_LIBRARIES})

add_executable(hazbuild ${HAZBUILD_SRC})
target_link_libraries(hazbuild ${SDL2_LIBRARIES})
