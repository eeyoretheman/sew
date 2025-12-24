cmake_minimum_required(VERSION 3.28)

project(sew)

set(CMAKE_C_STANDARD 99)

add_executable(sew source/main.c)

install(TARGETS sew RUNTIME DESTINATION bin)

include(CPack)
