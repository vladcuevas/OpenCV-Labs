# OpenCV-Labs

The following example explains how to configure OpenCV 4.3.0 on Windows 10, using PoweShell 7, Visual Studio 2019 and CMake 3.17.3

## Installation 

(Windows + OpenCV 4.3.0 + VS2019 + CMake 3.17.3)

1. Install [Visual Studio](https://visualstudio.microsoft.com/vs/older-downloads/), select Desktop development with C++
2. Install [CMake](https://cmake.org/download/)
3. Install [Git](https://git-scm.com/download/win)
4. Download opencv and opencv_contrib

    Using PowerShell 7:

    ```powershell
    mkdir opencv-4.3.0
    cd opencv-4.3.0
    Set-Variable -Name cwd -Value (Get-Location)
    mkdir Installation

    # Clone OpenCV_Contrib
    git clone https://github.com/opencv/opencv.git
    cd opencv
    git checkout tags/4.3.0
    cd ..

    # Clone OpenCV_Contrib
    git clone https://github.com/opencv/opencv_contrib.git
    cd opencv_contrib
    git checkout tags/4.3.0
    cd ..
    ```

    _Do not close the PowerShell, we'll use it on next step_

5. Compile OpenCV using CMake
    Using PowerShell 7:

    ```powershell
    cd opencv
    mkdir build
    cd build

    #compile OpenCV using CMake

    cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX="$cwd\Installation" -DINSTALL_C_EXAMPLES=ON -DOPENCV_EXTRA_MODULES_PATH="$cwd\opencv_contrib\modules" -DBUILD_opencv_saliency=OFF ..
    ```

6. Set environment variables  
    **Path:**  
    Add the path "$cwd\Installation\x64\vc15\bin" to your path in your [environment variables](https://www.architectryan.com/2018/08/31/how-to-change-environment-variables-on-windows-10/), replacing $cwd for the "real path" (i.e G:\opencv-4.3.0\Installation\x64\vc16\bin)

    **OPENCV_DIR**  
    Create a new OpenCV_DIR environment variable, where Variable Name will be OPENCV_DIR and the value will be "$cwd\Installation\x64\vc15\staticlib", (i.e G:\opencv-4.3.0\Installation\x64\vc16\staticlib)

## Test CMake

Save the following file as CMakeLists.txt in the project folder

```cmake
# Define the minimum CMake version which can execute this file
cmake_minimum_required(VERSION "3.17.3")

# Give a name to your project
PROJECT("myProject")

## If the library is installed on your machine, we tell CMake to find it.
# CMake looks for files OpenCVConfig.cmake and OpenCVConfig-version.cmake to 
# configure settings for OpenCV.

# There are two ways to help CMake find these OpenCV files.
# 1. Define an Environment Variable named OpenCV_DIR and give path to the folder
#    which contains files OpenCVConfig.cmake and OpenCVConfig-version.cmake
# 2. Set this variable OpenCV_DIR within CMakeLists.txt file. (Explained in Step 1)
# We will follow the second option. This way you can have multiple OpenCV
# versions on your machine but still you can point to exact OpenCV version
# you want to use for a particular project

# Find header folder and library folder for OpenCV
find_package( OpenCV REQUIRED )

# Include headers’ folders for OpenCV
include_directories( ${OpenCV_INCLUDE_DIRS})

# Now suppose we have a cpp file named, myCode.cpp
# We will write rule for compilation and linking.
# In ADD_EXECUTABLE first myCode is the name of executable 
# which will be generated when we compile our code myCode.cpp
#ADD_EXECUTABLE(myCode myCode.cpp)
#ADD_EXECUTABLE(hello hello.cpp)

# This is all we need to build our C++ code. But what if we have
# many C++ files to compile and build.
# We can write a Macro so that we don’t have to type this again and again.

#Bring the headers, such as *.h into the project
#include_directories(include)

# Define a Macro named add_example and add rules for compilation.
MACRO(add_example name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS})
ENDMACRO()

# Now we can use this macro to compile many C++ files.
# Here we are calling the name of the file for the example, main.cpp without the .cpp part because the macro adds that.
add_example(main)
```

### Create a C++ test program

Below example is the hello world example for cpp, for this example, it is saved main.cpp

```cpp
#include <iostream>

int main()
{
    std::cout << "Hellow World!" << std::endl;
}
```

### Build a test project

In the project folder, create a folder (i.e build folder).

```powershell
mkdir build
cd build

cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release
```

### Test

```powershell
PS G:\GitHub\OpenCV-Labs\build> .\Release\main.exe
Hellow World!
```

if the result is successful, we now have OpenCV configured to work with C++, CMake and Visual Studio 2019.
