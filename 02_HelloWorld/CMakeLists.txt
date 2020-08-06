############# Contents of a sample CMakeLists.txt file #############
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
add_example(main)
