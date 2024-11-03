#include "zipf.h"
#include <iostream>
using namespace homework;

int main() {
    // Specify the filename as wide string for UTF-8 support
    std::wstring filename = L"../homework1/file.txt";
    std::wstring espfilename = L"../homework1/quijote.txt";

    // Read and process the file
    std::vector<wchar_t> processedText = readBook(filename);
    std::vector<wchar_t> processedTextesp = readBook(espfilename);

    // Compute word frequency
    std::map<std::wstring, int> wordFrequency = computeWordFrequency(processedText);
    std::map<std::wstring, int> wordFrequencyesp = computeWordFrequency(processedTextesp);

    // Count unique words
    int uniqueWords = countUniqueWords(processedText);
    std::wcout << L"\nNumber of unique words: " << uniqueWords << std::endl;
    int uniqueWordsesp = countUniqueWords(processedTextesp);
    std::wcout << L"Number of unique words quijote: " << uniqueWordsesp << std::endl;

    // Sort frequencies in descending order
    std::multimap<int, std::wstring, std::greater<>> sortedFrequencies = sortFrequencies(wordFrequency);
    std::multimap<int, std::wstring, std::greater<>> sortedFrequenciesesp = sortFrequencies(wordFrequencyesp);

    // Output sorted frequencies to a file
    std::wstring outputFilename = L"../homework1/word_frequencies.txt";
    outputWordFrequencies(sortedFrequencies, outputFilename);

    std::wstring outputFilenameesp = L"../homework1/word_frequencies_quijote.txt";
    outputWordFrequencies(sortedFrequenciesesp, outputFilenameesp);

    std::wcout << std::endl;
    // Print hapax legomena
    std::wcout << L"Number of hapax legomena in Moby Dick (words that occur only once): " << std::endl;
    printHapaxLegomena(sortedFrequencies);
    std::wcout << L"Number of hapax legomena in El Quijote (words that occur only once): " << std::endl;
    printHapaxLegomena(sortedFrequenciesesp);

    // Plot word frequencies on a log-log scale
    plotCombinedWordFrequencies(sortedFrequencies, sortedFrequenciesesp, "Moby Dick", "El Quijote");

    return 0;
}