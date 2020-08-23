#pragma once
#ifndef CTUTILITIES_H_
#define CTUTILITIES_H_
/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200810
*/

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

bool isValidOption(string, vector<string>);

#endif