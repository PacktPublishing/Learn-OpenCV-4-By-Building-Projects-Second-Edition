cmake_minimum_required (VERSION 3.0) 

PROJECT(DeepLearning_ch12)

set (CMAKE_CXX_STANDARD 11)

IF(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
ENDIF()

# Requires OpenCV v4.0 or later
FIND_PACKAGE( OpenCV 4 REQUIRED )

ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}  ${CONAN_LIBS} ${OPENCV_LIBS} -lprotobuf)
