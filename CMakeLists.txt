cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(rice_project)

# Build vendor dependencies
add_subdirectory(vendor/codebase)

# build Rice engine
add_subdirectory(Rice)

# build teste game directory
add_subdirectory(test)