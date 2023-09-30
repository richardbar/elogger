# MIT License
# 
# Copyright (c) 2023 Rikarnto Bariampa
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.25)
project(elogger VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(ELOGGER_C_SRC "")
set(ELOGGER_CXX_SRC "")

include_directories("${CMAKE_CURRENT_LIST_DIR}/include/public")
include_directories("${CMAKE_CURRENT_LIST_DIR}/include/private")

include("${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt")

add_library("elogger_static" STATIC ${ELOGGER_C_SRC};${ELOGGER_CXX_SRC})

if (NOT WIN32)
    set_target_properties("elogger_static" PROPERTIES OUTPUT_NAME elogger)
endif()

install(TARGETS "elogger_static"
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/public/"
        DESTINATION "include"
        FILES_MATCHING
        PATTERN "*.h")
