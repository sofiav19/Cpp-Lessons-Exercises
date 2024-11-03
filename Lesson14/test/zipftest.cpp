#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include "zipf.h"

using namespace homework;

// Test case for computeWordFrequency
TEST(ZipfTest, ComputeWordFrequency) {
    std::vector<wchar_t> testText = {L'H', L'e', L'l', L'l', L'o', L' ', L'w', L'o', L'r', L'l', L'd'};
    auto frequencyMap = computeWordFrequency(testText);

    // Check that "Hello" occurs once
    auto helloIt = std::find_if(frequencyMap.begin(), frequencyMap.end(),
                                [](const std::pair<std::wstring, int>& pair) { return pair.first == L"Hello"; });
    EXPECT_NE(helloIt, frequencyMap.end());
    EXPECT_EQ(helloIt->second, 1);

    // Check that "world" occurs once
    auto worldIt = std::find_if(frequencyMap.begin(), frequencyMap.end(),
                                [](const std::pair<std::wstring, int>& pair) { return pair.first == L"world"; });
    EXPECT_NE(worldIt, frequencyMap.end());
    EXPECT_EQ(worldIt->second, 1);

    // Expect two unique words in total
    EXPECT_EQ(frequencyMap.size(), 2);
}

// Test case for countUniqueWords
TEST(ZipfTest, CountUniqueWords) {
    std::vector<wchar_t> testText = {L'T', L'e', L's', L't', L' ', L'T', L'e', L's', L't', L' ', L'C', L'a', L's', L'e'};
    int uniqueWordCount = countUniqueWords(testText);

    // Only "Test" and "Case" are unique
    EXPECT_EQ(uniqueWordCount, 2);
}