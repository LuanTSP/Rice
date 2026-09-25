cmake_minimum_required(VERSION 3.14)
project(rice)

add_library(rice SHARED
    src/core/application.cpp
)

target_include_directories(rice PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(rice
    PRIVATE codebase
)