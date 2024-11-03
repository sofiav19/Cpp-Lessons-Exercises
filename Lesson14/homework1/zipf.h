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
#include <sstream>
#include <matplot/matplot.h>

namespace homework{

    /**
     * @brief Reads a book file and extracts alphabetic and space characters.
     * @param wfileName The file path of the book in wide string format for UTF-8 support.
     * @return A vector of wide characters containing only alphabetic and space characters.
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
     * @brief Reads a book file and extracts alphabetic and space characters.
     * @param wfileName The file path of the book in wide string format for UTF-8 support.
     * @return A vector of wide characters containing only alphabetic and space characters.
     */
    std::vector<std::pair<std::wstring, int>> computeWordFrequency(const std::vector<wchar_t>& book) {
        std::vector<std::pair<std::wstring, int>> wordFrequency;
        std::wstring word;
        std::wstringstream ss;
        
        for (wchar_t c : book) {
            ss << c;
        }

        while (ss >> word) {
            auto it = std::find_if(wordFrequency.begin(), wordFrequency.end(),
                                   [&word](const std::pair<std::wstring, int>& pair) {
                                       return pair.first == word;
                                   });
            if (it != wordFrequency.end()) {
                it->second++;
            } else {
                wordFrequency.emplace_back(word, 1);
            }
        }
        return wordFrequency;
    }

    /**
     * @brief Counts the number of unique words in the book.
     * @param book A vector of wide characters representing the book's content.
     * @return The number of unique words.
     */
    int countUniqueWords(const std::vector<wchar_t>& book){
        // using std set as it will ignore duplicates
        std::vector<std::wstring> uniqueWords;
        std::wstring word;
        std::wstringstream ss;
        for (wchar_t c : book){
            ss << c;
        }
        while (ss >> word){
            if (std::find(uniqueWords.begin(), uniqueWords.end(), word) == uniqueWords.end()) {
                uniqueWords.push_back(word);
            }
        }
        return uniqueWords.size();
    }

    /**
     * @brief Sorts word frequencies in descending order.
     * @param frequencies A vector of pairs where each pair contains a word and its frequency.
     * @return The sorted vector of pairs with word frequencies in descending order.
     */
    std::vector<std::pair<std::wstring, int>> sortFrequencies(std::vector<std::pair<std::wstring, int>>& frequencies){
        std::sort(frequencies.begin(), frequencies.end(),
                  [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
                      return a.second > b.second;
                  });
        return frequencies;

    }

    /**
     * @brief Outputs word frequencies to a specified file.
     * @param sortedFrequencies A sorted vector of pairs where each pair contains a word and its frequency.
     * @param wfilename The filename for output, in wide string format for UTF-8 support.
     */
    void outputWordFrequencies(const std::vector<std::pair<std::wstring, int>>& sortedFrequencies, const std::wstring& wfilename) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string filename = converter.to_bytes(wfilename);

        std::wofstream outFile(filename);
        outFile.imbue(std::locale("es_ES.UTF-8"));

        if (!outFile.is_open()) {
            std::wcerr << L"Error opening file: " << wfilename << std::endl;
            return;
        }
        int rank = 1;
        for (const auto& [word, frequency] : sortedFrequencies) {
            outFile << rank << L" " << frequency << L" " << word << L"\n";
            rank++;
        }
        outFile.close();
    }

    /**
     * @brief Plots word frequency distributions of two datasets on a log-log scale.
     * @param freq1 The first dataset of word frequencies as a vector of pairs (word and frequency).
     * @param freq2 The second dataset of word frequencies as a vector of pairs (word and frequency).
     * @param label1 Label for the first dataset.
     * @param label2 Label for the second dataset.
     */
    void plotCombinedWordFrequencies(const std::vector<std::pair<std::wstring, int>>& freq1,
                                     const std::vector<std::pair<std::wstring, int>>& freq2,
                                     const std::string& label1,
                                     const std::string& label2) {
        using namespace matplot;

        std::vector<double> ranks1, frequencies1;
        std::vector<double> ranks2, frequencies2;

        for (size_t i = 0; i < freq1.size(); ++i) {
            ranks1.push_back(i + 1);
            frequencies1.push_back(freq1[i].second);
        }
        
        for (size_t i = 0; i < freq2.size(); ++i) {
            ranks2.push_back(i + 1);
            frequencies2.push_back(freq2[i].second);
        }

        auto fig = figure(true);
        hold(true); 

        auto p1 = loglog(ranks1, frequencies1, "-o");
        p1->color("blue");
        p1->display_name(label1);

        auto p2 = loglog(ranks2, frequencies2, "-o");
        p2->color("red");
        p2->display_name(label2);

        xlabel("Rank");
        ylabel("Frequency");
        title("Comparison of Word Frequency Distributions (Log-Log Scale)");
        legend();
        show();
    }

    /**
     * @brief Prints the number of hapax legomena (words that occur only once) and examples of them.
     * @param sortedFrequencies A vector of pairs, each containing a word and its frequency.
     */
    void printHapaxLegomena(const std::vector<std::pair<std::wstring, int>>& sortedFrequencies) {
        int hapaxCount = std::count_if(sortedFrequencies.begin(), sortedFrequencies.end(),
                                       [](const std::pair<std::wstring, int>& pair) {
                                           return pair.second == 1;
                                       });

        std::wcout << L"Number of hapax legomena (words that occur only once): " << hapaxCount << std::endl;
        std::wcout << L"Examples of hapax legomena: ";
        
        int count = 0;
        for (const auto& [word, frequency] : sortedFrequencies) {
            if (frequency == 1 && count < 10) {
                std::wcout << word << " ";
                count++;
            }
        }
        std::wcout << std::endl;
    }
}