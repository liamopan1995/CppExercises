cmake_minimum_required(VERSION 3.10)
project(CppExercises)

# ============================================================================
# C++ 标准和编译器配置
# ============================================================================

# 设置 C++ 标准为 C++17
# CMAKE_CXX_STANDARD: 指定使用的 C++ 标准版本（11, 14, 17, 20等）
set(CMAKE_CXX_STANDARD 17)

# 如果编译器不支持指定的标准，则停止配置
# 这确保了代码在不同平台上的一致性
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译器标志：
# -g: 生成调试信息，便于使用gdb调试
# -Wall: 启用所有常见的编译器警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall")

# ============================================================================
# 输出目录配置
# ============================================================================

# CMAKE_BINARY_DIR: CMake 的构建目录（即执行 cmake .. 的目录，通常是 build/）
# 设置生成的可执行文件输出目录为 build/make_gen/
# 对应 Makefile 中的 BUILD_DIR = make_gen
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/make_gen)

# ============================================================================
# 头文件路径配置
# ============================================================================

# CMAKE_SOURCE_DIR: CMakeLists.txt 所在的目录（项目根目录）
# 添加 include 目录，使编译器能找到 #include <xx.h> 的头文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# ============================================================================
# 源文件收集
# ============================================================================

# file(GLOB_RECURSE ...) 递归搜索指定目录下的文件
# 这里搜集：
#  - main.cpp: 项目入口文件
#  - src/*.cpp: src/ 目录及其子目录中的所有 .cpp 文件
# 结果存储在 SOURCES 变量中，后续用于创建可执行文件
file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# ============================================================================
# 创建可执行文件
# ============================================================================

# add_executable(目标名 源文件)
# 目标名 "main": 最终生成的可执行文件名（不含路径，由 CMAKE_RUNTIME_OUTPUT_DIRECTORY 控制）
# SOURCES: 之前收集的所有源文件列表
add_executable(main ${SOURCES})

# ============================================================================
# 链接库配置
# ============================================================================

# target_link_libraries(目标 [PUBLIC|PRIVATE|INTERFACE] 库)
# PRIVATE: 库只供该目标内部使用（通常用于最终可执行文件）

# 链接 POSIX 线程库（对应 Makefile 中的 -pthread）
# 用于支持 C++ 多线程编程
target_link_libraries(main PRIVATE pthread)

# 链接自定义共享库 libmy_so.so
# -L${CMAKE_SOURCE_DIR}/lib: 指定库文件搜索目录
# my_so: 库名（CMake 自动展开为 libmy_so.so）
# 对应 Makefile 中的 -L ./lib/ -lmy_so
target_link_libraries(main PRIVATE 
    -L${CMAKE_SOURCE_DIR}/lib 
    my_so
)

# ============================================================================
# 运行时库路径配置（RPATH）
# ============================================================================

# set_target_properties: 为目标设置属性
# BUILD_RPATH: 编译后立即运行可执行文件时的库搜索路径
#   - 用于开发阶段，在构建目录中运行程序
#   - 指向源码树中的库目录 ${CMAKE_SOURCE_DIR}/lib
# INSTALL_RPATH: 安装后运行可执行文件时的库搜索路径
#   - 用于部署阶段，在正式环境中运行程序
#   - 这里同样指向 lib 目录

# 作用：对应 Makefile 中的 -Wl,-rpath,./lib
# 当动态链接器加载可执行文件时，会先在 BUILD_RPATH/INSTALL_RPATH 中查找依赖的共享库
# 这样运行时就不需要设置 LD_LIBRARY_PATH 环境变量
set_target_properties(main PROPERTIES
    BUILD_RPATH "${CMAKE_SOURCE_DIR}/lib"
    INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib"
)

# ============================================================================
# 自定义目标
# ============================================================================

# add_custom_target: 创建一个不产生输出的目标，用于执行自定义命令
# clean-all: 目标名称，可通过 cmake --build . --target clean-all 调用
# 功能：清除所有 CMake 生成的构建产物
#   1. ${CMAKE_MAKE_PROGRAM} clean: 调用原生构建工具的 clean 目标（通常是 make clean）
#   2. rm -rf ${CMAKE_BINARY_DIR}: 完全删除构建目录及所有内容
add_custom_target(clean-all
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
)
