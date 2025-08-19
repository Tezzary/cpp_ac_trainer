mkdir build

g++ ^
imgui/imgui.cpp ^
imgui/imgui_draw.cpp ^
imgui/backends/imgui_impl_win32.cpp ^
imgui/backends/imgui_impl_dx11.cpp ^
imgui/imgui_widgets.cpp ^
imgui/imgui_tables.cpp ^
src/memory.cpp ^
src/player.cpp ^
src/utils.cpp ^
src/keymanager.cpp ^
src/main.cpp ^
-Iimgui ^
-o build/main.exe ^
-lgdi32 -ldwmapi -luser32 -ld3dcompiler

.\build\main.exe