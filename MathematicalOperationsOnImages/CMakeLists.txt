CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

PROJECT(opencv)

######################## EDIT IF REQUIRED ####################
###Uncomment the line below and specify the path to OpenCV directory i.e. the path to the OpenCVConfig.cmake file. Check the examples given below.

#SET(OpenCV_DIR Enter-the-path-of-OpenCV-installation-on-your-system)

################### OpenCV_DIR Examples  #####################

### MACOS : /usr/local/Cellar/opencv/4.1.0/share/OpenCV/

### UBUNTU : /usr/local/share/OpenCV/

### WINDOWS : C:\Users\yourname\Documents\opencv-4.1.0\build\install

##############################################################

##########   Uncomment For WINDOWS USERS ONLY    #############
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
##############################################################

###################   ***DO NOT EDIT***  #####################

#############  Common Instructions for all Users  ############

# SET (CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})
#include_directories(include)

MACRO(add_file name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS} )
ENDMACRO()

MACRO(add_lib name)
  ADD_LIBRARY(${name} ${name}.h ${name}.cpp)
ENDMACRO()

MACRO(add_exec name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
ENDMACRO()

MACRO(pack name)
  add_exec(${name})
  TARGET_LINK_LIBRARIES(${name}
                        commons
                        image_cv
                        ${OpenCV_LIBS} )
ENDMACRO()

add_lib(commons)
add_lib(image_cv)

pack(datatypeConversion)
pack(contrastEnhancement)
pack(brightnessEnhancement)
pack(pitfallsOfUsingUint8)