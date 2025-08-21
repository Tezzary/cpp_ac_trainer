mkdir build

g++ ^
imgui/imgui.cpp ^
imgui/imgui_draw.cpp ^
imgui/backends/imgui_impl_glfw.cpp ^
imgui/backends/imgui_impl_opengl3.cpp ^
imgui/imgui_widgets.cpp ^
imgui/imgui_tables.cpp ^
src/*.cpp ^
-Iimgui ^
-Iimgui/backends ^
-Iglfw/include ^
-Lglfw/lib-mingw-w64 ^
-lglfw3 -lopengl32 -lgdi32 -limm32 ^
-o build/main.exe


.\build\main.exe