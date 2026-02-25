#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;
bool skipToken(const string& token) {
    // Check for URL indicators
    if (token.find("http://") != string::npos || token.find("https://") != string::npos || token.find("www.") != string::npos) {
        return true;
    }
    // Check for unwanted characters
    if (token.find("<") != string::npos || token.find('>') != string::npos || token.find('#') != string::npos) {
        return true;
    }

    bool hasDigit = false;
	bool hasAlpha = false;
    
    for (char c : token) {
        if (isdigit(c)) {
            hasDigit = true;
        }
        if (isalpha(c)) {
            hasAlpha = true;
        }
    }
    // Skip tokens that contain digits but no letters
    if (hasDigit && !hasAlpha) {
        return true;
	}

    // skip mixed like 26th
    if (hasDigit && hasAlpha) {
        return true;
	}

	return false;
}

string cleanWord(const string& raw) {
    string cleaned;

    for (size_t i = 0; i < raw.length(); i++) {
        char c = raw[i];

        if (isalpha(c)) {
            cleaned += tolower(c);   // turn cleaned word to lowercase
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
		if (skipToken(word)) {
            continue; // skip this token and move to the next one
		}
        
        // now print out cleaned words
        string cleaned = cleanWord(word);
        if (!cleaned.empty()) {
            dictionary.push_back(cleaned);
        }
    }

    // Sort words alphabetically
    sort(dictionary.begin(), dictionary.end());

    // remove duplicates
    dictionary.erase(unique(dictionary.begin(), dictionary.end()), dictionary.end());

    // Write sorted words to output file
    for (const string& w : dictionary) {
        outpfile << w << endl;
    }

    inpfile.close();
    outpfile.close();

    return 0;
}
   