#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
#include "Rice/renderer/bufferLayout.hpp"
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include "Rice/renderer/renderer.hpp"
#include "log.hpp"

#include <GLES2/gl2.h>
#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <stdexcept>



namespace Rice 
{
    Application::Application(const std::string title, int width, int height)
    {
        // 1. Initialize logging
        Log::Init();

        // 2. Initialize window with OpenGL backend TODO: switch the backend implementation automatically
        Rice::Renderer::SetGraphicsBackend(Rice::GraphicsBackend::OpenGL);
        m_Window = std::make_unique<RICE_INTERNAL::glWindow>();

        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        m_Window->CreateWindow(title, width, height);

        // 3. Initialize managers
        m_Inputs = std::make_unique<RICE_INTERNAL::InputManager>();
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();

        // 3.1 Substribe to Quit event (not a must but is good)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });

        // 4. Initialize vertex array
        m_VertexArray.reset(Rice::VertexArray::Create());

        // 5. Initialize vertex buffer
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        m_VertexBuffer.reset(Rice::VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        m_VertexBuffer->SetLayout(layout);

        // 6. Initialize index buffer
        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(Rice::IndexBuffer::Create(indices, sizeof(indices)));

        // 7. Add buffers to vertex array
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // 8. Create shaders
        std::string vertSrc = R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;

            out vec4 v_Color;

            void main()
            {
                v_Color = aColor;
                gl_Position = vec4(aPos, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 460 core

            in vec4 v_Color;
            out vec4 FragColor;

            void main()
            {
                FragColor = v_Color;
            }
        )";

        m_Shader = std::make_shared<RICE_INTERNAL::GLShader>(vertSrc, fragSrc);

        Log::Info("Application initialized");
    }

    void Application::Run()
    {
        Log::Info("Runnig..."); // DEBUG

        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events->poll();
            m_Inputs->update();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_VertexArray->Bind();
            m_Shader->Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            m_Window->SwapBuffers();
            m_Shader->Unbind();
        }

        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}