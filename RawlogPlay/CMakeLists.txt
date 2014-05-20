# File: CMakeListst.txt for module RawlogPlay
PROJECT(RawlogPlay)

# Use MRPT:
FIND_PACKAGE( MRPT REQUIRED obs) # hmtslam hwdrivers ... any other sub-library

# Add executable
ADD_EXECUTABLE( ${PROJECT_NAME}
	main.cpp
	CRawlogPlayApp.h CRawlogPlayApp.cpp
	)

# Link the executable
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${MOOS_LIBRARIES} ${MRPT_LIBS} )
