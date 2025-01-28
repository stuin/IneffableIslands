files="src/main.cpp src/Skyrmion/*/*.cpp"
options="-pthread -O3 -std=c++17 -Wall -fpermissive"
windows_libs="-static -DSFML_STATIC -mwindows -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype"
linux_libs="-lsfml-graphics -lsfml-window -lsfml-system -lX11"

output="IneffableIslands"

windows_cmd="x86_64-w64-mingw32-g++ $files -o $output.exe $options $windows_libs"
linux_cmd="g++ $files -o $output.out $options $linux_libs"

echo $windows_cmd
$windows_cmd

echo $linux_cmd
$linux_cmd

em++ -o game.html src/main.cpp src/Skyrmion/core/Node.cpp src/Skyrmion/core/UpdateList.cpp src/Skyrmion/core/Vector.cpp src/Skyrmion/debug/DebugTools.cpp src/Skyrmion/debug/ImguiTools.cpp src/Skyrmion/input/InputHandler.cpp src/Skyrmion/input/Keymap.cpp src/Skyrmion/input/MovementSystems.cpp src/Skyrmion/tiling/GridMaker.cpp src/Skyrmion/tiling/LightMap.cpp src/Skyrmion/tiling/SquareTiles.cpp src/Skyrmion/include/imgui/imgui.cpp src/Skyrmion/include/imgui/imgui_demo.cpp src/Skyrmion/include/imgui/imgui_draw.cpp src/Skyrmion/include/imgui/imgui_tables.cpp src/Skyrmion/include/imgui/imgui_widgets.cpp src/Skyrmion/include/backward-cpp/backward.cpp src/Skyrmion/include/rlImGui/rlImGui.cpp src/Skyrmion/include/libnoise/build/src/libnoise-static.a -Os -Wall -std=c++17 src/Skyrmion/include/raylib/src/libraylib.web.a -I. -Isrc/Skyrmion/include/raylib/src/ -Isrc/Skyrmion/include/imgui -L. -Lsrc/Skyrmion/include/raylib/src/libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY --shell-file src/Skyrmion/include/raylib/src/minshell.html --preload-file res -DPLATFORM_WEB


echo "Done, Creating zip"
mv res/settings.json dev_settings.json
cp res/default_settings.json res/settings.json
zip -r "$output.zip" "$output.*" res/
mv dev_settings.json res/settings.json

