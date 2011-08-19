# =======================================================================
# zxing lib support
# =======================================================================

#find_package(SCons)
#
#IF(SCONS_EXEC)
#
#    message(STATUS "Building zxing")
#
#    ADD_CUSTOM_TARGET(
#        zxing ALL
#        COMMAND ${SCONS_EXEC} lib
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#        COMMENT "Kompilacja zxing" 
#    )
#
#    install(
#      FILES ${CMAKE_CURRENT_SOURCE_DIR}/build/libzxing.so
#      DESTINATION lib
#    )
#
#ENDIF(SCONS_EXEC)

file(GLOB_RECURSE source_files ${CMAKE_CURRENT_SOURCE_DIR}/core/src/zxing/*.cpp )
#file(GLOB_RECURSE include_files ${CMAKE_CURRENT_SOURCE_DIR}/core/src/zxing/*.h )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/core/src/)

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/core/src/ DESTINATION include FILES_MATCHING PATTERN "*.h")

add_library(zxing SHARED ${source_files})

install(
    TARGETS zxing
	RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)