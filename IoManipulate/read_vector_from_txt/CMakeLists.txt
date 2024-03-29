cmake_minimum_required(VERSION 3.0.2)


project(patchworkpp)
#add_compile_options(-std=c++17)
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")



set(CMAKE_BUILD_TYPE "Debug")
# Include an additional directory where CMake should look for modules. 
list( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules )

# Find Eigen3
find_package(Eigen3 REQUIRED)
# Include Eigen3 directories
include_directories(${EIGEN3_INCLUDE_DIR})

# Find PCL 
find_package(PCL 1.7 REQUIRED)
# Include PCL directories
include_directories(${PCL_INCLUDE_DIR})

# Find Sophus
find_package(Sophus REQUIRED) 
# Include PCL directories
include_directories(${Sophus_INCLUDE_DIRS})

# Find G2O
find_package( G2O REQUIRED )
include_directories( 
    ${G2O_INCLUDE_DIRS}
)
# g2o dependency for solver : CHOLMOD
# Include CHOLMOD directories
include_directories(/usr/include/suitesparse)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Find Armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Find mlpack
include_directories(/usr/include/mlpack)
link_directories(/usr/lib/x86_64-linux-gnu) 




# Find glong
# find_package(glog REQUIRED) could not find it as the apt downloaded version of glog does not contain a cmakeconfig file
# which is necessary for find_package command to working correctly. 
include_directories("/usr/include/glog")
# Find gflag
find_package(gflags REQUIRED)



# Add the top-level project directory to the list of paths the compiler should check for include files
include_directories(${CMAKE_SOURCE_DIR})


# This is not necessary for a header only library
# add_library( read_data_as_vec_from_txt read_vector_from_txt.hpp )
# Important : include bfnn.cc as a source file for the test as well
add_executable( test test.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )

# Specify the directory for the compiler to find included header files for the "test" target
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

# linking to tbb explictly in order to use multi threading
target_link_libraries(test  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog)

add_executable( scan2scan_test_serial_processing scan2scan_test_serial_processing.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )
target_include_directories(scan2scan_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(scan2scan_test_serial_processing  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)


add_executable( taged_scan2scan_test_serial_processing taged_scan2scan_test_serial_processing.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )
target_include_directories(taged_scan2scan_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(taged_scan2scan_test_serial_processing  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)

#  testing the clustering algorithm
add_executable( cluster_taged_scan2scan_test_serial_processing cluster_taged_scan2scan_test_serial_processing.cpp bfnn.cc icp3d.cc 
icp2d.cc 
kdtree.cc 
)
target_include_directories(cluster_taged_scan2scan_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(cluster_taged_scan2scan_test_serial_processing  Eigen3::Eigen 
${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags 
${ARMADILLO_LIBRARIES} 
mlpack
g2o_core g2o_stuff g2o_types_slam2d
cholmod
)

add_executable( encapsulized_cluster_taged_scan2scan_test_serial_processing encapsulized_cluster_taged_scan2scan_test_serial_processing.cpp
 bfnn.cc icp3d.cc icp2d.cc kdtree.cc 
 PoseGraphBuilder.cpp
 )
target_include_directories(encapsulized_cluster_taged_scan2scan_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(encapsulized_cluster_taged_scan2scan_test_serial_processing  Eigen3::Eigen 
${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags 
${ARMADILLO_LIBRARIES} 
mlpack
g2o_core g2o_stuff g2o_types_slam2d
cholmod
)



add_executable( taged_scan2scan_test_serial_processing_nl taged_scan2map_test_serial_processing_nonlinear_icp.cpp icp_2d_gauss_newton.cc )
target_include_directories(taged_scan2scan_test_serial_processing_nl PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(taged_scan2scan_test_serial_processing_nl  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)




add_executable( g2o_taged_scan2scan_test_serial_processing_nl g2o_taged_scan2map_test_serial_processing_nonlinear_icp.cpp icp_2d_gauss_newton.cc )
target_include_directories(g2o_taged_scan2scan_test_serial_processing_nl PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(g2o_taged_scan2scan_test_serial_processing_nl  Eigen3::Eigen ${PCL_LIBRARIES} 
${Sophus_LIBRARIES} 
tbb  glog gflags g2o_core g2o_stuff
${ARMADILLO_LIBRARIES} 
mlpack)




add_executable( pcl_scan2scan_test_serial_processing pcl_scan2scan_test_serial_processing.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )
target_include_directories(pcl_scan2scan_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(pcl_scan2scan_test_serial_processing  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)



add_executable( pcl_scan2map_test_serial_processing pcl_scan2map_test_serial_processing.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )
target_include_directories(pcl_scan2map_test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(pcl_scan2map_test_serial_processing  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)