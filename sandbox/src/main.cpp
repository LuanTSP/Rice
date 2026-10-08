#include "Rice/core/log.hpp"
#include "Rice/input/input.hpp"
#include <Rice.hpp>
#include <cstdlib>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <string>

class ExampleScene : public Rice::Scene
{
public:
    void onLoad() override
    {
        const std::string firstVertexShader = R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;
            uniform mat4 u_View;
            uniform mat4 u_Proj;

            out vec4 v_Color;

            void main()
            {
                v_Color = aColor;
                gl_Position = u_Proj * u_View * vec4(aPos, 1.0);
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
            uniform mat4 u_View;
            uniform mat4 u_Proj;

            out vec4 v_Color;

            void main()
            {
                v_Color = vec4(aColor.bgr, aColor.a);
                gl_Position = u_Proj * u_View * vec4(aPos.x + 0.55, aPos.y, aPos.z, 1.0);
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

        std::shared_ptr<Rice::VertexBuffer> vertexBuffer1(Rice::VertexBuffer::Create(
            firstVertices, 
            sizeof(firstVertices), 
            {
                { Rice::ShaderDataType::Float3, "aPos" },
                { Rice::ShaderDataType::Float4, "aColor" }
            }
        ));

        std::shared_ptr<Rice::VertexBuffer> vertexBuffer2(Rice::VertexBuffer::Create(
            secondVertices, 
            sizeof(secondVertices), 
            {
                { Rice::ShaderDataType::Float3, "aPos" },
                { Rice::ShaderDataType::Float4, "aColor" }
            }
        ));

        const std::shared_ptr<Rice::IndexBuffer> indexBuffer1(Rice::IndexBuffer::Create(firstIndices, sizeof(firstIndices)));
        const std::shared_ptr<Rice::IndexBuffer> indexBuffer2(Rice::IndexBuffer::Create(secondIndices, sizeof(secondIndices)));

        m_Shader1.reset(Rice::Shader::Create(firstVertexShader, firstFragmentShader));
        m_Shader2.reset(Rice::Shader::Create(secondVertexShader, secondFragmentShader));

        m_VertexArray1.reset(Rice::VertexArray::Create());
        m_VertexArray2.reset(Rice::VertexArray::Create());

        m_VertexArray1->AddVertexBuffer(vertexBuffer1);
        m_VertexArray2->AddVertexBuffer(vertexBuffer2);

        m_VertexArray1->SetIndexBuffer(indexBuffer1);
        m_VertexArray2->SetIndexBuffer(indexBuffer2);

        m_Camera = std::make_shared<Rice::OrthoCamera>(-1.0f, 1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
        m_Camera->SetRotation(0.0f);
        m_Camera->SetPosition({0.0f, 0.0f,1});

        Rice::Log::Info("Scene loaded");
    }

    void onUpdate() override
    {
        const float deltaTime = static_cast<float>(Rice::Time::DTSeconds());
        glm::vec3 movement(0.0f);

        if (Rice::Input::IsKeyDown(Rice::Key::W))
            movement.y += 1.0f;
        if (Rice::Input::IsKeyDown(Rice::Key::A))
            movement.x -= 1.0f;
        if (Rice::Input::IsKeyDown(Rice::Key::S))
            movement.y -= 1.0f;
        if (Rice::Input::IsKeyDown(Rice::Key::D))
            movement.x += 1.0f;

        if (glm::length(movement) > 0.0f)
        {
            movement = glm::normalize(movement);
            m_CameraPosition += movement * (m_CameraSpeedMetersPerSecond * deltaTime);
            m_Camera->SetPosition(m_CameraPosition);
        }

        std::string msg = "Frametime: ";
        msg += std::to_string(Rice::Time::DTMilliseconds());
        msg += "ms";
        Rice::Log::Info(msg);

        float rotationDeltaDegrees = 0.0f;
        if (Rice::Input::IsKeyDown(Rice::Key::Q))
            rotationDeltaDegrees += m_CameraRotationDegreesPerSecond * deltaTime;
        if (Rice::Input::IsKeyDown(Rice::Key::E))
            rotationDeltaDegrees -= m_CameraRotationDegreesPerSecond * deltaTime;

        // Wheel input is a discrete step, so it uses degrees per scroll unit, not degrees per second.
        rotationDeltaDegrees -= Rice::Input::MouseScrollY() * m_MouseWheelDegreesPerUnit;
        if (rotationDeltaDegrees != 0.0f)
        {
            m_CameraRotation += glm::radians(rotationDeltaDegrees);
            m_Camera->SetRotation(m_CameraRotation);
        }
        

        // Draw to screen
        auto clearColor = glm::vec4(0.1, 0.1, 0.1, 1.0f);

        Rice::Renderer::BeginScene(m_Camera);

        Rice::Renderer::SetClearColor(clearColor);
        Rice::Renderer::Clear();
        
        Rice::Renderer::Submit(m_VertexArray1, m_Shader1);            
        Rice::Renderer::Submit(m_VertexArray2, m_Shader2);

        Rice::Renderer::EndScene();
        Rice::Renderer::EndScene();
    }
private:
    std::shared_ptr<Rice::Shader> m_Shader1;
    std::shared_ptr<Rice::Shader> m_Shader2;
    std::shared_ptr<Rice::VertexArray> m_VertexArray1;
    std::shared_ptr<Rice::VertexArray> m_VertexArray2;
    std::shared_ptr<Rice::OrthoCamera> m_Camera;

    glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float m_CameraSpeedMetersPerSecond = 5.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationDegreesPerSecond = 90.0f;
    float m_MouseWheelDegreesPerUnit = 10.0f;
};

int main()
{
    auto app = Rice::Application("My Window", 600, 400);
    app.SetScene<ExampleScene>();
    
    app.Run();
}