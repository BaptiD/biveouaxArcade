##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake Centipede
##

project(arcade_centipede)

# Objects
add_library(${PROJECT_NAME} SHARED
    src/Centipede.cpp
)

# Lib
add_library(game::centipede ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC
        ./include
)

add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)