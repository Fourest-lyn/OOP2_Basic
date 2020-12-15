cmake_minimum_required(VERSION 3.17)
project(OOP2_Basic)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP2_Basic

        Basic/Basic.cpp

        Basic/exp.h
        Basic/exp.cpp
        Basic/parser.h
        Basic/parser.cpp
        Basic/program.h
        Basic/program.cpp
        Basic/evalstate.h
        Basic/evalstate.cpp
        Basic/statement.h
        Basic/statement.cpp

        StanfordCPPLib/error.h
        StanfordCPPLib/error.cpp
        StanfordCPPLib/simpio.h
        StanfordCPPLib/simpio.cpp
        StanfordCPPLib/tokenscanner.h
        StanfordCPPLib/tokenscanner.cpp
        StanfordCPPLib/strlib.h
        StanfordCPPLib/strlib.cpp
        StanfordCPPLib/map.h
        )