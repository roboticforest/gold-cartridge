cmake_minimum_required(VERSION 3.19)
project(gold_cartridge)

set(CMAKE_CXX_STANDARD 20)
add_executable(gold_cartridge main.cpp button.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# SDL2_BINDIR and SDL2_LIBDIR only exist under Win11. Linux Mint doesn't define/need them.
target_link_directories(gold_cartridge PUBLIC ${SDL2_BINDIR} ${SDL2_LIBDIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
    message(STATUS "Debug build on Windows. Allowing console to be visible.")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release" AND WIN32)
    message(STATUS "Release build on Windows. Hiding console.")
    target_link_libraries(gold_cartridge PUBLIC -mwindows)
endif()

# To avoid errors when linking SDL2 on Windows the linker flags must be specified in this order:
# -lmingw32 -lSDL2main -lSDL2 -lotherSDL2libs
if(MINGW)
    message(STATUS "Windows MinGW Build: Adding MinGW linker option.")
    target_link_libraries(gold_cartridge PUBLIC -lmingw32)
endif()
# Note: On Linux Mint I accidentally left out the -lSDL2main flag and everything worked.
#       I haven't looked into why it worked, but I feel it should always be there. - RF
target_link_libraries(gold_cartridge PUBLIC -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf)

# Move program resources and needed library files into the build directory.
file(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}")
if(WIN32)
    message(STATUS "Copying SDL2 Windows DLLs to project build directory.")
    file(COPY "${SDL2_BINDIR}/SDL2.dll" DESTINATION "${PROJECT_BINARY_DIR}")
    file(COPY "${SDL2_BINDIR}/SDL2_image.dll" DESTINATION "${PROJECT_BINARY_DIR}")
    file(COPY "${SDL2_BINDIR}/SDL2_mixer.dll" DESTINATION "${PROJECT_BINARY_DIR}")
    file(COPY "${SDL2_BINDIR}/SDL2_net.dll" DESTINATION "${PROJECT_BINARY_DIR}")
    file(COPY "${SDL2_BINDIR}/SDL2_ttf.dll" DESTINATION "${PROJECT_BINARY_DIR}")
endif()
