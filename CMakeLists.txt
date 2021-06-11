cmake_minimum_required(VERSION 3.5)

project(main)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})