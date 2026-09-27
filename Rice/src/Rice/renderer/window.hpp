#pragma once

#include <string>

namespace RICE_INTERNAL
{
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void CreateWindow(
            const std::string& title,
            int width,
            int height
        ) = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;
        virtual std::string GetTitle() const = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual void SwapBuffers() = 0;
    };
}