#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

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
    ofstream dictfile("dictionary.txt");
    ofstream unifile("unigrams.txt");


    // first, make sure that the files were opened successfully
    if (!inpfile.is_open()) {
        cerr << "Error: Could not open input file!" << endl;
        return 1;
    }
    if (!dictfile.is_open() || !unifile.is_open()) {
        cerr << "Error: Could not open output files!" << endl;
        return 1;
    }

    unordered_map<string, int> globalTF;
    unordered_map<string, int> documentFrequency;
    unordered_set<string> wordsInCurrentDoc;
    string word;

    // Read word by word
    while (inpfile >> word) {
        if (word.find("https://") != string::npos || word.find("http://") != string::npos || word.find("www.") != string::npos) {
            for (const auto& w : wordsInCurrentDoc) {   // update doc freq for each unique word in the current doc
                documentFrequency[w]++;
            }
            wordsInCurrentDoc.clear();  // clear set for the next doc
            continue;
        }
        if (skipToken(word)) {
            continue;
        }
        // now print out cleaned words
        string cleaned = cleanWord(word);
        if (cleaned.empty()) {
            continue;
        }
        globalTF[cleaned]++;  // count term freq for the cleaned word
        wordsInCurrentDoc.insert(cleaned);  //track unique words in the current doc
    }

    for (const auto& word : wordsInCurrentDoc) {  // update doc freq for the LAST doc 
        documentFrequency[word]++;
    }

    vector<string> dictionary;
    for (const auto& pair : globalTF) {      //pair.first is the word, and ill use pair.second as the freq
        dictionary.push_back(pair.first);
    }
    sort(dictionary.begin(), dictionary.end());

    for (const auto& word : dictionary) {
        dictfile << word << endl;
    }

    unordered_map<string, int> wordCode;   // word codes
    for (int i = 0; i < dictionary.size(); i++) {
        wordCode[dictionary[i]] = i;
    }

    vector<pair<string, int>> words;

    for (const auto& pair : globalTF) {
        words.push_back({ pair.first, pair.second });
    }

    sort(words.begin(), words.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;     // GTF is decreasing
        }   
    );

    for (const auto& pair : words) {
        string word = pair.first;
        int gtf = pair.second;
        int df = documentFrequency[word];
        int code = wordCode[word];

        unifile << code << " " << word << " " << df << " " << gtf << endl;
    }

    inpfile.close();
    dictfile.close();
    unifile.close();

    return 0;
}
   