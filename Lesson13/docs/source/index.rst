Homwrok 03 November documentation
===================================

C++ application designed to explore and analyze text data through the lens of Zipf's law. Zipf's law states that in a large corpus of natural language, the frequency of any word is inversely proportional to its rank in the frequency table. This project takes a text file as input, processes it, and produces insights into word usage patterns by computing and visualizing word frequencies. 
Project Modules
----------------

The following functions are documented in this project:

* `readBook` - Reads a text file and extracts alphabetic and space characters.
* `computeWordFrequency` - Computes the frequency of each unique word in a text.
* `countUniqueWords` - Counts the number of unique words in a text.
* `sortFrequencies` - Sorts word frequencies in descending order.
* `outputWordFrequencies` - Outputs word frequencies to a specified file.
* `plotCombinedWordFrequencies` - Plots word frequency distributions for two datasets.
* `printHapaxLegomena` - Prints hapax legomena (words that occur only once) from the text.

API Documentation
-----------------
.. doxygenfile:: zipf.h
   :project: MyVeryCoolProject

Cool C++ image:

.. image:: https://isocpp.org/assets/images/cpp_logo.png
   :alt: C++ logo
   :align: center

   

