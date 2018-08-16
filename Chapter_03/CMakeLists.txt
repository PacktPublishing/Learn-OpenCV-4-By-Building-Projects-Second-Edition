cmake_minimum_required (VERSION 3.0)

PROJECT(Photo_Tool)

set (CMAKE_CXX_STANDARD 11)

# Requires OpenCV
FIND_PACKAGE( OpenCV 4.0.0 REQUIRED )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample1 sample1.cpp )
TARGET_LINK_LIBRARIES( ch3_sample1 ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample2 sample2.cpp )
TARGET_LINK_LIBRARIES( ch3_sample2 ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample3 sample3.cpp )
TARGET_LINK_LIBRARIES( ch3_sample3 ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample4 sample4.cpp )
TARGET_LINK_LIBRARIES( ch3_sample4 ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample5 sample5.cpp )
TARGET_LINK_LIBRARIES( ch3_sample5 ${OpenCV_LIBS} )

ADD_EXECUTABLE( ch3_sample6 sample6.cpp )
TARGET_LINK_LIBRARIES( ch3_sample6 ${OpenCV_LIBS} )