cmake_minimum_required (VERSION 3.0) 

PROJECT(Segment_text_ch10)

set (CMAKE_CXX_STANDARD 11)

IF(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
ENDIF()

# Requires OpenCV v4.0 or later
FIND_PACKAGE( OpenCV 4 REQUIRED )

find_package( PkgConfig REQUIRED)

pkg_search_module( TESSERACT REQUIRED tesseract )

pkg_search_module( LEPTONICA REQUIRED lept )

include_directories( ${TESSERACT_INCLUDE_DIRS} )

include_directories( ${LEPTONICA_INCLUDE_DIRS} )

link_directories( ${TESSERACT_LIBRARY_DIRS} )

link_directories( ${LEPTONICA_LIBRARY_DIRS} )

include_directories( ${OpenCV_INCLUDE_DIRS} )

ADD_EXECUTABLE( segment segment.cpp )
TARGET_LINK_LIBRARIES( segment  ${CONAN_LIBS} ${OpenCV_LIBS})

ADD_EXECUTABLE( segmentOcr segmentOcr.cpp )
TARGET_LINK_LIBRARIES( segmentOcr  ${CONAN_LIBS} ${OpenCV_LIBS} ${TESSERACT_LIBRARIES} ${LEPTONICA_LIBRARIES})

ADD_EXECUTABLE( segmentOcrHigh segmentOcrHigh.cpp )
TARGET_LINK_LIBRARIES( segmentOcrHigh  ${CONAN_LIBS} ${OpenCV_LIBS} ${TESSERACT_LIBRARIES} ${LEPTONICA_LIBRARIES})
