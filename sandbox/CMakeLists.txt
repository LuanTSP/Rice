cmake_minimum_required(VERSION 3.14)
project(game)

add_executable(game
    src/main.cpp
)

target_link_libraries(game PRIVATE
    rice
)