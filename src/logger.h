#ifndef PLUGINDEV_LOGGER_H
#define PLUGINDEV_LOGGER_H

#ifdef _WIN32
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API
#endif // EXPORT_API

#include <iostream>
#include <fstream>

typedef enum log_rank
{
    INFO,
    WARN,
    ERR,
    FATAL
} log_rank_t;

// initialization logger.
extern "C" EXPORT_API void initLogger(const std::string &,
                                      const std::string &,
                                      const std::string &);

class EXPORT_API Logger
{
    friend void initLogger(const std::string &,
                           const std::string &,
                           const std::string &);

public:
    Logger(log_rank_t log_rank) : m_log_rank(log_rank){};
    ~Logger();

    static std::ostream &start(log_rank_t log_rank,
                               const int32_t line,
                               const std::string &file_name);

private:
    static std::ostream &getStream(log_rank_t log_rank);

    static std::ofstream m_info_log_file;
    static std::ofstream m_warn_log_file;
    static std::ofstream m_error_log_file;

    log_rank_t m_log_rank;
};

#define LOG(log_rank) \
    Logger(log_rank).start(log_rank, __LINE__, __FILE__)

#endif // PLUGINDEV_LOGGER_H