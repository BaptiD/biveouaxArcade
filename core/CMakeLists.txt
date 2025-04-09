##
## EPITECH PROJECT, 2025
## B-OOP-400-PAR-4-1-arcade-pierre.pruvost
## File description:
## CMake
##
project(core)

# Objects
add_executable(arcade
    src/core.cpp
    src/main.cpp
)

# Compilation
target_include_directories(arcade
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Moving binary
add_custom_command(TARGET arcade 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade> ../..)