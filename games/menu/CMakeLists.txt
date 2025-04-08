##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake nCurses
##
project(arcade_menu)

# Objects
add_library(${PROJECT_NAME} SHARED
    src/menu.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

# Lib
add_library(game::menu ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC 
        ./include
        ../../core/include
)

add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)
