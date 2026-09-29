#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
#include "Rice/renderer/bufferLayout.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "log.hpp"

#include <GLES2/gl2.h>
#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <stdexcept>

#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"

namespace Rice {
    namespace {
        void InitializeWindow(const std::string& backend, std::unique_ptr<Rice::Window>& window)
        {
            if (backend == "opengl")
            {
                Rice::Renderer::SetGraphicsBackend(Rice::GraphicsBackend::OpenGL);
                window = std::make_unique<RICE_INTERNAL::glWindow>();
                return;
            }

            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        void InitializeManagers(std::unique_ptr<RICE_INTERNAL::EventManager>& events,
                                std::unique_ptr<RICE_INTERNAL::InputManager>& inputs)
        {
            events = std::make_unique<RICE_INTERNAL::EventManager>();
            inputs = std::make_unique<RICE_INTERNAL::InputManager>();
        }

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
        {
            switch (type) {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                case ShaderDataType::Mat2:
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                    return GL_FLOAT;

                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                    return GL_INT;

                case ShaderDataType::Bool:
                    return GL_BOOL;
            }

            std::string msg = "Invalid ShaderDataType";
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }
    }

    Application::Application(const std::string title, int width, int height)
        : Application(title, width, height, m_Backend)
    {
    }

    Application::Application(const std::string title, int width, int height, const std::string& backend)
    {
        Log::Init();
        m_Backend = backend;

        InitializeWindow(m_Backend, m_Window);

        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        m_Window->CreateWindow(title, width, height);
        InitializeManagers(m_Events, m_Inputs);

        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    void Application::Run()
    {
        Log::Info("Application running...");

        unsigned int vertexArray = 0;
        glGenVertexArrays(1, &vertexArray);
        glBindVertexArray(vertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        auto vertBuffer = Rice::VertexBuffer::Create(vertices, sizeof(vertices));
        vertBuffer->Bind();

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        vertBuffer->SetLayout(layout);

        uint32_t index = 0;
        for (auto& e : vertBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                e.GetComponentCount(), 
                ShaderDataTypeToOpenGLBaseType(e.Type), 
                e.Normalized ? GL_TRUE : GL_FALSE , 
                layout.GetStride(), 
                reinterpret_cast<const void*>(static_cast<std::uintptr_t>(e.Offset)));
            index++;
        }

        uint32_t indices[3] = {0, 1, 2};
        auto indexBuffer = Rice::IndexBuffer::Create(indices, sizeof(indices));
        indexBuffer->Bind();

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

        auto myShader = RICE_INTERNAL::GLShader(vertSrc, fragSrc);

        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events->poll();
            m_Inputs->update();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindVertexArray(vertexArray);
            myShader.Bind();
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            m_Window->SwapBuffers();
            myShader.Unbind();
        }

        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}