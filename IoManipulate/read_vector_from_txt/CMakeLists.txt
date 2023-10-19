cmake_minimum_required(VERSION 3.0.2)


project(patchworkpp)
#add_compile_options(-std=c++17)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")

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


# Find OpenCV
find_package(OpenCV REQUIRED)
# Include PCL directories
include_directories(${OpenCV_INCLUDE_DIRS})

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

add_executable( test_serial_processing test_serial_processing.cpp bfnn.cc icp3d.cc icp2d.cc kdtree.cc )
target_include_directories(test_serial_processing PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_serial_processing  Eigen3::Eigen ${PCL_LIBRARIES} ${Sophus_LIBRARIES} tbb  glog gflags)