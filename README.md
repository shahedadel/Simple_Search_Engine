# Simple_Search_Engine

A C++ program that processes a text dataset (like a Wikipedia dump) to generate a dictionary and unigrams for each word. Designed as the first step in building a search engine or text analysis pipeline.

## Purpose
 - dictionary.txt: Contains all unique words in the dataset, sorted alphabetically.
 - unigrams.txt: Contains word codes, document frequency (number of documents each word appears in), and global term frequency (total occurrences in the dataset). Sorted by decreasing global term frequency.

This program ignores URLs, HTML markup, and unwanted characters. Words are cleaned and lowercased, with hyphens preserved in words like "well-known".

## Files
simplesearchengine.cpp – the main C++ program.

samplewiki.txt – input text dataset.

dictionary.txt – output file of unique words.

unigrams.txt – output file with word codes, document frequencies, and global term frequencies.

## Requirements
C++17 compatible compiler (e.g., g++, clang++)

Standard C++ libraries. No external dependencies.

## Compilation
Open a terminal in the project directory:
g++ -std=c++17 -o simplesearchengine simplesearchengine.cpp

This creates an executable called simplesearchengine (or simplesearchengine.exe on Windows).

## Usage
./simplesearchengine        (# Mac/Linux)

simplesearchengine.exe      (# Windows)

The program will:
- Read samplewiki.txt.
- Generate dictionary.txt (sorted unique words).
- Generate unigrams.txt (word codes, document frequency, global term frequency).

### Notes
- Each URL in the input marks a new "document" for calculating document frequency.
- Words with digits, mixed alphanumeric tokens, or unwanted symbols are ignored.
- Memory usage is optimized with unordered maps and sets, but large datasets may still take some time to process.

### Example
unigrams.txt line format:

0 apple 543 3245
1 fog 341 1321

- 0, 1 → word codes
- 543, 341 → document frequency
- 3245, 1321 → global term frequency
