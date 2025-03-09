# 添加测试可执行文件
add_executable(MyTests
    test_main.cpp
)

# 链接 GTest 和你的库
target_link_libraries(MyTests
    PRIVATE
                                        # GTest::GTest
                                        # GTest::Main

                                        # will not work
                                        # *当使用 FetchContent 下载 GTest 时，GTest 的 CMake 配置会生成目标 gtest 和 gtest_main。
                                        # 当你使用 find_package(GTest REQUIRED) 时，GTest 的 CMake 配置会生成目标 GTest::GTest 和 GTest::Main。
    gtest
    gtest_main
    # MyLibrary  # 链接你的库
)

# Optionally, add include directories
target_include_directories( MyTests PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/include  # 添加 lib/include 目录
)

# 添加测试
add_test(NAME MyTests COMMAND MyTests)