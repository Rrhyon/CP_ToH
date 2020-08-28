/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200810
  Date Modified:    20200827
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ctutilities.h"

using namespace std;

vector<string> parseCSV(const string& line) {
    /* Will read a CSV file line by line converting each line into a stringstream.
     * With a comma as the delimiter, the strings will be entered one at a time into
     * the string variable "item", and will be recorded into the vector results as
     * elements, and results will be returned.
     */
    vector<string> result;
    stringstream record(line);
    string item;
    while (getline(record, item, ',')) {
        result.push_back(item);
    }
    return result;
}

string writeCSV(const vector<string>& data) {
    /* Will read each string in a vector
     * converting each element into 
     */
    stringstream record;
    record << data[0];
    for (unsigned int i = 1; i < data.size(); i++) {
        record << ',' << data[i];
    }
    return record.str();
}

bool fileExists(const string& file) {
    fstream f(file.c_str());
    return f.good();
}

string input(const string& query, const char delim) {
    string result;
    cout << query;
    getline(cin, result, delim);
    return result;
}

string capsMe(const string& lcString) {
    string ucString;
    for (unsigned int i = 0; i < lcString.size(); i++) {
        ucString.push_back(toupper(lcString.at(i)));
    }
    return ucString;
}

bool isValidOption(const string& choice, const vector<string>& values) {
    // Will validate all input assuming it's a string.
    return !choice.empty() && find(values.begin(), values.end(), choice) != values.end();
}

string padMe(const string& txt, const size_t len, const char dir, const char pad) {
    switch (dir) {
        case 'l':
            return string(len - txt.length(), pad) + txt;
        case 'c':
            return string((len - txt.length()) / 2, pad) + txt +
                   string((len - txt.length()) / 2 + (len - txt.length()) % 2, pad);
        case 'r':
        default:
            return txt + string(len - txt.length(), pad);
    }
}

string lPadMe(const string& txt, const size_t len, const char pad) {
    return padMe(txt, len, 'l', pad);
}

string cPadMe(const string& txt, const size_t len, const char pad) {
    return padMe(txt, len, 'c', pad);
}

string rPadMe(const string& txt, const size_t len, const char pad) {
    return padMe(txt, len, 'r', pad);
}

string addMargin(const string& txt, const size_t len, const char dir, const char pad) {
    switch (dir) {
    case 'l':
        return string(len, pad) + txt;
    case 'c':
        return string(len / 2, pad) + txt +
               string(len / 2 + len % 2, pad);
    case 'r':
    default:
        return txt + string(len, pad);
    }
}

string lMargin(const string& txt, const size_t len, const char pad) {
    return addMargin(txt, len, 'l', pad);
}

string cMargin(const string& txt, const size_t len, const char pad) {
    return addMargin(txt, len, 'c', pad);
}

string rMargin(const string& txt, const size_t len, const char pad) {
    return addMargin(txt, len, 'r', pad);
}
