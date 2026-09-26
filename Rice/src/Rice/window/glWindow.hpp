#pragma once

#include "window.hpp"
#include <string>

namespace RICE_INTERNAL
{
    class glWindow : public I_Window
    {
        public:
            // Initializes the window
            // @param title : std::string   (window title)
            // @param width : int           (window width)
            // @param height: int           (window height)      
            glWindow(const std::string& title, const int width, const int height);
            ~glWindow() = default;

            // Returns the width of the window
            int getWidth() override;

            // Returns the height of the window
            int getHeight() override;

            // Returns the title of the window
            std::string getTitle() override;

            // Returns true if vsync is enabled. Returns false otherwise
            bool isVSync() override;

            // Setter of the window title
            // @param title: std::string (title of the window)
            void setTitle(const std::string& title) override;

            // Setter for vsync
            // @param enabled: bool (if vsync is enabled)
            void setVSync(bool enabled) override;

        private:
            int m_Width = 600;
            int m_Height = 400;
            std::string m_TItle = "Window";


    };
}