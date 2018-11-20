cmake_minimum_required (VERSION 3.0)

PROJECT(Chapter6)

set (CMAKE_CXX_STANDARD 11)

IF(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
ENDIF()

# Requires OpenCV
FIND_PACKAGE( OpenCV 4.0.0 REQUIRED )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE( earDetector earDetector.cpp )
TARGET_LINK_LIBRARIES( earDetector ${OpenCV_LIBS} )

ADD_EXECUTABLE( overlayFacemask overlayFacemask.cpp )
TARGET_LINK_LIBRARIES( overlayFacemask ${OpenCV_LIBS} )

ADD_EXECUTABLE( overlayMoustache overlayMoustache.cpp )
TARGET_LINK_LIBRARIES( overlayMoustache ${OpenCV_LIBS} )

ADD_EXECUTABLE( overlayNose overlayNose.cpp )
TARGET_LINK_LIBRARIES( overlayNose ${OpenCV_LIBS} )

ADD_EXECUTABLE( overlaySunglasses overlaySunglasses.cpp )
TARGET_LINK_LIBRARIES( overlaySunglasses ${OpenCV_LIBS} )