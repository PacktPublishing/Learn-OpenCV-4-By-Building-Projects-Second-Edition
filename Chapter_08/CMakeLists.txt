cmake_minimum_required (VERSION 3.0)

PROJECT(Chapter6)

set (CMAKE_CXX_STANDARD 11)

# Requires OpenCV
FIND_PACKAGE( OpenCV 4.0.0 REQUIRED )
MESSAGE("OpenCV version : ${OpenCV_VERSION}")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

ADD_EXECUTABLE( backgroundSubtraction backgroundSubtraction.cpp )
TARGET_LINK_LIBRARIES( backgroundSubtraction ${OpenCV_LIBS} )

ADD_EXECUTABLE( dilation dilation.cpp )
TARGET_LINK_LIBRARIES( dilation ${OpenCV_LIBS} )

ADD_EXECUTABLE( erosion erosion.cpp )
TARGET_LINK_LIBRARIES( erosion ${OpenCV_LIBS} )

ADD_EXECUTABLE( frameDifferencing frameDifferencing.cpp )
TARGET_LINK_LIBRARIES( frameDifferencing ${OpenCV_LIBS} )

ADD_EXECUTABLE( morphologicalOperations morphologicalOperations.cpp )
TARGET_LINK_LIBRARIES( morphologicalOperations ${OpenCV_LIBS} )