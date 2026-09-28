#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "log.hpp"

#include <memory>
#include <stdexcept>

#include <glad/glad.h> // TODO: Remove dependency
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"
#include "Rice/renderer/indexBuffer.hpp"


namespace Rice {
    Application::Application(const std::string title, int width, int height)
    {
        // Global log initialization
        Log::Init();
        
        // Define rendering backend
        if (m_Backend == "opengl")
        {
            RICE_INTERNAL::Renderer::SetGraphicsBackend(RICE_INTERNAL::GraphicsBackend::OpenGL);
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }
        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        // Try to create window with selected backend
        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }
        m_Window->CreateWindow(title, width, height);
        
        // Initialization of managers
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();
        m_Inputs = std::make_unique<RICE_INTERNAL::InputManager>();

        // Subscrive to Quit event for window to be able to close (default choice)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    Application::Application(const std::string title, int width, int height, const std::string& backend)
    {
        // 1. Global log initialization
        Log::Init();
        
        // 2. Define backend
        m_Backend = backend;
        
        // 3. Define rendering backend
        if (m_Backend == "opengl")
        {
            RICE_INTERNAL::Renderer::SetGraphicsBackend(RICE_INTERNAL::GraphicsBackend::OpenGL);
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }
        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        // 4. Try to create window with selected backend
        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }
        m_Window->CreateWindow(title, width, height);
        
        // 5. Initialization of managers
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();
        m_Inputs = std::make_unique<RICE_INTERNAL::InputManager>();

        // 6. Subscrive to Quit event for window to be able to close (default choice)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    void Application::Run()
    {
        Log::Info("Application running..."); // DEBUG
        
        // DEBUG
        unsigned int VertexArray;

        // 1. Create vertex array buffer
        glGenVertexArrays(1, &VertexArray);
        glBindVertexArray(VertexArray);

        // 2. Create vertex buffer
        // 2.1 Send vertex data to the GPU
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };
        auto vertBuffer = RICE_INTERNAL::VertexBuffer::Create(vertices, sizeof(vertices));
        vertBuffer->Bind();

        // 3. Create and bind index buffer
        uint32_t indices[3] = {0, 1, 2};
        auto indexBuffer = RICE_INTERNAL::IndexBuffer::Create(indices, sizeof(indices));
        indexBuffer->Bind();

        // 3.1 Send index data into GPU

        // 4. Shader
        std::string vertSrc = R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;

            out vec3 v_Pos;

            void main()
            {
                v_Pos = aPos;
                gl_Position = vec4(aPos, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 460 core

            in vec3 v_Pos;
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(v_Pos * 0.5 + 0.5, 0.0);
            }
        )";

        auto myShader = RICE_INTERNAL::GLShader(vertSrc, fragSrc);
        
        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events->poll();
            m_Inputs->update();

            // DEBUG
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindVertexArray(VertexArray);
            myShader.Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            m_Window->SwapBuffers();
            myShader.Unbind();
        }
        
        Log::Info("Application ended."); // DEBUG
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}