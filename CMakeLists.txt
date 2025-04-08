##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake
##
cmake_minimum_required(VERSION 3.10)
project(arcade)

# Libs setup
set(CMAKE_SHARED_LIBRARY_PREFIX "")
add_custom_target(build-time-make-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ../lib/)

# Includes
include_directories(
    ./include
    ./include/data
    ./include/interfaces
)

# Graphic Libs
add_subdirectory(graphics/nCurses)
add_subdirectory(graphics/SDL2)
add_subdirectory(graphics/SFML)

# Game Libs
add_subdirectory(games/menu)
add_subdirectory(games/SolarFox)

# Core
add_subdirectory(core)