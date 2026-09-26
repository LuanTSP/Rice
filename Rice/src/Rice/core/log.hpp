#pragma once

#include <string>

namespace Rice
{

    /**
    * @brief Logging interface for the Rice engine.
    *
    * Provides simple logging functions for different log levels.
    * The implementation uses spdlog internally.
    */
    class Log
    {
    public:

        /**
        * @brief Initializes the logging system.
        *
        * Must be called before using the logging functions.
        */
        static void Init();

        /**
        * @brief Logs an informational message.
        *
        * @param message Message to log.
        */
        static void Info(const std::string& message);

        /**
        * @brief Logs a warning message.
        *
        * @param message Message to log.
        */
        static void Warn(const std::string& message);

        /**
        * @brief Logs an error message.
        *
        * @param message Message to log.
        */
        static void Error(const std::string& message);

        /**
        * @brief Logs a debug message.
        *
        * @param message Message to log.
        */
        static void Debug(const std::string& message);
    };

}
