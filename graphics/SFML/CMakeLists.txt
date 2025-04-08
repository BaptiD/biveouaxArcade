##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake SFML
##

project(arcade_sfml)

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

add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)