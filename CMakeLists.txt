cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(rice_project)

# Build vendor dependencies
add_subdirectory(vendor/codebase)
add_subdirectory(vendor/entt)
add_subdirectory(vendor/spdlog)

# build Rice engine
add_subdirectory(Rice)

# build sandbox game directory
add_subdirectory(sandbox)