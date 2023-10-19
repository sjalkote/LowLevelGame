cmake_minimum_required(VERSION 3.26)
project(LowLevelGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/sdl2/2.28.4)

find_package(SDL2 REQUIRED)

# Add your project source files
add_executable(LowLevelGame src/main.cpp)

# Link SDL2 library to your project
target_link_libraries(LowLevelGame PRIVATE SDL2::SDL2)


