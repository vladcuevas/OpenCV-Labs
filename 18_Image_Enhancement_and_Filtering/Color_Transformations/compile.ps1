mkdir build
Set-Location build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
Set-Location ..