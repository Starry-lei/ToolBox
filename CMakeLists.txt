
cmake_minimum_required( VERSION 3.2 )

project(convert_rgbe)

find_package (Eigen3 3.3 REQUIRED )
include_directories(thirdparty/Sophus)
set(CMAKE_CXX_STANDARD 17)
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# include_directories(/usr/include/pcl-1.12)

message(STATUS "show PCL-----PCL_INCLUDE_DIRS: ${PCL_INCLUDE_DIRS}")
message(STATUS "show PCL-----PCL_LIBRARY_DIRS: ${PCL_LIBRARY_DIRS}")
message(STATUS "show PCL-----PCL_DEFINITIONS: ${PCL_DEFINITIONS}")

find_package(OpenCV REQUIRED COMPONENTS core features2d)
message(STATUS "Found OpenCV ${OpenCV_VERSION} headers in: ${OpenCV_INCLUDE_DIRS}")
add_library(OpenCV INTERFACE IMPORTED)
set_property(TARGET OpenCV PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OpenCV_INCLUDE_DIRS})
set_property(TARGET OpenCV PROPERTY INTERFACE_LINK_LIBRARIES ${OpenCV_LIBS})
if(OpenCV_VERSION VERSION_LESS 3)
    set_property(TARGET OpenCV PROPERTY INTERFACE_COMPILE_DEFINITIONS DBATK_OPENCV2)
endif()


find_package(Qt5 5.15 REQUIRED COMPONENTS Core OpenGL Widgets)





find_package(Boost 1.71.0 REQUIRED COMPONENTS system filesystem program_options)
include_directories( ${Boost_INCLUDE_DIRS})
link_directories( ${Boost_LIBRARY_DIRS})

#add_executable(codeTest codeTest.cpp)
#target_link_libraries(codeTest
#        OpenCV
#        ${PCL_LIBRARIES}
#        Eigen3::Eigen
#        #  ${Boost_LIBRARIES}
#        )








set(dsonl_SOURCE_FILES
        include/PFMReadWrite.cpp
        include/slic.cpp
        )

add_library(dsonl ${dsonl_SOURCE_FILES})

add_executable(convert_rgbe src/rgbereader.cpp include/toolBox.h )
add_executable(pfmReader src/pfmReader.cpp include/toolBox.h)
add_executable(radiance src/16bitRadiance.cpp include/toolBox.h)
add_executable(readHdr src/readHdr.cpp include/toolBox.h)
add_executable(test3DHash src/3DhashTest.cpp include/toolBox.h)
add_executable(radiance2RGB src/radiance2RGB.cpp include/toolBox.h)
add_executable(renameImg src/renameImages.cpp include/toolBox.h)
add_executable(envmapPrepare src/EnvMap_prepare.cpp include/toolBox.h)

target_link_libraries(envmapPrepare OpenCV  Eigen3::Eigen dsonl ${Boost_LIBRARIES})
target_link_libraries(renameImg OpenCV  Eigen3::Eigen dsonl )
target_link_libraries(test3DHash OpenCV  Eigen3::Eigen  dsonl )
target_link_libraries(convert_rgbe OpenCV  Eigen3::Eigen dsonl  )
target_link_libraries(pfmReader OpenCV  Eigen3::Eigen  dsonl)
target_link_libraries(readHdr OpenCV  Eigen3::Eigen  dsonl)
target_link_libraries(radiance2RGB OpenCV  Eigen3::Eigen  dsonl)
target_link_libraries(radiance OpenCV  Eigen3::Eigen  dsonl Qt5::Widgets Qt5::Core Qt5::OpenGL)


add_executable(pfmC3ToC1 src/pfmC3ToC1.cpp include/toolBox.h)
target_link_libraries(pfmC3ToC1 OpenCV  Eigen3::Eigen dsonl ${Boost_LIBRARIES})

add_executable(findCorrespondence src/findCorrespondence.cpp include/toolBox.h)
target_link_libraries(findCorrespondence OpenCV  Eigen3::Eigen dsonl ${Boost_LIBRARIES})


add_executable(pointSelector src/pointSelector.cpp include/toolBox.h)
target_link_libraries(pointSelector OpenCV  Eigen3::Eigen dsonl ${Boost_LIBRARIES} opencv_ximgproc)

add_executable(contolPointSelector src/controlPointSelector.cpp include/toolBox.h src/smallTest.cpp)
target_link_libraries(contolPointSelector OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})


add_executable(smallTest src/smallTest.cpp include/toolBox.h )
target_link_libraries(smallTest OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})


add_executable(saveRadianceAsPNG src/saveRadianceAsPNG.cpp)
target_link_libraries(saveRadianceAsPNG OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})

add_executable(depthProcessing src/depthProcesing.cpp)
target_link_libraries(depthProcessing OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})


add_executable(fixTrajectory src/fixTrajectory.cpp)
target_link_libraries(fixTrajectory OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})

add_executable(checkTranNormal src/transAndCheckNormal.cpp)
target_link_libraries(checkTranNormal OpenCV  Eigen3::Eigen dsonl
        ${PCL_LIBRARIES}
        ${Boost_LIBRARIES})



