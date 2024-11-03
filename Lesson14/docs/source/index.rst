Homwrok 03 November documentation
===================================

Homework
----------

Welcome to the documentation for the **Homework Project**, a project aimed at analyzing text data and visualizing word frequency distributions based on Zipf's law.
This project includes functions to read text from a file, compute word frequencies, count unique words, and plot word frequency distributions using `matplot++`.

The following modules are included in this documentation:

* `readBook`: Reads a book file and extracts alphabetic and space characters.
* `computeWordFrequency`: Computes the frequency of each unique word in a text.
* `countUniqueWords`: Counts the number of unique words in a text.
* `sortFrequencies`: Sorts word frequencies in descending order.
* `outputWordFrequencies`: Outputs word frequencies to a specified file.
* `plotCombinedWordFrequencies`: Plots word frequency distributions for two datasets.
* `printHapaxLegomena`: Prints hapax legomena (words that occur only once) from the text.


API Documentation
-----------------
.. doxygenfile:: zipf.h
   :project: MyVeryCoolProject


Cool C++ image:

.. image:: https://isocpp.org/assets/images/cpp_logo.png
   :alt: C++ logo
   :align: center

   

