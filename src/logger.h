#ifndef PLUGINDEV_LOGGER_H
#define PLUGINDEV_LOGGER_H

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
void initLogger(const std::string &,
                const std::string &,
                const std::string &);

class Logger
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

#define CHECK(a)                                \
    if (!(a))                                   \
    {                                           \
        LOG(ERR) << "CHECK failed" << endl      \
                 << #a << " = " << (a) << endl; \
        abort();                                \
    }

#define CHECK_NOTNULL(a)                           \
    if (NULL == (a))                               \
    {                                              \
        LOG(ERR) << "CHECK_NOTNULL failed" << endl \
                 << #a << " == NULL" << endl;      \
        abort();                                   \
    }

#define CHECK_NULL(a)                             \
    if (NULL != (a))                              \
    {                                             \
        LOG(ERR) << " CHECK_NULL failed " << endl \
                 << #a << "!= NULL " << endl;     \
        abort();                                  \
    }

#define CHECK_EQ(a, b)                          \
    if (!((a) == (b)))                          \
    {                                           \
        LOG(ERR) << " CHECK_EQ failed " << endl \
                 << #a << "= " << (a) << endl   \
                 << #b << "= " << (b) << endl;  \
        abort();                                \
    }

#define CHECK_NE(a, b)                          \
    if (!((a) != (b)))                          \
    {                                           \
        LOG(ERR) << " CHECK_NE failed " << endl \
                 << #a << "= " << (a) << endl   \
                 << #b << "= " << (b) << endl;  \
        abort();                                \
    }

#define CHECK_LT(a, b)                         \
    if (!((a) < (b)))                          \
    {                                          \
        LOG(ERR) << " CHECK_LT failed "        \
                 << #a << "= " << (a) << endl  \
                 << #b << "= " << (b) << endl; \
        abort();                               \
    }

#define CHECK_GT(a, b)                          \
    if (!((a) > (b)))                           \
    {                                           \
        LOG(ERR) << " CHECK_GT failed " << endl \
                 << #a << " = " << (a) << endl  \
                 << #b << "= " << (b) << endl;  \
        abort();                                \
    }

#define CHECK_LE(a, b)                          \
    if (!((a) <= (b)))                          \
    {                                           \
        LOG(ERR) << " CHECK_LE failed " << endl \
                 << #a << "= " << (a) << endl   \
                 << #b << "= " << (b) << endl;  \
        abort();                                \
    }

#define CHECK_GE(a, b)                          \
    if (!((a) >= (b)))                          \
    {                                           \
        LOG(ERR) << " CHECK_GE failed " << endl \
                 << #a << " = " << (a) << endl  \
                 << #b << "= " << (b) << endl;  \
        abort();                                \
    }

#define CHECK_DOUBLE_EQ(a, b)                    \
    do                                           \
    {                                            \
        CHECK_LE((a), (b) + 0.000000000000001L); \
        CHECK_GE((a), (b)-0.000000000000001L);   \
    } while (0)

#endif // PLUGINDEV_LOGGER_H