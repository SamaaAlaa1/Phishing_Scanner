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
    //top common words and phrases in phishing emails
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
            {"login", 2},
            {"congratulations", 2},
            {"you have won", 3},
            {"claim your prize", 3},
            {"limited time offer", 3},
            {"act now", 3},
            {"risk-free", 2},
            {"exclusive deal", 3},
            {"confirm your account", 3},
            {"click to verify", 3},
            {"update your information", 3},
            {"suspicious activity", 3},
            {"security alert", 3},
            {"unable to verify", 3},
            {"reset your password", 3},
            {"urgent action required", 3},
            {"your account has been suspended", 3},
            {"immediate attention needed", 3},
            {"verify your identity", 3},
            {"account verification", 3},
            {"please respond", 2},
            {"thank you for your cooperation", 2},
            {"provide your details", 3},
            {"we need your help", 2},
            {"this is not a scam", 2},
            {"your invoice", 2},
            {"unexpected payment", 3},
            {"referral bonus", 2},
            {"urgent: update required", 3},
            {"please verify",3}
    };
    //handling opening the text file
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
    //convert the content of the mail to lowercase
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    content = toLowerCase(content);

    unordered_map<string, int> termCounts;
    int totalPoints = 0;
    //check for phishing
    for (const auto &term : phishingTerms) {
        size_t pos = content.find(term.first);
        while (pos != string::npos) {
            termCounts[term.first] += term.second;
            totalPoints += term.second;
            pos = content.find(term.first, pos + 1);
        }
    }

    // print the results
    cout << left << setw(50) << "Term" << "Points" << endl;
    cout << string(60, '-') << endl;
    for (const auto &entry : termCounts) {
        cout << left << setw(50) << entry.first << entry.second << endl;
    }
    cout << string(60, '-') << endl;
    cout << "Total Phishing Score: " << totalPoints << endl;
    file.close();
}

int main() {
  cout << "Enter the name of the file to scan: ";
  string file;
  getline(cin ,file);
  phishingScanner(file);
  return 0;
}
