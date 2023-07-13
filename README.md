# OpenCV-Labs

This guide provides step-by-step instructions on how to configure OpenCV 4.8.0 on Windows 10, using PowerShell 7, Visual Studio 2022, and CMake 3.24.2.

## Installation

We'll be setting up OpenCV 4.8.0 on a Windows 10 machine, using Visual Studio 2022 and CMake 3.24.2 for building and configuring our project. In this example, we used Visual Studio 2022 Professional, but the process should be very similar for other versions.

Follow the steps below to get everything set up:

1. **Install Visual Studio 2022**: Download and install Visual Studio from the [official website](https://visualstudio.microsoft.com/vs/whatsnew/). During the installation process, select the "Desktop development with C++" workload.

2. **Install CMake 3.24.2**: CMake is a cross-platform build system. Download and install it from the [CMake official website](https://cmake.org/download/). It's recommended to install the latest stable version.

3. **Install Git**: Git is a distributed version control system that we'll use to download the source code of OpenCV. You can download it from the [Git official website](https://git-scm.com/download/win).

4. **Download OpenCV and OpenCV_Contrib**: The next step is to download the source code of OpenCV and OpenCV_Contrib. OpenCV_Contrib provides additional functionalities to OpenCV. 

   We'll use PowerShell to download these repositories. Launch PowerShell 7 and execute the following commands:

    ```powershell
    mkdir opencv-4.8.0
    cd opencv-4.8.0
    Set-Variable -Name cwd -Value (Get-Location)
    mkdir Installation

    # Clone OpenCV repository
    git clone https://github.com/opencv/opencv.git
    cd opencv
    git checkout tags/4.8.0
    cd ..

    # Clone OpenCV_Contrib repository
    git clone https://github.com/opencv/opencv_contrib.git
    cd opencv_contrib
    git checkout tags/4.8.0
    cd ..
    ```

   _Please keep the PowerShell window open as we'll continue to use it in the subsequent steps._

[1]: https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.2

---

In these instructions, `cwd` is a variable that stores the current working directory. We'll use this variable in subsequent steps. The `git checkout tags/4.8.0` command checks out the specific version (4.8.0 in this case) of the repository.

## Compile OpenCV using CMake

Using PowerShell 7, we'll execute the below commands:

```powershell
cd opencv
mkdir build
cd build
```

# Compiling OpenCV using CMake

To compile OpenCV using CMake, use the following command:

```powershell
cmake -G "Visual Studio 17 2022" -A x64 -T host=x64 -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX="$cwd\Installation" -DINSTALL_C_EXAMPLES=ON -DOPENCV_EXTRA_MODULES_PATH="$cwd\opencv_contrib\modules" -DBUILD_opencv_saliency=OFF ..
```

This command will generate the necessary build files for OpenCV. Here's what each of the options does:

- `-G "Visual Studio 17 2022"`: Generates build files for Visual Studio 2022.
- `-A x64 -T host=x64`: Specifies a 64-bit platform and toolset.
- `-DBUILD_SHARED_LIBS=OFF`: Disables the building of shared libraries (dynamic link libraries). By default, OpenCV builds both static and shared libraries. This option makes it build only static libraries.
- `-DCMAKE_INSTALL_PREFIX="$cwd\Installation"`: Specifies the installation path for the built files.
- `-DINSTALL_C_EXAMPLES=ON`: Enables the installation of C examples.
- `-DOPENCV_EXTRA_MODULES_PATH="$cwd\opencv_contrib\modules"`: Specifies the path to the OpenCV extra modules (opencv_contrib).
- `-DBUILD_opencv_saliency=OFF`: Disables the building of the saliency module.

Executing this command might take a significant amount of time depending on your system's capabilities. If you're using a laptop, it's advisable to connect the power cord during this process to avoid interruptions due to battery drain.

After successful execution of this command, a Visual Studio solution file will be generated, which you can open using Visual Studio. In the IDE, you can select either "Release" or "Debug" configuration based on your needs to proceed with the actual build process.

Please replace the path variables (`$cwd\Installation` and `$cwd\opencv_contrib\modules`) with your actual paths.    

## Building OpenCV using CMake

Once you've generated the necessary build files for OpenCV using CMake, you can proceed to build the project. You can build the project either in Debug mode or in Release mode.

### Debug Mode

To build the project in Debug mode, use the following command:

```bash
cmake --build . --config Debug --target INSTALL
```

Debug mode includes debug information in the built files and disables optimizations, making it easier to diagnose issues and debug your application.

### Release Mode

To build the project in Release mode, use the following command:

```bash
cmake --build . --config Release --target INSTALL
```

Release mode enables optimizations and excludes debug information, making your application run faster and use less disk space.

Keep in mind that both commands can take a significant amount of time to complete. The duration largely depends on your system's specifications. As a benchmark, on a high-end computer from 2022, each build should approximately take around 8 minutes.

Remember to ensure your machine is connected to a power source before initiating these builds, especially if you're using a laptop. This will help prevent any disruptions due to a potential power cut.

--- 

In these instructions, `--config` specifies the build configuration (Debug or Release), and `--target INSTALL` specifies that the INSTALL target should be built. This target copies the built files to the destination specified by `CMAKE_INSTALL_PREFIX` during the build file generation step.

---

## Setting Environment Variables for OpenCV

To ensure your system recognizes and properly interacts with OpenCV, you need to add specific paths to your environment variables. We'll need to set two environment variables: `Path` and `OPENCV_DIR`.

### Update Path Variable

The `Path` variable helps your operating system locate necessary executables and libraries. 

To add OpenCV to your `Path`, you'll append the path to the OpenCV binaries to your existing `Path` variable:

1. Replace `$cwd\Installation\x64\vc17\bin` with your actual path. For example, it might be `G:\opencv-4.8.0\Installation\x64\vc17\bin`.

    ```powershell
    PS G:\opencv-4.8.0\opencv\build> ls $cwd\Installation\x64\vc17\bin

        Directory: G:\opencv-4.8.0\Installation\x64\vc17\bin

    Mode                 LastWriteTime         Length Name
    ----                 -------------         ------ ----
    -a---           7/12/2023  7:24 PM       42366464 opencv_annotationd.exe
    -a---           7/12/2023  7:24 PM       71390208 opencv_interactive-calibrationd.exe
    -a---           7/12/2023  7:24 PM       63649792 opencv_model_diagnosticsd.exe
    -a---           7/12/2023  7:32 PM       12262400 opencv_version_win32d.exe
    -a---           7/12/2023  7:31 PM       12341760 opencv_versiond.exe
    -a---           7/12/2023  7:17 PM       26353152 opencv_videoio_ffmpeg480_64.dll
    -a---           7/12/2023  7:32 PM       45720576 opencv_visualisationd.exe
    ```

2. Append this path to your `Path` environment variable.

### Set OPENCV_DIR Variable

The `OPENCV_DIR` variable is used by many projects to locate the OpenCV installation. 

To set the `OPENCV_DIR` environment variable:

1. Create a new environment variable named `OPENCV_DIR`.

2. Set its value to the path of the OpenCV static libraries, replacing `$cwd\Installation\x64\vc17\staticlib` with your actual path. For example, it might be `G:\opencv-4.8.0\Installation\x64\vc17\staticlib`.

Please note that the exact steps to set these environment variables depend on your operating system. If you're using Windows, you can find the environment variables in the System Properties dialog (accessible via "Advanced system settings" in the System control panel). If you're using Linux or macOS, you can set environment variables in your shell startup file, such as `~/.bashrc` or `~/.bash_profile`.

---

In these instructions, `cwd` stands for the "current working directory". Replace `$cwd` with the actual path to your OpenCV installation.

## Test CMake

Save the following text as CMakeLists.txt file in the project folder

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

## Creating and Testing a Simple C++ Program

Once you have set up OpenCV and configured the necessary environment variables, you can create a simple C++ program to verify that everything is working as expected.

### Create a C++ Test Program

The following code is a simple "Hello, World!" program in C++. Save it as `main.cpp` in your project directory.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Build the Test Program

Create a new directory in your project folder to hold the build files and the compiled program. Here, we will call it the `build` directory.

Navigate to your project folder in your terminal or command prompt and run the following commands:

```powershell
mkdir build
cd build
```

Then, use CMake to generate the build files and compile the program:

```powershell
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
```

### Run the Test Program

After building the project, navigate to the `Release` directory within the `build` directory, and run the executable file, `main.exe`.

```powershell
.\Release\main.exe
```

The output should be:

```bash
Hello, World!
```

If you see the "Hello, World!" message, it means your setup is working correctly. You have successfully configured your environment to work with OpenCV, C++, CMake, and Visual Studio 2022.

---

Note: The provided PowerShell commands are for Windows systems. If you are using a different operating system, the commands might vary. If you are new to PowerShell, check the Microsoft's official documentation on how to install and use PowerShell [here][1].

[1]: https://learn.microsoft.com/en-us/powershell/scripting/install/installing-powershell-on-windows?view=powershell-7.2

---

In these instructions, `..` in the `cmake -G "Visual Studio 17 2022" -A x64 ..` command represents the parent directory of the current directory. Replace this with the actual path to the source code if necessary.

---

# Using OpenCV with Visual Studio Code

Visual Studio Code is a highly versatile and lightweight code editor that supports a wide variety of languages, including C++. Here's how you can configure it to work with OpenCV.

## Prerequisites

- OpenCV installed on your system.
- Visual Studio Code installed on your system.
- The C/C++ extension for Visual Studio Code installed. You can download it from the Visual Studio Marketplace [here](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

## Setting up Visual Studio Code for OpenCV

Visual Studio Code uses a file named `c_cpp_properties.json` to configure its C/C++ extension. This file resides in the `.vscode` folder within your workspace. We need to modify this file so that it contains the correct path to the OpenCV headers.

Follow these steps:

1. Open Visual Studio Code.
2. Open your workspace (or create a new one).
3. In the workspace directory, create a new folder named `.vscode` if it doesn't already exist.
4. Inside the `.vscode` folder, create a new file named `c_cpp_properties.json`.
5. Open `c_cpp_properties.json` and insert the following content:

    ```json
    {
        "configurations": [
            {
                "name": "Win32",
                "includePath": [
                    "${workspaceFolder}/**",
                    "C:/path/to/opencv/build/include"
                ],
                "defines": [
                    "_DEBUG",
                    "UNICODE",
                    "_UNICODE"
                ],
                "windowsSdkVersion": "10.0.19041.0",
                "compilerPath": "C:/path/to/compiler",
                "cStandard": "c17",
                "cppStandard": "c++17",
                "intelliSenseMode": "${default}"
            }
        ],
        "version": 4
    }
    ```

6. Replace `"C:/path/to/opencv/build/include"` with the path to your OpenCV's `include` directory and replace `"C:/path/to/compiler"` with the path to your C++ compiler.
    
    Example: "G:/opencv-4.8.0/Installation/include"

After you make these changes, Visual Studio Code should be able to find the OpenCV headers and you will be ready to start coding with OpenCV in Visual Studio Code.

---

If you're not sure where your OpenCV's `include` directory is, you can find it by searching for the file "core.hpp" in the directory where you installed OpenCV. The path to the directory containing this file is the path you should add to the "includePath" property.

Similarly, if you're unsure of the path to your C++ compiler, you can use the `where` command (Windows) or the `which` command (Linux/Mac) in your terminal to find it. For example, if you're using the GCC compiler, you can run `where gcc` (Windows) or `which gcc` (Linux/Mac) to find its path.