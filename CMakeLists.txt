cmake_minimum_required(VERSION 3.14)

project(crender)

add_executable(main main.c)

target_link_libraries(main PUBLIC shader)
target_link_libraries(main PUBLIC window)

target_include_directories(main PUBLIC src)

add_subdirectory(src)
