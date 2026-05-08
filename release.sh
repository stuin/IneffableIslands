lib_files="Skyrmion/include/imgui/*.cpp Skyrmion/include/backward-cpp/backward.cpp Skyrmion/include/rlImGui/rlImGui.cpp"
files="src/main.cpp src/Skyrmion/*/*.cpp src/Skyrmion/core/backend/RaylibUpdateList.cpp $lib_files"

options="-pthread -O3 -std=c++17 -Wall -fpermissive"
windows_libs="-static -DSFML_STATIC -mwindows -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lgdi32 -lopengl32 -lfreetype"
linux_libs="-lsfml-graphics -lsfml-window -lsfml-system -lX11"
web_libs="-Os -Wall -std=c++17 src/Skyrmion/include/libnoise/build/src/libnoise-static.a src/Skyrmion/include/raylib/src/libraylib.web.a -I. -Isrc/Skyrmion/include/raylib/src/ -Isrc/Skyrmion/include/imgui -L. -Lsrc/Skyrmion/include/raylib/src/libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY --shell-file src/Skyrmion/include/raylib/src/minshell.html --preload-file res -DPLATFORM_WEB"

output="IneffableIslands"

windows_cmd="x86_64-w64-mingw32-g++ $files -o $output.exe $options $windows_libs"
linux_cmd="g++ $files -o $output.out $options $linux_libs"
web_cmd="em++ -o game.html p $files $web_libs"

echo $windows_cmd
$windows_cmd

echo $linux_cmd
$linux_cmd

echo $web_cmd
$web_cmd

#web="em++ -o game.html src/Skyrmion/include/imgui/*.cpp src/Skyrmion/include/backward-cpp/backward.cpp src/Skyrmion/include/rlImGui/rlImGui.cpp src/*.cpp src/Skyrmion/*/*.cpp src/Skyrmion/core/backend/RaylibUpdateList.cpp src/Skyrmion/core/backend/nullClient.cpp src/Skyrmion/include/libnoise/src/*.cpp src/Skyrmion/include/libnoise/src/model/*.cpp src/Skyrmion/include/libnoise/src/module/*.cpp  -Os -Wall -std=c++17 src/Skyrmion/include/raylib/src/libraylib.web.a -I. -Isrc/Skyrmion/include/raylib/src/ -Isrc/Skyrmion/include/imgui -Isrc/Skyrmion/include/libnoise/src/noise/ -L. -Lsrc/Skyrmion/include/raylib/src/libraylib.web.a -s USE_GLFW=3 -s ASYNCIFY --shell-file src/Skyrmion/include/raylib/src/minshell.html --preload-file res -DPLATFORM_WEB"

echo "Done, Creating zip"
mv res/settings.json dev_settings.json
cp res/default_settings.json res/settings.json
zip -r "$output.zip" "$output.*" res/
mv dev_settings.json res/settings.json

