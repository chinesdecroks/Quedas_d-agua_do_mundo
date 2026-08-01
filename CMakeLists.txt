cmake_minimum_required(VERSION 4.2)
project(Quedas_d_agua_do_mundo C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Quedas_d_agua_do_mundo
        cachoeira.c
        cachoeira.h
        main.c)
