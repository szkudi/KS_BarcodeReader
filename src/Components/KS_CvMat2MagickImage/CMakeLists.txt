# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(IMAGE_MAGICK_PATH /home/kszkudla/workspace/ImageMagick)
set(IMAGE_MAGICK_PATH /usr)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE( ImageMagick COMPONENTS Magick++ REQUIRED )

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR} ${ImageMagick_Magick++_INCLUDE_DIR}) 
#${IMAGE_MAGICK_PATH}/include/ImageMagick/)

# Create an executable file from sources:
ADD_LIBRARY(KS_CvMat2MagickImage SHARED ${files})
TARGET_LINK_LIBRARIES(KS_CvMat2MagickImage ${OpenCV_LIBS} ${DisCODe_LIBRARIES} ${ImageMagick_Magick++_LIBRARY}) 
#${IMAGE_MAGICK_PATH}/lib/libMagick++.so)

INSTALL_COMPONENT(KS_CvMat2MagickImage)
