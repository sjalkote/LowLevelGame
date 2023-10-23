cmake_minimum_required(VERSION 3.23)
project(LowLevelGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH F:/libs/SDL2)

set(IMGUI_SOURCE_DIR "include/imgui")
add_library(imgui
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp

    # Include other source files if necessary
)
target_include_directories(imgui PUBLIC ${IMGUI_SOURCE_DIR} ${IMGUI_SOURCE_DIR}/backends )

find_package(SDL2 REQUIRED)

# Add your project source files
add_executable(LowLevelGame src/main.cpp)

# Link SDL2 library to your project
target_link_libraries(LowLevelGame PRIVATE imgui SDL2::SDL2)
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})