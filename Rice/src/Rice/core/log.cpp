#include "log.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Rice
{

    void Log::Init()
    {
        auto logger = spdlog::stdout_color_mt("Rice");

        logger->set_pattern("[%T] [%^%l%$] %v");

        spdlog::set_default_logger(logger);
    }

    void Log::Info(const std::string& message)
    {
        spdlog::info(message);
    }

    void Log::Warn(const std::string& message)
    {
        spdlog::warn(message);
    }

    void Log::Error(const std::string& message)
    {
        spdlog::error(message);
    }

    void Log::Debug(const std::string& message)
    {
        spdlog::debug(message);
    }

}