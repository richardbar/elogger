/**
 * MIT License
 * 
 * Copyright (c) 2023 Rikarnto Bariampa
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "elogger.hpp"

#include <iostream>

static constexpr const std::string GetColor(const elogger::LogLevel& logLevel) noexcept
{
    switch (logLevel)
    {
        case elogger::LogLevel::Verbose: return "\e[0;37m";
        case elogger::LogLevel::Debug: return "\e[0;34m";
        case elogger::LogLevel::Information: return "\e[0;32m";
        case elogger::LogLevel::Warning: return "\e[0;33m";
        case elogger::LogLevel::Error: return "\e[0;31m";
        default: return "Unknown";
    }
}

static constexpr const std::string GetColorReset() noexcept
{
    return "\e[0m";
}

elogger::Sinks::ConsoleSink::ConsoleSink(const elogger::Sinks::Configuations::ConsoleSinkConfiguration& configuations) :
    _configuration { configuations }
{ }

bool elogger::Sinks::ConsoleSink::Handle(const elogger::LogPacket& logPacket) const
{
    if (this->_configuration.GetIncludeTime())
    {
        std::cout << Utilities::GetDateTime(this->_configuration.GetTimeFormat()) << " ";
    }
    
    std::cout << "[";
    
    if (this->_configuration.GetColor())
    {
        std::cout << GetColor(logPacket.GetLogLevel());
    }

    std::cout << elogger::LogLevelToString(logPacket.GetLogLevel());
    
    if (this->_configuration.GetColor())
    {
        std::cout << GetColorReset();
    }

    std::cout << "]: " << logPacket.GetMessage() << std::endl;

    return true;
}
