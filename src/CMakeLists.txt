set(PROJECT_SOURCES
  window.c window.h
  shader.c shader.h
)

add_library(crender ${PROJECT_SOURCES})

find_package(glfw3 REQUIRED)

set(LIBRARIES shader window)
set(THIRD_PARTY_LIBS glfw glad)

# third-party libraries
target_link_libraries(crender PUBLIC ${THIRD_PARTY_LIBS})

target_include_directories(crender PUBLIC third-party/glad)

add_subdirectory(third-party/glad)
