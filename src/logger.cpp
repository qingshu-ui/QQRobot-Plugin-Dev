#include "logger.h"
#include <iomanip>
#include <filesystem>

std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;
std::ofstream Logger::m_error_log_file;

Logger::~Logger()
{
    getStream(m_log_rank) << std::endl
                          << std::flush;

    if (FATAL == m_log_rank)
    {
        m_info_log_file.close();
        m_info_log_file.close();
        m_info_log_file.close();
        abort();
    }
}

std::ostream &Logger::start(log_rank_t log_rank, const int32_t line, const std::string &file_name)
{
    std::time_t currentTime = std::time(nullptr);
    std::tm *timeinfo = std::localtime(&currentTime);
    std::filesystem::path file_path(file_name);

    return getStream(log_rank) << std::put_time(timeinfo, "%H:%M:%S ")
                               << "file (" << file_path.filename().string() << ") "
                               << "line " << line << ": "
                               << std::flush;
}

std::ostream &Logger::getStream(log_rank_t log_rank)
{
    return (INFO == log_rank) ? (m_info_log_file.is_open() ? m_info_log_file : std::cout) : (WARN == log_rank) ? (m_warn_log_file.is_open() ? m_warn_log_file : std::cerr)
                                                                                                               : (m_error_log_file.is_open() ? m_error_log_file : std::cerr);
}

void initLogger(const std::string &info_log_filename, const std::string &warn_log_filename, const std::string &error_log_filename)
{
    Logger::m_info_log_file.open(info_log_filename.c_str());
    Logger::m_warn_log_file.open(warn_log_filename.c_str());
    Logger::m_error_log_file.open(error_log_filename.c_str());
}
