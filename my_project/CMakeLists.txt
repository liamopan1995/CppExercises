cmake_minimum_required(VERSION 3.10)
# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 启用测试
enable_testing()

# 查找 GTest code space 上没有提供gtest， 所以跳过查找，改为用fetch 下载和安装
# find_package(GTest REQUIRED) 

# 自动下载 GTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# 添加库和应用程序的子目录
add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(tests)