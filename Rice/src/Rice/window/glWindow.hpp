#pragma once

#include "SDL3/SDL_video.h"
#include "window.hpp"
#include <string>
#include <SDL3/SDL.h>

namespace RICE_INTERNAL
{
    class glWindow : public Window
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

        private:
            SDL_Window* m_Window = nullptr;
            SDL_GLContext m_Context;
            int m_Width = 600;
            int m_Height = 400;
            bool m_Vsync = true;
            std::string m_Title = "Window";

    };
}