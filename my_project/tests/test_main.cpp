#include <gtest/gtest.h>
#include "my_utils.h"

TEST(ConfigurationTest, BasicTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(MyLibraryTest, BasicTest) {
    EXPECT_EQ(phx::FindLastSlash("myfolder/app"), 8U);
}

TEST(MyLibraryTest, EmptyString) {
    EXPECT_EQ(phx::FindLastSlash(""), std::string::npos);
}

TEST(MyLibraryTest, NoSlash) {
    EXPECT_EQ(phx::FindLastSlash("abcdef"), std::string::npos);
}

TEST(MyLibraryTest, SingleSlash) {
    EXPECT_EQ(phx::FindLastSlash("/"), 0U);
}

TEST(MyLibraryTest, MultipleSlashes) {
    EXPECT_EQ(phx::FindLastSlash("/////"), 4U);
}

TEST(MyLibraryTest, SlashAtEnd) {
    EXPECT_EQ(phx::FindLastSlash("path/to/file/"), 12U);
}

TEST(MyLibraryTest, SlashAtStart) {
    EXPECT_EQ(phx::FindLastSlash("/home/user"), 5U);
}

TEST(MyLibraryTest, OnlyOneSlashAtStart) {
    EXPECT_EQ(phx::FindLastSlash("/abc"), 0U);
}

TEST(MyLibraryTest, OnlyOneSlashInMiddle) {
    EXPECT_EQ(phx::FindLastSlash("abc/def"), 3U);
}

TEST(MyLibraryTest, OnlyOneSlashAtEnd) {
    EXPECT_EQ(phx::FindLastSlash("abc/"), 3U);
}

TEST(MyLibraryTest, ConsecutiveSlashes) {
    EXPECT_EQ(phx::FindLastSlash("home//user///docs"), 12U);
}

TEST(MyLibraryTest, LargeStringWithSlash) {
    std::string largeStr(1000, 'a');
    largeStr[500] = '/';
    EXPECT_EQ(phx::FindLastSlash(largeStr), 500U);
}

TEST(MyLibraryTest, LargeStringWithoutSlash) {
    std::string largeStr(1000, 'a');
    EXPECT_EQ(phx::FindLastSlash(largeStr), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}