#pragma once

#include "SDL3/SDL_video.h"
#include "Rice/renderer/window.hpp"
#include "Rice/renderer/opengl/glContext.hpp"
#include <string>
#include <SDL3/SDL.h>

namespace RICE_INTERNAL
{
    class glWindow : public Rice::Window
    {
        public:
            glWindow() = default;
            ~glWindow() override;
        
            // Initializes the window
            // @param title : std::string   (window title)
            // @param width : int           (window width)
            // @param height: int           (window height)      
            void CreateWindow(
                const std::string& title,
                int width,
                int height
            ) override;

            // Returns the width of the window
            int GetWidth() const override;

            // Returns the height of the window
            int GetHeight() const override;

            // Returns the title of the window
            std::string GetTitle() const override;

            // Returns true if vsync is enabled. Returns false otherwise
            bool IsVSync() const override;

            // Setter of the window title
            // @param title: std::string (title of the window)
            void SetTitle(const std::string& title) override;

            // Setter for vsync
            // @param enabled: bool (if vsync is enabled)
            void SetVSync(bool enabled) override;

            // Swap buffers
            void SwapBuffers() override;

        private:
            SDL_Window* m_Window = nullptr;
            GLRenderContext* m_GLRenderContext = nullptr;
            int m_Width;
            int m_Height;
            bool m_Vsync = true;
            std::string m_Title;

    };
}