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

#pragma once

#ifdef __cplusplus

#include <cstdint>
#include <fstream>
#include <string>

namespace elogger
{
    /**
     * @brief LogLevel is an enum used to describe the severity of a log
     * 
     * @see std::string LogLevelToString(const elogger::LogLevel& logLevel)
     */
    enum class LogLevel : uint8_t
    {
        Verbose = 0, /*!< Verbose logging is used to output as much information about events. */
        Debug = 1, /*!< Debugging logging is used to output information that is usefull for debug pursposes. */
        Information = 2, /*!< Information logging is used to provide information about the state of the process. */
        Warning = 3, /*!< Warning logging is used to inform about small errors with a low priority. */
        Error = 4, /*!< Error logging is used to output errors that are top priority. */
        Fatal = 5 /*!< Fatal logging is used to output errors that led the program to a fatal state. */
    };

    /**
     * @brief LogLevelToString stringifies the elogger::LogLevel enum.
     * 
     * @see enum elogger::LogLevel
     * 
     * @param logLevel The elogger::LogLevel to stringify.
     * @return std::string The stringified elogger::LogLevel.
     */
    [[nodiscard]] extern std::string LogLevelToString(const elogger::LogLevel& logLevel) noexcept;

    /**
     * @brief LogPacket houses all the necessary data used by sinks to generate logs. 
     * 
     */
    class LogPacket
    {
        private:
            const elogger::LogLevel _logLevel;
            const std::string _message;
        
        public:
            LogPacket() = delete;
            explicit LogPacket(const elogger::LogLevel& logLevel, const std::string& message);

            /**
             * @brief Get the Log Level object.
             * 
             * @return const elogger::LogLevel& The return value.
             */
            [[nodiscard]] const elogger::LogLevel& GetLogLevel() const noexcept;

            /**
             * @brief Get the Message object.
             * 
             * @return const std::string& The return value.
             */
            [[nodiscard]] const std::string& GetMessage() const noexcept;

    };

    namespace Sinks
    {
        namespace Configuations
        {
            class SinkConfiguration
            {
                private:
                    bool _includeTime = true;
                    std::string _timeFormat = "%FT%T%z";

                public:
                    SinkConfiguration& SetIncludeTime(bool value) noexcept;
                    SinkConfiguration& SetTimeFormat(const std::string& format) noexcept;

                    [[nodiscard]] bool GetIncludeTime() const noexcept;
                    [[nodiscard]] const std::string GetTimeFormat() const noexcept;
            };

            class ConsoleSinkConfiguration  : public SinkConfiguration
            {
                private:
                    bool _color = false;

                public:
                    ConsoleSinkConfiguration& SetColor(bool value) noexcept;
                    
                    [[nodiscard]] bool GetColor() const noexcept;
            };

            class FileSinkConfiguration : public SinkConfiguration
            {
                private:
                    const std::string _fileName;

                public:
                    FileSinkConfiguration() = delete;
                    FileSinkConfiguration(const std::string& fileName);

                    [[nodiscard]] const std::string& GetFileName() const noexcept;
            };
        }

        namespace Utilities
        {
            const std::string GetDateTime(const std::string& format);
        }

        class ISink
        {
            private:

            public:
                [[nodiscard]] virtual bool Handle(const elogger::LogPacket& logPacket) const = 0;
        };

        class ConsoleSink : public elogger::Sinks::ISink
        {
            private:
                elogger::Sinks::Configuations::ConsoleSinkConfiguration _configuration;

            public:
                ConsoleSink() = default;
                explicit ConsoleSink(const elogger::Sinks::Configuations::ConsoleSinkConfiguration& configuations);

                [[nodiscard]] bool Handle(const elogger::LogPacket& logPacket) const final;
        };

        class FileSink : public elogger::Sinks::ISink
        {
            private:
                Configuations::FileSinkConfiguration _configuration;
                mutable std::ofstream _fileStream;

            public:
                FileSink() = delete;
                explicit FileSink(const Configuations::FileSinkConfiguration& configuations);

                [[nodiscard]] bool Handle(const LogPacket& logPacket) const final;

                ~FileSink();
        };
    }
}

#endif
