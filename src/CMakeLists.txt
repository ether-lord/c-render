set(PROJECT_SOURCES
  window.c window.h
  shader.c shader.h
)

add_library(crender ${PROJECT_SOURCES})

find_package(glfw3 REQUIRED)

# third-party libraries
set(THIRD_PARTY_LIBS glfw glad cglm_headers)
set(THIRD_PARTY_DIRS third-party/glad third-party/stb)
target_link_libraries(crender PUBLIC ${THIRD_PARTY_LIBS} m)

target_include_directories(crender PUBLIC ${THIRD_PARTY_DIRS})

add_subdirectory(${THIRD_PARTY_DIRS})
add_subdirectory(third-party/cglm EXCLUDE_FROM_ALL)