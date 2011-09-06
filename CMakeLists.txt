cmake_minimum_required(VERSION 2.8)

PROJECT( output )

# Make sure the compiler can find include files from our Hello library. 
include_directories (/usr/local/include/opencv) 
include_directories (/usr/local/include) 
include_directories (/usr/local/lib) 

FIND_PACKAGE( OpenCV REQUIRED )

ADD_LIBRARY( bezier bezier.cpp ) 
ADD_EXECUTABLE( main main.cpp )

TARGET_LINK_LIBRARIES( main bezier )
TARGET_LINK_LIBRARIES( main ${OpenCV_LIBS} )
