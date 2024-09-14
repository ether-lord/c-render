add_library(shader SHARED shader.h shader.c)
add_library(window SHARED window.h window.c)

find_package(glfw3 REQUIRED)

# third-party libraries
target_link_libraries(window PUBLIC glfw)
target_link_libraries(window PUBLIC glad)

target_link_libraries(shader PUBLIC glfw)
target_link_libraries(shader PUBLIC glad)

target_include_directories(window PUBLIC third-party/glad)
target_include_directories(shader PUBLIC third-party/glad)


add_subdirectory(third-party/glad)
