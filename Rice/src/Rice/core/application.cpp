#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
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
#include <utility>



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

        const std::string firstVertexShader = R"(
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

        const std::string firstFragmentShader = R"(
            #version 460 core

            in vec4 v_Color;
            out vec4 FragColor;

            void main()
            {
                FragColor = v_Color;
            }
        )";

        const std::string secondVertexShader = R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;

            out vec4 v_Color;

            void main()
            {
                v_Color = vec4(aColor.bgr, aColor.a);
                gl_Position = vec4(aPos.x + 0.55, aPos.y, aPos.z, 1.0);
            }
        )";

        const std::string secondFragmentShader = R"(
            #version 460 core

            in vec4 v_Color;
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(v_Color.rgb * vec3(1.0, 0.55, 0.25), v_Color.a);
            }
        )";

        auto addRenderObject = [this](
            float* vertices,
            std::uint32_t vertexBufferSize,
            std::uint32_t* indices,
            std::uint32_t indexCount,
            const std::string& vertexShader,
            const std::string& fragmentShader)
        {
            RenderObject object;
            object.vertexArray.reset(Rice::VertexArray::Create());
            object.vertexBuffer.reset(Rice::VertexBuffer::Create(
                vertices,
                vertexBufferSize,
                {
                    { ShaderDataType::Float3, "a_Position" },
                    { ShaderDataType::Float4, "a_Color" }
                }
            ));

            object.indexBuffer.reset(Rice::IndexBuffer::Create(
                indices,
                static_cast<std::uint32_t>(sizeof(std::uint32_t) * indexCount)
            ));

            object.vertexArray->AddVertexBuffer(object.vertexBuffer);
            object.vertexArray->SetIndexBuffer(object.indexBuffer);
            object.shader = std::make_shared<RICE_INTERNAL::GLShader>(vertexShader, fragmentShader);
            object.indexCount = indexCount;
            m_RenderObjects.push_back(std::move(object));
        };

        std::uint32_t firstIndices[] = {0, 1, 2};
        float firstVertices[] = {
            -0.90f, -0.55f, 0.0f, 1.0f, 0.1f, 0.1f, 1.0f,
            -0.15f, -0.55f, 0.0f, 0.1f, 1.0f, 0.1f, 1.0f,
            -0.525f, 0.50f, 0.0f, 0.1f, 0.2f, 1.0f, 1.0f
        };

        std::uint32_t secondIndices[] = {0, 1, 2, 2, 3, 0};
        float secondVertices[] = {
            -0.30f, -0.30f, 0.0f, 1.0f, 0.2f, 0.1f, 1.0f,
            0.30f, -0.30f, 0.0f, 0.1f, 1.0f, 0.2f, 1.0f,
            0.30f, 0.30f, 0.0f, 0.1f, 0.2f, 1.0f, 1.0f,
            -0.30f, 0.30f, 0.0f, 1.0f, 0.8f, 0.1f, 1.0f
        };

        addRenderObject(
            firstVertices,
            static_cast<std::uint32_t>(sizeof(firstVertices)),
            firstIndices,
            static_cast<std::uint32_t>(std::size(firstIndices)),
            firstVertexShader,
            firstFragmentShader
        );
        addRenderObject(
            secondVertices,
            static_cast<std::uint32_t>(sizeof(secondVertices)),
            secondIndices,
            static_cast<std::uint32_t>(std::size(secondIndices)),
            secondVertexShader,
            secondFragmentShader
        );

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
            for (const auto& object : m_RenderObjects)
            {
                object.vertexArray->Bind();
                object.shader->Bind();
                glDrawElements(
                    GL_TRIANGLES,
                    static_cast<GLsizei>(object.indexCount),
                    GL_UNSIGNED_INT,
                    nullptr
                );
                object.shader->Unbind();
            }

            m_Window->SwapBuffers();
        }

        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}