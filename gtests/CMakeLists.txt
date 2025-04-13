cmake_minimum_required(VERSION 3.10)
project(pico_tests C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)


# Find Google Test
find_package(GTest REQUIRED)

add_library(pico
  ../src/linked_list.c
  # ../src/map.c
  ../src/fifo.c
)
target_include_directories(pico PUBLIC ../src)

# Test executable
add_executable(${PROJECT_NAME} gtests.cpp)
target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main pico)

# Enable testing
enable_testing()
add_test(NAME AllTests COMMAND ${PROJECT_NAME})