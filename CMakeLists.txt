cmake_minimum_required(VERSION 3.10)
project(Ex1)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

add_executable(Ex1 main.cpp Command.cpp Game.cpp Parser.cpp MainAux.cpp Cell.cpp Files.h Files.cpp)