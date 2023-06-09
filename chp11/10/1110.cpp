#include <iostream>
#include <string>
using namespace std;



// Function to check if a character is alphanumeric
bool isAlphanumeric(char c) {
    return ((c >= 'a' && c <= 'z') ||(c >= '0' && c <= '9'));
}

// Function to check if a character is a space
bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

// Function to remove punctuation marks (except spaces) from a string
string removePunctuation(const string& str) {
    string result;
    for (char c : str) {
        if (isAlphanumeric(c) || isSpace(c)) {
            result += c;
        }
    }
    return result;
}

// Function to convert a string to lowercase
string toLowercase(const string& str) {
    string lowercaseStr = str;
    for (char& c : lowercaseStr) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return lowercaseStr;
}

// Function to compare two titles subject to the given rules
bool compareByTitle(const string& title1, const string& title2) {
    // Convert titles to lowercase
    string lowercaseTitle1 = toLowercase(title1);
    string lowercaseTitle2 = toLowercase(title2);

    // Remove punctuation marks (except spaces)
    string cleanTitle1 = removePunctuation(lowercaseTitle1);
    string cleanTitle2 = removePunctuation(lowercaseTitle2);

    // Ignore words "a", "an", or "the" at the beginning of titles
    const string ignoredWords[] = { "a ", "an ", "the " };
    for (const string& ignoredWord : ignoredWords) {
        if (cleanTitle1.substr(0, ignoredWord.length()) == ignoredWord) {
            cleanTitle1 = cleanTitle1.substr(ignoredWord.length());
        }
        if (cleanTitle2.substr(0, ignoredWord.length()) == ignoredWord) {
            cleanTitle2 = cleanTitle2.substr(ignoredWord.length());
        }
    }

    // Compare the cleaned titles
    return cleanTitle1 == cleanTitle2;
}

int main() {
string title1 = "The Great Gatsby";
string title2 = "An Introduction to Computer Science";
string title3 = "A Tale of Two Cities";

if (compareByTitle(title1,title2)){
    cout << title1 << " is the same as " << title2 << endl;
} else {
    cout << title1 << " is different from " << title2 << endl;
}

title2 = "An Great Gatsby";
if (compareByTitle(title1,title2)) {
    cout << title1 << " is the same as " << title2 << endl;
} else {
    cout << title1 << " is different from " << title2 << endl;
}

title2 = "An the Great Gatsby";
if (compareByTitle(title1,title2)) {
    cout << title1 << " is the same as " << title2 << endl;
} else {
    cout << title1 << " is different from " << title2 << endl;
}


return 0;
}
