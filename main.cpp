#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
void phishingScanner(const string &fileName){
    unordered_map<string, int> phishingTerms = {
            {"verification required", 3},
            {"invoice", 3},
            {"request", 3},
            {"action required",3},
            {"document",2},
            {"vm", 2},
            {"file",2},
            {"click here",3},
            {"urgent",2},
            {"need urgent help", 3},
            {"important! Your password is about to expire", 3},
            {"action required", 3},
            {"to preform verification, click here", 3},
            {"account",2},
            {"financial",2},
            {"delivery",2},
            {"paypal", 3},
            {"ebay", 2},
            {"amazon", 2},
            {"bank", 2},
            {"payment", 2},
            {"login", 2}
    };
    ifstream file;
    try{
        file.open(fileName);
        if(!file.is_open()){
            throw runtime_error("This file couldn't be open");
        }
    } catch (const runtime_error &e){
        cerr << e.what() << endl;
        return;
    }
    unordered_map<string, int> termCounts;
    string word;
    int totalPoints = 0;

    while (file >> word) {
        word = toLowerCase(word);
        if (phishingTerms.find(word) != phishingTerms.end()) {
            termCounts[word] += phishingTerms[word];
            totalPoints += phishingTerms[word];
        }
    }
    cout << "Term                Points" << endl;
    cout << "----------------------------" << endl;
    for (const auto &entry : termCounts) {
        cout << entry.first << "            " << entry.second << endl;
    }
    cout << "----------------------------" << endl;
    cout << "Total Phishing Score: " << totalPoints << endl;

    file.close();
}

int main() {
  string file;
  getline(cin ,file);
  phishingScanner(file);
  return 0;
}
