##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake nCurses
##
project(arcade_ncurses)

find_package(Curses REQUIRED)

# Objects
add_library(${PROJECT_NAME} SHARED
    src/nCurses.cpp
)

# Lib
add_library(graphic::ncurses ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC 
        ./include
        ${CURSES_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${CURSES_LIBRARIES}
)

add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)
