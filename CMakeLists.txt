cmake_minimum_required(VERSION 3.19)
project(gold_cartridge)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")  # Add the CMake directory to the search path.

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})       # Should be: /usr/include/SDL2

message(NOTICE ${SDL2_INCLUDE_DIRS})
message(NOTICE ${SDL2_IMAGE_INCLUDE_DIRS})

message(NOTICE ${SDL2_LIBRARIES})
message(NOTICE ${SDL2_IMAGE_LIBRARIES})

message(NOTICE "DEFAULT OUTPUT DIR:")
message(NOTICE "${PROJECT_BINARY_DIR}")

file(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}")

add_executable(gold_cartridge main.cpp)
target_link_libraries(gold_cartridge PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
