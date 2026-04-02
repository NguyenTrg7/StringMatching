#include "Run.h"
#include "Match.h"

void ReadFromFile(string fileName, vector<vector<char>>& grid, vector<string>& words) {
    ifstream fin(fileName);
    if (!fin.is_open()) {
        return cerr << "Error opening file!", void();
    }

	int n, m;
    fin >> n >> m;
	grid.resize(n, vector<char>(m));
	for (auto& x : grid) {
        for (auto &y: x) {
            fin >> y;
        }
    }

	int k;
    fin >> k;
	words.resize(k);
    for (auto &x: words) {
        fin >> x;
    }

	fin.close();
}

void WriteToFile(string fileName, string algo, vector<string>& words, vector<vector<pair<int,int>>>& res, unsigned long long comp, double time) {
    ofstream fout(fileName);
    if (!fout.is_open()) {
        return cerr << "Error opening file!", void();
    }

	for (int i = 0; i < words.size(); ++i) {
        if (res[i].empty()) {
            fout << words[i] << ": not found\n";
        }
        else {
            fout << words[i] << ": ";
            for (int j = 0; j < res[i].size(); j += 2) {
                fout << '(' << res[i][j].first << ", " << res[i][j].second << ") -> ";
				fout << '(' << res[i][j + 1].first << ", " << res[i][j + 1].second << "); ";
            }
			fout << '\n';
        }
    }

	fout << "----------------------------------\nAlgorithm: ";
    if (algo == "bf")
        fout << "Brute Force\n";
    else if (algo == "rk")
        fout << "Rabin-Karp\n";
    else if (algo == "kmp")
        fout << "KMP\n";
    else if (algo == "bm")
        fout << "Boyer-Moore\n";
    else fout << "Aho-Corasick\n";
	fout << "Comparisons: " << comp << '\n';
	fout << "Excution Time: " << fixed << setprecision(10) << time << " ms\n";
}

void Run(string algo, string inputFile, string outputFile) {
    vector<vector<char>> grid;
    vector<string> words;
    ReadFromFile(inputFile, grid, words);

	vector<vector<pair<int, int>>> res;
	unsigned long long comp = 0;
	double time;

    AlgoNavigatorCmp(algo, grid, words, comp);
    
    auto start = high_resolution_clock::now();
    res = AlgoNavigator(algo, grid, words);
    auto end = high_resolution_clock::now();
    time = duration_cast<duration<double>>(end - start).count();
    
    WriteToFile(outputFile, algo, words, res, comp, time);
}