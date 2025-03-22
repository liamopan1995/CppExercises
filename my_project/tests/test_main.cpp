#include <gtest/gtest.h>
#include "my_utils.h"

TEST(ConfigurationTest, BasicTest) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(MyStaticLibraryTest, BasicTest) {
    EXPECT_EQ(phx::FindLastSlash("myfolder/app"), 8U);
}

TEST(MyStaticLibraryTest, EmptyString) {
    EXPECT_EQ(phx::FindLastSlash(""), std::string::npos);
}

TEST(MyStaticLibraryTest, NoSlash) {
    EXPECT_EQ(phx::FindLastSlash("abcdef"), std::string::npos);
}

TEST(MyStaticLibraryTest, SingleSlash) {
    EXPECT_EQ(phx::FindLastSlash("/"), 0U);
}

TEST(MyStaticLibraryTest, MultipleSlashes) {
    EXPECT_EQ(phx::FindLastSlash("/////"), 4U);
}

TEST(MyStaticLibraryTest, SlashAtEnd) {
    EXPECT_EQ(phx::FindLastSlash("path/to/file/"), 12U);
}

TEST(MyStaticLibraryTest, SlashAtStart) {
    EXPECT_EQ(phx::FindLastSlash("/home/user"), 5U);
}

TEST(MyStaticLibraryTest, OnlyOneSlashAtStart) {
    EXPECT_EQ(phx::FindLastSlash("/abc"), 0U);
}

TEST(MyStaticLibraryTest, OnlyOneSlashInMiddle) {
    EXPECT_EQ(phx::FindLastSlash("abc/def"), 3U);
}

TEST(MyStaticLibraryTest, OnlyOneSlashAtEnd) {
    EXPECT_EQ(phx::FindLastSlash("abc/"), 3U);
}

TEST(MyStaticLibraryTest, ConsecutiveSlashes) {
    EXPECT_EQ(phx::FindLastSlash("home//user///docs"), 12U);
}

TEST(MyStaticLibraryTest, LargeStringWithSlash) {
    std::string largeStr(1000, 'a');
    largeStr[500] = '/';
    EXPECT_EQ(phx::FindLastSlash(largeStr), 500U);
}

TEST(MyStaticLibraryTest, LargeStringWithoutSlash) {
    std::string largeStr(1000, 'a');
    EXPECT_EQ(phx::FindLastSlash(largeStr), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}