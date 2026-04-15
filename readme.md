# 2D Matrix Word Search Engine

A high-performance command-line tool designed to scan, locate, and extract target words hidden within a 2D character grid.

## Overview

This project tackles the classic string-matching problem adapted for a 2D space. The engine is specifically designed to scan the matrix horizontally (left-to-right) and vertically (top-to-bottom) to find hidden patterns. 

Beyond simple pattern matching, this tool serves as an educational benchmarking suite. By precisely measuring execution time and tracking the total number of character comparisons, it provides empirical data for in-depth research and performance analysis of various string-matching techniques when scaled to matrix environments.

## Implemented Algorithms

To ensure optimal performance and provide a comprehensive comparison, the search engine evaluates 5 distinct algorithms:

* **Brute Force:** The standard, exhaustive search method.
* **Rabin-Karp:** Optimizes comparisons utilizing rolling hash functions.
* **Knuth-Morris-Pratt (KMP):** Employs a Longest Prefix Suffix (LPS) array to eliminate redundant character checks.
* **Boyer-Moore:** Achieves high-speed searching by skipping multiple characters using "Bad Character" and "Good Suffix" heuristics.
* **Aho-Corasick:** Constructs a finite state machine (Trie) with failure links, representing the ultimate solution for matching multiple patterns simultaneously in a single pass.

## Prerequisites

To compile and run this project, you will need:
* A C++ compiler that supports C++17 or higher (e.g., `g++`, `clang++`).
* A command-line interface (Terminal on macOS/Linux, or Git Bash/PowerShell/CMD on Windows).

## How to Build and Run

### 1. Compile the Source Code
Navigate to the directory containing the source files and compile the program using your preferred C++ compiler. 

If you are using `g++`, run the following command:
```bash
g++ *.cpp -o crossword[.exe] -std=c++17
```
### 2. Run the program
The program requires command-line arguments to execute

**Command Syntax:**
```bash
crossword[.exe] -a [algorithm] -i [input_file] -o [output_file]
```
Options:
* [algorithm]   : Select algorithm: bf, rk, kmp, bm, ac
* [input_file]  : Path to user-provided data file
* [output_file] : Path to the result output file

> **\*Note on Execution (`crossword[.exe]`):**
> The executable name varies depending on your operating system. When running the commands above:
> * **Windows users:** Include the `.exe` extension (e.g., `crossword.exe -a kmp ...`).
> * **Linux / macOS users:** Omit the `.exe` extension and ensure you prefix the command with `./` (e.g., `./crossword -a kmp ...`).