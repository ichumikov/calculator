#include "logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger()
{
    auto console = spdlog::stdout_color_mt("calculator");
    spdlog::set_default_logger(console);
}

Logger& Logger::instance()
{
    static Logger logger; 
    return logger;
}

void Logger::info(const std::string& message)
{
    spdlog::info(message);
}

void Logger::error(const std::string& message)
{
    spdlog::error(message);
}