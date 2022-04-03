#include "cxx/oop/stream.h"

namespace UCA_L2INFO_PW4
{
    Logger::Logger(const Logger &log, String lvl):
    stream(log.stream), prefix(log.prefix.concat("/", lvl)), _F_tmp(true)
    { /* ... */ }

    Logger::Logger(OutputStream *stream, String prefix):
    stream(stream), prefix(prefix)
    { /* ... */ }

    Logger::~Logger()
    {
        if (!_F_tmp)
        {
            stream->close();
            delete stream;
        }
    }

    Logger Logger::info() const
    {
        return Logger(*this, "Info");
    }

    Logger Logger::warning() const
    {
        return Logger(*this, "Warning");
    }

    Logger Logger::severe() const
    {
        return Logger(*this, "Error");
    }

    void Logger::setPrefix(const String p)
    {
        this->prefix = p;
    }

    String Logger::getPrefix() const
    {
        return prefix;
    }

    void Logger::print(String str)
    {
        stream->write(str.getCharSequence(), str.length());
    }

    void Logger::println(String str)
    {
        stream->write(str.getCharSequence(), str.length());
        stream->write("\n", 1);
    }
}
