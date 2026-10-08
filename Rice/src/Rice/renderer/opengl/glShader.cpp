#include "glShader.hpp"
#include "Rice/core/log.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GLES2/gl2.h>
#include <glad/glad.h>
#include <stdexcept>

namespace RICE_INTERNAL
{
    GLShader::GLShader(const std::string& vertSrc, const std::string& fragSrc)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar *source = (const GLchar *)vertSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            std::string msg = "Error compiling vertex shader: ";
            msg += std::string(infoLog.begin(), infoLog.end());
            Rice::Log::Error(msg);
            
            // In this simple program, we'll just leave
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = (const GLchar *)fragSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.
            std::string msg = "Error compiling fragment shader: ";
            msg += std::string(infoLog.begin(), infoLog.end());
            Rice::Log::Error(msg);
            
            // In this simple program, we'll just leave
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_ProgramID = glCreateProgram();

        // Attach our shaders to our program
        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);

        // Link our program
        glLinkProgram(m_ProgramID);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);
            
            // We don't need the program anymore.
            glDeleteProgram(m_ProgramID);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.
            std::string msg = "Error linking shaders: ";
            msg += std::string(infoLog.begin(), infoLog.end());
            Rice::Log::Error(msg);
            
            // In this simple program, we'll just leave
            return;
        }
        // Load uniform locations
        LoadUniformLocations();

        // Always detach shaders after a successful link.
        glDetachShader(m_ProgramID, vertexShader);
        glDetachShader(m_ProgramID, fragmentShader);

    };

    void GLShader::LoadUniformLocations()
    {
        GLint count = 0;
        GLint maxNameLength = 0;

        glGetProgramiv(
            m_ProgramID,
            GL_ACTIVE_UNIFORMS,
            &count
        );

        glGetProgramiv(
            m_ProgramID,
            GL_ACTIVE_UNIFORM_MAX_LENGTH,
            &maxNameLength
        );

        std::vector<GLchar> name(maxNameLength);

        for (GLint i = 0; i < count; ++i)
        {
            GLsizei length = 0;
            GLint size = 0;
            GLenum type = 0;

            glGetActiveUniform(
                m_ProgramID,
                i,
                maxNameLength,
                &length,
                &size,
                &type,
                name.data()
            );

            std::string uniformName(name.data(), length);

            GLint location =
                glGetUniformLocation(m_ProgramID, uniformName.c_str());

            m_Locations.emplace(uniformName, location);
        }
    };

    GLShader::~GLShader()
    {
        glDeleteProgram(m_ProgramID);
    }

    void GLShader::Bind()
    {
        glUseProgram(m_ProgramID);
    };

    void GLShader::Unbind()
    {
        glUseProgram(0);
    }

    void GLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
    {
        auto it = m_Locations.find(name);

        // Check if location exist
        if (it == m_Locations.end())
        {
            std::string msg = "Cannot find location with name: ";
            msg += name;
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }

        // Send data to the GPU
        glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}