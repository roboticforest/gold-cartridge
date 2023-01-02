cmake_minimum_required(VERSION 3.19)
project(gold_cartridge)

set(CMAKE_CXX_STANDARD 20)
add_executable(gold_cartridge main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

target_link_libraries(gold_cartridge PUBLIC -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lSDL2_net -lSDL2_ttf)

file(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}")
