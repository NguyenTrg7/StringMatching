#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

void ReadFromFile(string fileName, vector<vector<char>>& grid, vector<string>& words);
void WriteToFile(string fileName, string algo, vector<string>& words, vector<vector<pair<int, int>>>& res, unsigned long long comp, double time);
void Run(string algo, string inputFile, string outputFile);