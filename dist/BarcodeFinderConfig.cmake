# This file is used when other components needs to use something provided by this DCL. 
# Provide any include paths and lib directories. Use /home/kszkudla/workspace/discode_dcl/BarcodeFinder/dist
# to point to 'dist' directory of current DCL, it'll be substituted during installation. 

# directory containing header files
SET(BarcodeFinder_INCLUDE_DIR /home/kszkudla/workspace/discode_dcl/BarcodeFinder/dist/include)
INCLUDE_DIRECTORIES(${BarcodeFinder_INCLUDE_DIR})

# directory containing libraries
SET(BarcodeFinder_LIB_DIR /home/kszkudla/workspace/discode_dcl/BarcodeFinder/dist/lib)
LINK_DIRECTORIES(${BarcodeFinder_LIB_DIR})

# list of libraries to link against when using features of BarcodeFinder
# add all additional libraries built by this dcl (NOT components)
SET(BarcodeFinder_LIBS zxing)
SET(ADDITIONAL_LIB_DIRS /home/kszkudla/workspace/discode_dcl/BarcodeFinder/dist/lib ${ADDITIONAL_LIB_DIRS})
