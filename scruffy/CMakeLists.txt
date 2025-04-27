cmake_minimum_required(VERSION 3.10)
project(pico_tests LANGUAGES C)
set(CMAKE_C_STANDARD 23)

# Add scruffy test framework
# Symbolic link: ln -s ~/github/scruffy extlib-scruffy
add_subdirectory(extlib-scruffy)

add_library(pico
  ../src/linked_list.c
  # ../src/map.c
  ../src/fifo.c
)
target_include_directories(pico PUBLIC ../src)

# Test executable
add_executable(${PROJECT_NAME} picotests.c)
target_link_libraries(${PROJECT_NAME} scruffy pico)
