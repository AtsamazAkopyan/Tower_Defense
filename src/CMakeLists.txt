cmake_minimum_required(VERSION 3.10)
project(akopyats)

set(CMAKE_CXX_STANDARD 11)

include_directories(/C:/Users/armad/Desktop/ncurses-6.1/ncurses)


add_executable(PA2Project main.cpp Tower.cpp Tower.h Attacker.cpp Attacker.h MapObjects/MapObjects.cpp MapObjects/MapObjects.h MapObjects/Wall.cpp MapObjects/Wall.h Map.cpp Map.h FileReaderClass.cpp FileReaderClass.h BFS.cpp BFS.h MapObjects/Path.cpp MapObjects/Path.h gameLoop.cpp gameLoop.h)