# Compute paths
get_filename_component( PROJECT_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH )
SET( Pangolin_INCLUDE_DIRS "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/include;/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/src/include;/usr/include;/usr/include;/usr/include;/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/eigen" )
SET( Pangolin_INCLUDE_DIR  "/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/include;/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/build-Pangolin/src/include;/usr/include;/usr/include;/usr/include;/home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/eigen" )

# Library dependencies (contains definitions for IMPORTED targets)
if( NOT TARGET pangolin AND NOT Pangolin_BINARY_DIR )
  include( "${PROJECT_CMAKE_DIR}/PangolinTargets.cmake" )
  
endif()

SET( Pangolin_LIBRARIES    pangolin )
SET( Pangolin_LIBRARY      pangolin )
SET( Pangolin_CMAKEMODULES /home/lei/Documents/Research/Guided research/nldso_photometricLoss/thirdparty/Pangolin/src/../CMakeModules )
