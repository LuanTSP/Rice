#pragma once

#include <string>

namespace RICE_INTERNAL
{
    class I_Window
    {        
        virtual int getWidth()  = 0;
        virtual int getHeight() = 0;
        virtual std::string getTitle()  = 0;
        virtual bool isVSync()  = 0;

        virtual void setTitle(const std::string& title) = 0;
        virtual void setVSync(bool enabled) = 0;
    };
}