#pragma once

namespace Rice
{
    enum class GraphicsBackend
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
        public:
            inline static GraphicsBackend GetGraphicsBackend()
            {
                return m_GraphicsBackend;
            }

            inline static void SetGraphicsBackend(GraphicsBackend backend)
            {
                m_GraphicsBackend = backend;
            }
        
        private:
            static GraphicsBackend m_GraphicsBackend;
    };
}