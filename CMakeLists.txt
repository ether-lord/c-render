cmake_minimum_required(VERSION 3.14)

project(crender)

find_package(glfw3 REQUIRED)

add_executable(main main.c)

# third-party libraries
target_link_libraries(main PUBLIC glad)
target_link_libraries(main PUBLIC glfw)

target_link_libraries(main PUBLIC shader)

target_include_directories(main PUBLIC third-party/glad)
target_include_directories(main PUBLIC src)

add_subdirectory(third-party/glad)
add_subdirectory(src)
