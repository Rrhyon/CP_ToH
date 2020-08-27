#pragma once
/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date Started:     20200810
  Date Modified:    20200823
*/

#ifndef CTUTILITIES_H
#define CTUTILITIES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> parseCSV(const string&);

string writeCSV(const vector<string>&);

bool fileExists(const string&);

string input(const string&, const char = '\n');

string capsMe(const string&);

bool isValidOption(const string&, const vector<string>&);

string padMe(const string&, const size_t, const char = 'r', const char = ' ');

string lPadMe(const string&, const size_t, const char = ' ');

string cPadMe(const string&, const size_t, const char = ' ');

string rPadMe(const string&, const size_t, const char = ' ');

#endif
