#pragma once
#include "Run.h"

vector<vector<pair<int, int>>> BruteForceCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);
vector<vector<pair<int, int>>> RabinKarpCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);
vector<vector<pair<int, int>>> KMPCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);
vector<vector<pair<int, int>>> BoyerMooreCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);
vector<vector<pair<int, int>>> AhoCorasickCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);

vector<vector<pair<int, int>>> AlgoNavigatorCmp(string algo, const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp);

vector<vector<pair<int, int>>> BruteForce(const vector<vector<char>>& grid, const vector<string>& words);
vector<vector<pair<int, int>>> RabinKarp(const vector<vector<char>>& grid, const vector<string>& words);
vector<vector<pair<int, int>>> KMP(const vector<vector<char>>& grid, const vector<string>& words);
vector<vector<pair<int, int>>> BoyerMoore(const vector<vector<char>>& grid, const vector<string>& words);
vector<vector<pair<int, int>>> AhoCorasick(const vector<vector<char>>& grid, const vector<string>& words);

vector<vector<pair<int, int>>> AlgoNavigator(string algo, const vector<vector<char>>& grid, const vector<string>& words);