#include "cxx/oop/stream.h"

namespace UCA_L2INFO_PW4
{
    Logger::Logger(const Logger &log, String lvl):
            stream(log.stream), _F_prefix(log._F_prefix.concat("/", lvl)), _F_tmp(true)
    { /* ... */ }

    Logger::Logger(OutputStream *stream, String prefix):
            stream(stream), _F_prefix(prefix)
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
        this->_F_prefix = p;
    }

    String Logger::getPrefix() const
    {
        return _F_prefix;
    }

    void Logger::print(String str)
    {
        if (!_F_prefix.isEmpty())
        {
            stream->write("[", 1u);
            stream->write(_F_prefix.getCharSequence(), _F_prefix.length());
            stream->write("] ", 2u);
        }
        stream->write(str.getCharSequence(), str.length());
    }

    void Logger::println(String str)
    {
        if (!_F_prefix.isEmpty())
        {
            stream->write("[", 1u);
            stream->write(_F_prefix.getCharSequence(), _F_prefix.length());
            stream->write("] ", 2u);
        }

        stream->write(str.getCharSequence(), str.length());
        stream->write("\n", 1);
    }
}
