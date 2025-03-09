#include <gtest/gtest.h>
// #include "my_utils.h"  // 假设这是你的库的头文件

TEST(MyLibraryTest, BasicTest) {
    EXPECT_EQ(1 + 1, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}