# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard (e.g., C++17, C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dependencies
find_package(Threads REQUIRED)

# Add an executable target
add_executable( MyApp 
    
    main.cpp 
    src/derived.cpp
    src/my_utils_dele.cpp)

# Optionally, add include directories
target_include_directories( MyApp PRIVATE include)

# Optionally, link libraries (e.g., a library named MyLibrary)
target_link_libraries( MyApp 
    PRIVATE 
    Threads::Threads
    MyLibrary
    )