cmake_minimum_required(VERSION 3.14)
project(rice_project)


# for clangd intel
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# for spdlog with is build statically
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Disable X11 for linux
set(SDL_X11 OFF)
set(SDL_WAYLAND ON)

# Build vendor dependencies dirs with CMake
add_subdirectory(vendor/codebase)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/SDL)

# Build glad as a shared lib
add_library(glad SHARED vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

# build Rice engine
add_subdirectory(Rice)

# build sandbox game directory
add_subdirectory(sandbox)