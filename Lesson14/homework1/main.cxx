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
    std::vector<std::pair<std::wstring, int>> wordFrequency = computeWordFrequency(processedText);
    std::vector<std::pair<std::wstring, int>> wordFrequencyesp = computeWordFrequency(processedTextesp);

    // Count unique words
    int uniqueWords = countUniqueWords(processedText);
    std::wcout << L"\nNumber of unique words: " << uniqueWords << std::endl;
    int uniqueWordsesp = countUniqueWords(processedTextesp);
    std::wcout << L"\nNumber of unique words in Quijote: " << uniqueWordsesp << std::endl;

    // Sort frequencies in descending order
    std::vector<std::pair<std::wstring, int>> sortedFrequencies = sortFrequencies(wordFrequency);
    std::vector<std::pair<std::wstring, int>> sortedFrequenciesesp = sortFrequencies(wordFrequencyesp);

    // Output sorted frequencies to a file
    std::wstring outputFilename = L"../homework1/word_frequencies.txt";
    outputWordFrequencies(sortedFrequencies, outputFilename);

    std::wstring outputFilenameesp = L"../homework1/word_frequencies_quijote.txt";
    outputWordFrequencies(sortedFrequenciesesp, outputFilenameesp);

    // Print hapax legomena
    printHapaxLegomena(sortedFrequencies);
    printHapaxLegomena(sortedFrequenciesesp);

    // Plot word frequencies on a log-log scale
    plotCombinedWordFrequencies(sortedFrequencies, sortedFrequenciesesp, "Moby Dick", "El Quijote");

    return 0;
}