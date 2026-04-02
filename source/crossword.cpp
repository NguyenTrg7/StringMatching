#include "Run.h"

// g++ *.cpp -o crossword.exe -std=c++17
// crossword.exe -a [algo] -i [inputFile] -o [outputFile]
int main(int argc, char* argv[]) {
	string arg1 = argv[1], arg3 = argv[3], arg5 = argv[5];
    if (argc != 7 || arg1 != "-a" || arg3 != "-i" || arg5 != "-o") {
        cerr << "Invalid command!";
        return 1;
    }

    string algo = argv[2], inputFile = argv[4], outputFile = argv[6];
	if (algo != "bf" && algo != "rk" && algo != "kmp" && algo != "bm" && algo != "ac") {
        cerr << "Invalid algorithm!";
        return 1;
    }

    Run(algo, inputFile, outputFile);
    return 0;
}