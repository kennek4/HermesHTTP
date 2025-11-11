# Project Setup
cmake_minimum_required(VERSION 3.29)
project(
  HERMES_CMAKE
  LANGUAGES CXX)

set(HERMES_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

######### DIRECTORIES ##############
add_subdirectory(src)
add_subdirectory(lib/hermes)
