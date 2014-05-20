# File: CMakeListst.txt for module ScopeLogger
PROJECT(ScopeLogger)

FIND_PACKAGE(MRPT REQUIRED base gui obs maps)  # Use MRPT

SET(wxWidgets_USE_LIBS base core adv aui)
FIND_PACKAGE(wxWidgets) # Not "required"!! -> skip module if not found

#LINK_DIRECTORIES( ${MOOS_LIBRARY_DIRS} )

IF(wxWidgets_FOUND)
	INCLUDE(${wxWidgets_USE_FILE})

	# Add executable
	ADD_EXECUTABLE( ${PROJECT_NAME} WIN32
		CScopeApp.h CScopeApp.cpp
		ScopeWindowApp.cpp ScopeWindowApp.h
		ScopeWindowMain.cpp ScopeWindowMain.h 
		)

	# Link the executable
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${MOOS_LIBRARIES} ${MRPT_LIBS} ${wxWidgets_LIBRARIES})

ELSE(wxWidgets_FOUND)
	MESSAGE("[${PROJECT_NAME}] **Warning**: wxWidgets libs not found, this module won't be built!")
ENDIF(wxWidgets_FOUND)

