#pragma once

namespace Rice 
{
    class Application 
    {
        public:
            // Application class is the entrypoint for
            // the engine. It includes methods for managing Scenes
            Application() = default;
            ~Application() = default;

            void Run();

        private:
            bool m_IsRunning = false;
    };
}