# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(ZXING_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/zxing_src/build)
#set(ZBAR_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/KS_BarcodeReader)
set(ZBAR_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#set(IMAGE_MAGICK_PATH /home/kszkudla/workspace/ImageMagick)
#set(IMAGE_MAGICK_PATH /usr)

# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )
find_package( ImageMagick COMPONENTS Magick++ REQUIRED )

#find_package(SCons)

ADD_SUBDIRECTORY(zxing_src)

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

include_directories( . Base Core Common Types ${Boost_INCLUDE_DIR} ${ImageMagick_Magick++_INCLUDE_DIR})
# ${IMAGE_MAGICK_PATH}/include/ImageMagick/)
#/home/kszkudla/workspace/ImageMagick/include/ImageMagick/)

# Create an executable file from sources:
ADD_LIBRARY(KS_BarcodeReader SHARED ${files})
TARGET_LINK_LIBRARIES(KS_BarcodeReader ${OpenCV_LIBS} ${DisCODe_LIBRARIES} ${ImageMagick_Magick++_LIBRARY} ${ZXING_LIB_PATH}/libzxing.so ${ZBAR_LIB_PATH}/libzbar.so.0.2.0)
#${IMAGE_MAGICK_PATH}/lib/libMagick++.so 
#${ZGING_LIB_PATH}/libzxing_32.so)

INSTALL_COMPONENT(KS_BarcodeReader)
