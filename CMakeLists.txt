cmake_minimum_required(VERSION 3.17)
project(MetroRoutePlanningSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(MetroRoutePlanningSystem main.cpp Map.cpp Map.h LoadData.cpp LoadData.h)