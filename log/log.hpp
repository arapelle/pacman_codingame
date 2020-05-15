#pragma once

#include <chrono>
#include <iostream>

inline std::ostream& info() { return std::cerr; }
inline std::ostream& error() { return std::cerr << "ERROR: "; }
inline std::ostream& debug() { return std::cerr << "DEBUG: "; }

struct Function_trace
{
    Function_trace(const char* file, int line, const char* func)
        : file(file), line(line), func(func)
    {
        debug() << "TRACE: " << file << ":" << line << " " << func << std::endl;
    }

    ~Function_trace()
    {
        debug() << "/TRACE: " << file << ":" << line << " " << func << std::endl;
    }

    const char* file;
    int line;
    const char* func;
};

struct Duration_trace
{
    Duration_trace()
        : start_time_(std::chrono::steady_clock::now())
    {}

    ~Duration_trace()
    {
        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> turn_duration = end_time - start_time_;
        debug() << "Duration: " << turn_duration.count() << "ms" << std::endl;
    }

private:
    std::chrono::steady_clock::time_point start_time_;
};

#define TRACE 1
#ifdef TRACE
#define trace() Function_trace ftrace__(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#else
#define trace do {} while(false)
#endif
