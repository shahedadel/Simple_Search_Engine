#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

string cleanWord(const string& raw) {
    string cleaned;

    for (size_t i = 0; i < raw.length(); i++) {
        char c = raw[i];

        if (isalpha(c)) {
            cleaned += c;   // preserve case (for now)
        }
        else if (c == '-' && i > 0 && i < raw.length() - 1 && isalpha(raw[i - 1]) && isalpha(raw[i + 1])) {
            cleaned += c;
        }
    }
    return cleaned;
}

int main() {
    ifstream inpfile("samplewiki.txt");
    ofstream outpfile("dictionary.txt");

	// first, make sure that the files were opened successfully
    if (!inpfile.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        throw runtime_error("Input file failed to open");
    }
    if (!outpfile.is_open()) {
        cerr << "Error: Could not open output file!" << endl;
        throw runtime_error("Output file failed to open");
    }

    vector<string> dictionary;
    string word;

    // Read word by word
    while (inpfile >> word) {
		// first, reject URL indicators. Used npos to check if the substring is not found in the word. if it is found, npos will return a valid index, which means we should skip this word.
        if (word.find("http://") != string::npos || word.find("https://") != string::npos || word.find("www.") != string::npos) {
            continue;
		}
        // there are other word slops that must be detected and wiped like "ltonlyincludegtltonlyincludegt"
        if (word.find("<") != string::npos || word.find('>') != string::npos || word.find('#') != string::npos) {
            continue;
		}
        // now print out cleaned words
        string cleaned = cleanWord(word);
        if (!cleaned.empty()) {
            dictionary.push_back(cleaned);
        }
    }

    // Sort words alphabetically
    sort(dictionary.begin(), dictionary.end());

    // Write sorted words to output file
    for (const string& w : dictionary) {
        outpfile << w << endl;
    }

    inpfile.close();
    outpfile.close();

    return 0;
}
