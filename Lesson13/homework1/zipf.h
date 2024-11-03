#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <locale>
#include <codecvt>
#include <iostream>
#include <fstream>
#include <matplot/matplot.h>

namespace homework{

    /**
     * @brief Reads a book file and extracts alphabetic and space characters.
     * 
     * This function reads a text file and extracts alphabetic and whitespace characters,
     * which are stored in a vector of wide characters.
     * 
     * @param wfileName The wide-string filename of the book to be read.
     * @return std::vector<wchar_t> A vector containing the alphabetic and space characters from the book.
     */
    std::vector<wchar_t> readBook(const std::wstring wfileName){
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string fileName = converter.to_bytes(wfileName);

        std::wifstream file(fileName);
        file.imbue(std::locale("es_ES.UTF-8")); 

        std::vector<wchar_t> book;
        if (!file) {
            std::wcerr << L"Error opening file" << std::endl;
            return book;
        }

        wchar_t c;
        while (file.get(c)) {
            // Use global locale, no need to pass it as an argument
            if (std::iswalpha(c)) {
                book.push_back(c);
            } else if (std::iswspace(c)) {
                book.push_back(L' ');
            }
        }
        return book;
    }

    /**
     * @brief Computes the frequency of each unique word in a text.
     * 
     * This function counts the frequency of each word in a text represented by a vector of characters,
     * storing the results in a map where keys are words and values are their frequencies.
     * 
     * @param book A vector of characters representing the book text.
     * @return std::map<std::wstring, int> A map with each word and its corresponding frequency.
     */
    std::map<std::wstring, int> computeWordFrequency(const std::vector<wchar_t>&book){
        // using std map as it stores the words as keys and their frequency as values
        std::map<std::wstring, int> wordFrequency;
        std::wstring word;
        std::wstringstream ss;
        for (wchar_t c : book){
            ss << c;
        }

        while (ss>>word){
            wordFrequency[word]++;
        }
        return wordFrequency;
    }

    /**
     * @brief Counts the number of unique words in a text.
     * 
     * This function uses a set to count unique words from a vector of characters representing text.
     * 
     * @param book A vector of characters representing the book text.
     * @return int The count of unique words in the text.
     */
    int countUniqueWords(const std::vector<wchar_t>& book){
        // using std set as it will ignore duplicates
        std::set<std::wstring> uniqueWords;
        std::wstring word;
        std::wstringstream ss;
        for (wchar_t c : book){
            ss << c;
        }
        while (ss >> word){
            uniqueWords.insert(word);
        }
        return uniqueWords.size();
    }

    /**
     * @brief Sorts word frequencies in descending order.
     * 
     * This function takes a map of word frequencies and sorts it into a multimap,
     * ordered by frequency in descending order.
     * 
     * @param frequencies A map of words and their corresponding frequencies.
     * @return std::multimap<int, std::wstring, std::greater<>> A sorted multimap with frequencies as keys and words as values.
     */
    std::multimap<int, std::wstring, std:: greater<>> sortFrequencies(const std::map<std::wstring, int>& frequencies){
        std::multimap<int, std::wstring, std:: greater<>> sortedFrequencies;
        for (const auto& pair : frequencies){
            sortedFrequencies.insert({pair.second, pair.first});
        }
        return sortedFrequencies;
    }

    /**
     * @brief Outputs word frequencies to a specified file.
     * 
     * This function writes the sorted word frequencies to a file, with each line containing the word rank, frequency, and the word itself.
     * 
     * @param sortedFrequencies A multimap of sorted word frequencies.
     * @param wfilename The wide-string filename to which the word frequencies will be saved.
     */
    void outputWordFrequencies(const std::multimap<int, std::wstring, std:: greater<>>& sortedFrequencies, const std::wstring& wfilename) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string filename = converter.to_bytes(wfilename);

        std::wofstream outFile(filename);
        outFile.imbue(std::locale("es_ES.UTF-8"));

        if (!outFile.is_open()) {
            std::wcerr << L"Error opening file: " << wfilename << std::endl;
            return;
        }
        int rank = 1; // Start rank at 1 for log-log plot visibility
        for (const auto& [frequency, word] : sortedFrequencies) {
            outFile << rank << L" " << frequency << L" " << word << L"\n";
            rank++;
        }
        outFile.close();
    }


    /**
     * @brief Plots word frequency distributions for two datasets.
     * 
     * This function uses Matplot++ to plot two word frequency distributions on a log-log scale for comparison.
     * 
     * @param freq1 The first multimap of sorted word frequencies.
     * @param freq2 The second multimap of sorted word frequencies.
     * @param label1 The label for the first dataset in the plot.
     * @param label2 The label for the second dataset in the plot.
     */
    void plotCombinedWordFrequencies(const std::multimap<int, std::wstring, std::greater<>>& freq1,
                                    const std::multimap<int, std::wstring, std::greater<>>& freq2,
                                    const std::string& label1,
                                    const std::string& label2) {
        using namespace matplot;

        std::vector<double> ranks1, frequencies1;
        std::vector<double> ranks2, frequencies2;

        // Populate ranks and frequencies for first dataset
        int rank = 1;
        for (const auto& [frequency, word] : freq1) {
            ranks1.push_back(rank++);
            frequencies1.push_back(frequency);
        }

        // Populate ranks and frequencies for second dataset
        rank = 1;
        for (const auto& [frequency, word] : freq2) {
            ranks2.push_back(rank++);
            frequencies2.push_back(frequency);
        }

        auto fig = figure(true);
        hold(true); 
        
        // Plot the first dataset
        auto p1 = loglog(ranks1, frequencies1, "-o");
        p1->color("blue");
        p1->display_name(label1);

        // Plot the second dataset
        auto p2 = loglog(ranks2, frequencies2, "-o");
        p2->color("red");
        p2->display_name(label2);

        // Set labels, title, and legend
        xlabel("Rank");
        ylabel("Frequency");
        title("Comparison of Word Frequency Distributions (Log-Log Scale)");
        legend();
        show();
    }

    /**
     * @brief Prints hapax legomena (words that occur only once) from the text.
     * 
     * This function counts the number of hapax legomena in the sorted word frequencies and prints a few examples.
     * 
     * @param sortedFrequencies A multimap of sorted word frequencies.
     */
    void printHapaxLegomena(const std::multimap<int, std::wstring, std::greater<>>& sortedFrequencies) {
        int hapaxCount = 0;
        std::vector<std::wstring> examples;

        // Iterate over the sorted frequencies to find words with frequency 1
        for (const auto& [frequency, word] : sortedFrequencies) {
            if (frequency == 1) {
                hapaxCount++;
                if (examples.size() < 10) {  // Collect a few examples, like 10 words
                    examples.push_back(word);
                }
            }
        }

        // Print the number of hapax legomena
        std::wcout << hapaxCount << std::endl;

        // Print some examples of hapax legomena
        std::wcout << L"Examples of hapax legomena: ";
        for (const auto& word : examples) {
            std::wcout << word << " ";
        }
        std::wcout << std::endl;
    }
}