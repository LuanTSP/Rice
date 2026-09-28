cmake_minimum_required(VERSION 3.14)
project(rice)

add_library(rice SHARED
    # Core
    src/Rice/core/application.cpp
    src/Rice/core/log.cpp

    # Event
    src/Rice/event/eventManager.cpp
    
    # Input
    src/Rice/input/inputManager.cpp
    
    
    # Scene
    src/Rice/scene/scene.cpp
    src/Rice/scene/sceneManager.cpp

    # Renderer
    src/Rice/renderer/opengl/glWindow.cpp
    src/Rice/renderer/opengl/glContext.cpp
    src/Rice/renderer/opengl/glShader.cpp
    src/Rice/renderer/renderer.cpp
    src/Rice/renderer/renderer.cpp
    src/Rice/renderer/vertexBuffer.cpp
    src/Rice/renderer/opengl/glVertexBuffer.cpp
    src/Rice/renderer/indexBuffer.cpp
    src/Rice/renderer/opengl/glIndexBuffer.cpp
)

target_include_directories(rice PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(rice
    PRIVATE 
        codebase
        EnTT::EnTT
        spdlog::spdlog
        SDL3::SDL3
        glad
)