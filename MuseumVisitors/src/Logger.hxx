#pragma once

#include <string>
#include <chrono>
#include <iostream>

/*! \enum Logger::LogLevel
 * The various log levels
 */
enum class LogLevel {
    TRACE, ///< Captures the finest details of application behavior, making it ideal for deep debugging
    DEBUG, ///< Focuses on information beneficial for regular debugging scenarios.
    INFO, ///< Offers an overview rather than an in - depth analysis.
    WARN, ///< Flag potential problematic behaviors or outcomes
    ERROR, ///< Flag problematic behaviors or outcomes
    CRITICAL ///< Flag critical errors
};

/*! \enum Logger::LogOutput
 * The various log outputs
 */
enum class LogOutput {
    CONSOLE,
    FILE
};

/*! \class Logger
 * The Logger class.
 */
class Logger {
public:
    
    /*! \fn std::shared_ptr<Logger> Logger::getLogger()
    \brief Gets the singleton Logger instance
    */
    static std::shared_ptr<Logger> getLogger();


    /**
    * Logs the given message if the current LogLevel is at least equal to the messageLevel.\n
    * LogLevel can be changed using setLogLevel()
    * @param[in] messageLevel: Log Level
    * @param[in] codeFile: __FILE__
    * @param[in] codeLine: __LINE__
    * @param[in] message: Log Message
    */
    void log(LogLevel messageLevel, std::string codeFile, int codeLine, std::string message);
       
    /**
    * Sets the log level
    * @param[in] logLevel The desired log level.
    */
    void setLogLevel(LogLevel logLevel);

private:
    LogLevel logLevel;
    LogOutput logOutput;
    static std::shared_ptr<Logger> loggerInstance;
    void logMessage(const std::string& message);
};