cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 添加库和应用程序的子目录
add_subdirectory(lib)
add_subdirectory(app)