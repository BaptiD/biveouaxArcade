##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake SFML
##

cmake_minimum_required(VERSION 3.10)
project(arcade_sfml)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Objects
add_library(${PROJECT_NAME} SHARED
    src/Sfml.cpp
)

# Lib
add_library(graphic::sfml ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC 
        ./include
)

target_link_libraries(arcade_sfml sfml-graphics sfml-audio sfml-window sfml-system)


add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)