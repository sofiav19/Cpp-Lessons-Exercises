#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include "zipf.h"  // Adjust the path accordingly

using namespace homework;
// Test case for computeWordFrequency
TEST(ZipfTest, ComputeWordFrequency) {
    std::vector<wchar_t> testText = {L'H', L'e', L'l', L'l', L'o', L' ', L'w', L'o', L'r', L'l', L'd'};
    auto frequencyMap = computeWordFrequency(testText);

    EXPECT_EQ(frequencyMap[L"Hello"], 1);  // "Hello" occurs once
    EXPECT_EQ(frequencyMap[L"world"], 1);  // "world" occurs once
    EXPECT_EQ(frequencyMap.size(), 2);     // Expect 2 unique words
}

// Test case for countUniqueWords
TEST(ZipfTest, CountUniqueWords) {
    std::vector<wchar_t> testText = {L'T', L'e', L's', L't', L' ', L'T', L'e', L's', L't', L' ', L'C', L'a', L's', L'e'};
    int uniqueWordCount = countUniqueWords(testText);

    EXPECT_EQ(uniqueWordCount, 2);  // Only 2 unique words: "Test" and "Case"
}
