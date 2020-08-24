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

string writeCSV(const vector<string>);

bool fileExists(const string&);

string input(const string);

string capsMe(const string);

bool isValidOption(const string, const vector<string>);

#endif
