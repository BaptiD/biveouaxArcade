##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake SDL2
##
project(arcade_sdl2)

# Requierments
find_package(SDL2 REQUIRED)

# Objects
add_library(${PROJECT_NAME} SHARED
    src/SDL2.cpp
)

# Lib
add_library(graphic::sdl2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ./include
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)

add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ../../../lib/)
