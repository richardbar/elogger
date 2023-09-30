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
namespace elogger
{
    /**
     * @brief LogLevel is an enum used to describe the severity of a log
     * 
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
}

#endif
