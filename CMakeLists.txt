cmake_minimum_required(VERSION 3.16)
project(ImGuiApp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect your source files
set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

file(GLOB SRC_FILES src/*.cpp)

add_executable(main
    ${IMGUI_SOURCES}
    ${SRC_FILES}
)

# Add include directories
target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
    ${CMAKE_SOURCE_DIR}/glfw/include
)

# Link libraries (Windows MinGW case)
target_link_libraries(main PRIVATE
    ${CMAKE_SOURCE_DIR}/glfw/lib-mingw-w64/libglfw3.a
    opengl32
    gdi32
    imm32
)

# Tell CMake where to find GLFW (your prebuilt lib)
link_directories(${CMAKE_SOURCE_DIR}/glfw/lib-mingw-w64)
