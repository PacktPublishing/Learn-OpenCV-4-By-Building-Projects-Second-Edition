cmake_minimum_required (VERSION 3.0) 

PROJECT(DeepLearning_ch12)

set (CMAKE_CXX_STANDARD 11)

IF(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
ENDIF()

# Requires OpenCV v4.0 or later
FIND_PACKAGE( OpenCV 4 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}  ${CONAN_LIBS} ${OpenCV_LIBS} -lprotobuf)

ADD_EXECUTABLE( ${PROJECT_NAME}_face resnet_ssd_face.cpp )
TARGET_LINK_LIBRARIES( ${PROJECT_NAME}_face  ${CONAN_LIBS} ${OpenCV_LIBS} -lprotobuf)
