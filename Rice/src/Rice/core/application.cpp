#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"
#include "glm/ext/vector_float4.hpp"
#include "log.hpp"

#include <memory>

namespace Rice 
{
    Application::Application(const std::string& title, int width, int height)
    {
        // 1. Initialize logging
        Log::Init();
        Renderer::Init(Rice::GraphicsBackend::OpenGL);

        // 2. Initialize window with OpenGL backend TODO: switch the backend implementation automatically
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

        m_VertexBuffer1.reset(Rice::VertexBuffer::Create(
            firstVertices, 
            sizeof(firstVertices), 
            {
                { Rice::ShaderDataType::Float3, "aPos" },
                { Rice::ShaderDataType::Float4, "aColor" }
            }
        ));

        m_VertexBuffer2.reset(Rice::VertexBuffer::Create(
            secondVertices, 
            sizeof(secondVertices), 
            {
                { Rice::ShaderDataType::Float3, "aPos" },
                { Rice::ShaderDataType::Float4, "aColor" }
            }
        ));

        m_IndexBuffer1.reset(Rice::IndexBuffer::Create(firstIndices, sizeof(firstIndices)));
        m_IndexBuffer2.reset(Rice::IndexBuffer::Create(secondIndices, sizeof(secondIndices)));

        m_Shader1 = std::make_shared<RICE_INTERNAL::GLShader>(firstVertexShader, firstFragmentShader);
        m_Shader2 = std::make_shared<RICE_INTERNAL::GLShader>(secondVertexShader, secondFragmentShader);

        m_VertexArray1.reset(Rice::VertexArray::Create());
        m_VertexArray2.reset(Rice::VertexArray::Create());

        m_VertexArray1->AddVertexBuffer(m_VertexBuffer1);
        m_VertexArray2->AddVertexBuffer(m_VertexBuffer2);

        m_VertexArray1->SetIndexBuffer(m_IndexBuffer1);
        m_VertexArray2->SetIndexBuffer(m_IndexBuffer2);

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

            auto clearColor = glm::vec4(0.1, 0.1, 0.1, 1.0f);

            Renderer::SetClearColor(clearColor);
            Renderer::Clear();
            
            // Draw
            m_Shader1->Bind();
            Renderer::Submit(m_VertexArray1);
            
            m_Shader2->Bind();
            Renderer::Submit(m_VertexArray2);

            Renderer::EndScene();

            m_Window->SwapBuffers();
        }

        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}