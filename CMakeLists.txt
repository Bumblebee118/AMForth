cmake_minimum_required(VERSION 3.17)
project(AMForth C)

set(CMAKE_C_STANDARD 99)

add_executable(AMForth main.c stack.c stack.h dict.c dict.h interpret.c interpret.h basic.c basic.h executor.c executor.h error.c error.h compiler.c compiler.h global.h)