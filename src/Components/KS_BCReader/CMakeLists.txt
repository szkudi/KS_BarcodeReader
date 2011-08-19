# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR}) 

# Create an executable file from sources:
ADD_LIBRARY(KS_BCReader SHARED ${files})
TARGET_LINK_LIBRARIES(KS_BCReader ${OpenCV_LIBS} ${DisCODe_LIBRARIES} ) 

INSTALL_COMPONENT(KS_BCReader)
