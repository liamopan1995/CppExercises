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
    # 当使用 FetchContent 下载 GTest 时，GTest 的 CMake 配置会生成目标 gtest 和 gtest_main。
    # 当你使用 find_package(GTest REQUIRED) 时，GTest 的 CMake 配置会生成目标 GTest::GTest 和 GTest::Main。
    gtest
    gtest_main
    # MyLibrary  # 链接你的库
)

# 添加测试
add_test(NAME MyTests COMMAND MyTests)