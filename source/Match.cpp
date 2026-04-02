#include "Match.h"

const int BASE = 256;
const int MOD = 1e9 + 7;

struct TrieNode {
    int children[256];
    int fail;
    vector<int> out;

    TrieNode() {
        fill(begin(children), end(children), -1);
        fail = 0;
    }
};

vector<vector<pair<int, int>>> BruteForceCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c <= cols - len; ++c) {
                    int k = 0;
                    while (k < len) {
                        if (++comp && grid[r][c + k] != words[i][k]) break;
                        ++k;
                    }
                    if (k == len) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r, c + len - 1 });
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                for (int r = 0; r <= rows - len; ++r) {
                    int k = 0;
                    while (k < len) {
                        if (++comp && grid[r + k][c] != words[i][k]) break;
                        ++k;
                    }
                    if (k == len) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r + len - 1, c });
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> RabinKarpCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        long long hashkey = 0;
        long long Basepow = 1;
        for (int k = 0; k < len; ++k) {
            hashkey = (hashkey * BASE + (unsigned char)words[i][k]) % MOD;
            if (k > 0) Basepow = (Basepow * BASE) % MOD;
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                long long patternHash = 0;
                for (int c = 0; c < len; ++c) {
                    patternHash = (patternHash * BASE + (unsigned char)grid[r][c]) % MOD;
                }

                for (int c = 0; c <= cols - len; ++c) {
                    if (c > 0) {
                        patternHash = (patternHash - (unsigned long long)grid[r][c - 1] * Basepow % MOD + MOD) % MOD;
                        patternHash = (patternHash * BASE + (unsigned char)grid[r][c + len - 1]) % MOD;
                    }

                    if (patternHash == hashkey) {
                        int k = 0;
                        while (k < len) {
                            if (++comp && grid[r][c + k] != words[i][k]) break;
                            ++k;
                        }
                        if (k == len) {
                            res[i].push_back({ r, c });
                            res[i].push_back({ r, c + len - 1 });
                        }
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                long long patternHash = 0;
                for (int r = 0; r < len; ++r) {
                    patternHash = (patternHash * BASE + (unsigned char)grid[r][c]) % MOD;
                }

                for (int r = 0; r <= rows - len; ++r) {
                    if (r > 0) {
                        patternHash = (patternHash - (unsigned long long)grid[r - 1][c] * Basepow % MOD + MOD) % MOD;
                        patternHash = (patternHash * BASE + (unsigned char)grid[r + len - 1][c]) % MOD;
                    }

                    if (patternHash == hashkey) {
                        int k = 0;
                        while (k < len) {
                            if (++comp && grid[r + k][c] != words[i][k]) break;
                            ++k;
                        }
                        if (k == len) {
                            res[i].push_back({ r, c });
                            res[i].push_back({ r + len - 1, c });
                        }
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> KMPCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        vector<int> lps(len, 0);
        int len_lps = 0;
        int k = 1;
        while (k < len) {
            if (words[i][k] == words[i][len_lps]) {
                ++len_lps;
                lps[k] = len_lps;
                ++k;
            }
            else {
                if (len_lps != 0) {
                    len_lps = lps[len_lps - 1];
                }
                else {
                    lps[k] = 0;
                    ++k;
                }
            }
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                int c = 0;
                int j = 0;

                while (c < cols) {
                    if (cols - c < len - j) break;

                    if (++comp && grid[r][c] == words[i][j]) {
                        ++c;
                        ++j;

                        if (j == len) {
                            res[i].push_back({ r, c - len });
                            res[i].push_back({ r, c - 1 });
                            j = lps[j - 1];
                        }
                    }
                    else {
                        if (j != 0) {
                            j = lps[j - 1];
                        }
                        else {
                            ++c;
                        }
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                int r = 0;
                int j = 0;

                while (r < rows) {
                    if (rows - r < len - j) break;

                    if (++comp && grid[r][c] == words[i][j]) {
                        ++r;
                        ++j;

                        if (j == len) {
                            res[i].push_back({ r - len, c });
                            res[i].push_back({ r - 1, c });
                            j = lps[j - 1];
                        }
                    }
                    else {
                        if (j != 0) {
                            j = lps[j - 1];
                        }
                        else {
                            ++r;
                        }
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> BoyerMooreCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        vector<int> badChar(256, -1);
        for (int k = 0; k < len; ++k) {
            badChar[(unsigned char)words[i][k]] = k;
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                int c = 0;
                while (c <= cols - len) {
                    int k = len - 1;
                    while (k >= 0) {
                        if (++comp && grid[r][c + k] != words[i][k]) break;
                        --k;
                    }

                    if (k < 0) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r, c + len - 1 });
                        c += (c + len < cols) ? len - badChar[(unsigned char)grid[r][c + len]] : 1;
                    }
                    else {
                        c += max(1, k - badChar[(unsigned char)grid[r][c + k]]);
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                int r = 0;
                while (r <= rows - len) {
                    int k = len - 1;
                    while (k >= 0) {
                        if (++comp && grid[r + k][c] != words[i][k]) break;
                        --k;
                    }

                    if (k < 0) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r + len - 1, c });
                        r += (r + len < rows) ? len - badChar[(unsigned char)grid[r + len][c]] : 1;
                    }
                    else {
                        r += max(1, k - badChar[(unsigned char)grid[r + k][c]]);
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> AhoCorasickCmp(const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());
    vector<TrieNode> trie(1);

    for (int i = 0; i < words.size(); ++i) {
        if (words[i].empty() || words[i].length() > max(rows, cols)) continue;

        int curr = 0;
        for (char c : words[i]) {
            unsigned char uc = c;
            if (trie[curr].children[uc] == -1) {
                trie[curr].children[uc] = trie.size();
                trie.emplace_back();
            }
            curr = trie[curr].children[uc];
        }
        trie[curr].out.push_back(i);
    }

    queue<int> q;
    for (int k = 0; k < 256; ++k) {
        if (trie[0].children[k] != -1) {
            trie[trie[0].children[k]].fail = 0;
            q.push(trie[0].children[k]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int f = trie[u].fail;
        trie[u].out.insert(trie[u].out.end(), trie[f].out.begin(), trie[f].out.end());

        for (int k = 0; k < 256; ++k) {
            int v = trie[u].children[k];
            if (v != -1) {
                int fail_state = trie[u].fail;
                while (fail_state != 0 && trie[fail_state].children[k] == -1) {
                    fail_state = trie[fail_state].fail;
                }
                if (trie[fail_state].children[k] != -1) {
                    fail_state = trie[fail_state].children[k];
                }
                trie[v].fail = fail_state;
                q.push(v);
            }
        }
    }

    for (int r = 0; r < rows; ++r) {
        int curr = 0;
        for (int c = 0; c < cols; ++c) {
            unsigned char uc = grid[r][c];

            while (++comp && curr != 0 && trie[curr].children[uc] == -1) {
                curr = trie[curr].fail;
                ++comp;                
            }

            if (trie[curr].children[uc] != -1) {
                curr = trie[curr].children[uc];
            }

            for (int idx : trie[curr].out) {
                int len = words[idx].length();
                res[idx].push_back({ r, c - len + 1 });
                res[idx].push_back({ r, c });
            }
        }
    }

    for (int c = 0; c < cols; ++c) {
        int curr = 0;
        for (int r = 0; r < rows; ++r) {
            unsigned char uc = grid[r][c];

            while (++comp && curr != 0 && trie[curr].children[uc] == -1) {
                curr = trie[curr].fail;
                ++comp;
            }

            if (trie[curr].children[uc] != -1) {
                curr = trie[curr].children[uc];
            }

            for (int idx : trie[curr].out) {
                int len = words[idx].length();
                if (len == 1) continue;

                res[idx].push_back({ r - len + 1, c });
                res[idx].push_back({ r, c });
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> AlgoNavigatorCmp(string algo, const vector<vector<char>>& grid, const vector<string>& words, unsigned long long& comp) {
	if (algo == "bf")
		return BruteForceCmp(grid, words, comp);
	else if (algo == "rk")
		return RabinKarpCmp(grid, words, comp);
	else if (algo == "kmp")
		return KMPCmp(grid, words, comp);
	else if (algo == "bm")
		return BoyerMooreCmp(grid, words, comp);
	else return AhoCorasickCmp(grid, words, comp);
}

vector<vector<pair<int, int>>> BruteForce(const vector<vector<char>>& grid, const vector<string>& words) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c <= cols - len; ++c) {
                    int k = 0;
                    while (k < len) {
                        if (grid[r][c + k] != words[i][k]) break;
                        ++k;
                    }
                    if (k == len) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r, c + len - 1 });
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                for (int r = 0; r <= rows - len; ++r) {
                    int k = 0;
                    while (k < len) {
                        if (grid[r + k][c] != words[i][k]) break;
                        ++k;
                    }
                    if (k == len) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r + len - 1, c });
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> RabinKarp(const vector<vector<char>>& grid, const vector<string>& words) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        long long hashkey = 0;
        long long Basepow = 1;
        for (int k = 0; k < len; ++k) {
            hashkey = (hashkey * BASE + (unsigned char)words[i][k]) % MOD;
            if (k > 0) Basepow = (Basepow * BASE) % MOD;
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                long long patternHash = 0;
                for (int c = 0; c < len; ++c) {
                    patternHash = (patternHash * BASE + (unsigned char)grid[r][c]) % MOD;
                }

                for (int c = 0; c <= cols - len; ++c) {
                    if (c > 0) {
                        patternHash = (patternHash - (unsigned long long)grid[r][c - 1] * Basepow % MOD + MOD) % MOD;
                        patternHash = (patternHash * BASE + (unsigned char)grid[r][c + len - 1]) % MOD;
                    }

                    if (patternHash == hashkey) {
                        int k = 0;
                        while (k < len) {
                            if (grid[r][c + k] != words[i][k]) break;
                            ++k;
                        }
                        if (k == len) {
                            res[i].push_back({ r, c });
                            res[i].push_back({ r, c + len - 1 });
                        }
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                long long patternHash = 0;
                for (int r = 0; r < len; ++r) {
                    patternHash = (patternHash * BASE + (unsigned char)grid[r][c]) % MOD;
                }

                for (int r = 0; r <= rows - len; ++r) {
                    if (r > 0) {
                        patternHash = (patternHash - (unsigned long long)grid[r - 1][c] * Basepow % MOD + MOD) % MOD;
                        patternHash = (patternHash * BASE + (unsigned char)grid[r + len - 1][c]) % MOD;
                    }

                    if (patternHash == hashkey) {
                        int k = 0;
                        while (k < len) {
                            if (grid[r + k][c] != words[i][k]) break;
                            ++k;
                        }
                        if (k == len) {
                            res[i].push_back({ r, c });
                            res[i].push_back({ r + len - 1, c });
                        }
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> KMP(const vector<vector<char>>& grid, const vector<string>& words) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        vector<int> lps(len, 0);
        int len_lps = 0;
        int k = 1;
        while (k < len) {
            if (words[i][k] == words[i][len_lps]) {
                ++len_lps;
                lps[k] = len_lps;
                ++k;
            }
            else {
                if (len_lps != 0) {
                    len_lps = lps[len_lps - 1];
                }
                else {
                    lps[k] = 0;
                    ++k;
                }
            }
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                int c = 0;
                int j = 0;

                while (c < cols) {
                    if (cols - c < len - j) break;

                    if (grid[r][c] == words[i][j]) {
                        ++c;
                        ++j;

                        if (j == len) {
                            res[i].push_back({ r, c - len });
                            res[i].push_back({ r, c - 1 });
                            j = lps[j - 1];
                        }
                    }
                    else {
                        if (j != 0) {
                            j = lps[j - 1];
                        }
                        else {
                            ++c;
                        }
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                int r = 0;
                int j = 0;

                while (r < rows) {
                    if (rows - r < len - j) break;

                    if (grid[r][c] == words[i][j]) {
                        ++r;
                        ++j;

                        if (j == len) {
                            res[i].push_back({ r - len, c });
                            res[i].push_back({ r - 1, c });
                            j = lps[j - 1];
                        }
                    }
                    else {
                        if (j != 0) {
                            j = lps[j - 1];
                        }
                        else {
                            ++r;
                        }
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> BoyerMoore(const vector<vector<char>>& grid, const vector<string>& words) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());

    for (int i = 0; i < words.size(); ++i) {
        int len = words[i].length();
        if (len == 0 || len > max(rows, cols)) continue;

        vector<int> badChar(256, -1);
        for (int k = 0; k < len; ++k) {
            badChar[(unsigned char)words[i][k]] = k;
        }

        if (len <= cols) {
            for (int r = 0; r < rows; ++r) {
                int c = 0;
                while (c <= cols - len) {
                    int k = len - 1;
                    while (k >= 0) {
                        if (grid[r][c + k] != words[i][k]) break;
                        --k;
                    }

                    if (k < 0) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r, c + len - 1 });
                        c += (c + len < cols) ? len - badChar[(unsigned char)grid[r][c + len]] : 1;
                    }
                    else {
                        c += max(1, k - badChar[(unsigned char)grid[r][c + k]]);
                    }
                }
            }
        }

        if (len > 1 && len <= rows) {
            for (int c = 0; c < cols; ++c) {
                int r = 0;
                while (r <= rows - len) {
                    int k = len - 1;
                    while (k >= 0) {
                        if (grid[r + k][c] != words[i][k]) break;
                        --k;
                    }

                    if (k < 0) {
                        res[i].push_back({ r, c });
                        res[i].push_back({ r + len - 1, c });
                        r += (r + len < rows) ? len - badChar[(unsigned char)grid[r + len][c]] : 1;
                    }
                    else {
                        r += max(1, k - badChar[(unsigned char)grid[r + k][c]]);
                    }
                }
            }
        }
    }

    return res;
}

vector<vector<pair<int, int>>> AhoCorasick(const vector<vector<char>>& grid, const vector<string>& words) {
    int rows = grid.size();
    if (rows == 0) return {};
    int cols = grid[0].size();

    vector<vector<pair<int, int>>> res(words.size());
    vector<TrieNode> trie(1);

    for (int i = 0; i < words.size(); ++i) {
        if (words[i].empty() || words[i].length() > max(rows, cols)) continue;

        int curr = 0;
        for (char c : words[i]) {
            unsigned char uc = c;
            if (trie[curr].children[uc] == -1) {
                trie[curr].children[uc] = trie.size();
                trie.emplace_back();
            }
            curr = trie[curr].children[uc];
        }
        trie[curr].out.push_back(i);
    }

    queue<int> q;
    for (int k = 0; k < 256; ++k) {
        if (trie[0].children[k] != -1) {
            trie[trie[0].children[k]].fail = 0;
            q.push(trie[0].children[k]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int f = trie[u].fail;
        trie[u].out.insert(trie[u].out.end(), trie[f].out.begin(), trie[f].out.end());

        for (int k = 0; k < 256; ++k) {
            int v = trie[u].children[k];
            if (v != -1) {
                int fail_state = trie[u].fail;
                while (fail_state != 0 && trie[fail_state].children[k] == -1) {
                    fail_state = trie[fail_state].fail;
                }
                if (trie[fail_state].children[k] != -1) {
                    fail_state = trie[fail_state].children[k];
                }
                trie[v].fail = fail_state;
                q.push(v);
            }
        }
    }

    for (int r = 0; r < rows; ++r) {
        int curr = 0;
        for (int c = 0; c < cols; ++c) {
            unsigned char uc = grid[r][c];

            while (curr != 0 && trie[curr].children[uc] == -1) {
                curr = trie[curr].fail;
            }

            if (trie[curr].children[uc] != -1) {
                curr = trie[curr].children[uc];
            }

            for (int idx : trie[curr].out) {
                int len = words[idx].length();
                res[idx].push_back({ r, c - len + 1 });
                res[idx].push_back({ r, c });
            }
        }
    }

    for (int c = 0; c < cols; ++c) {
        int curr = 0;
        for (int r = 0; r < rows; ++r) {
            unsigned char uc = grid[r][c];

            while (curr != 0 && trie[curr].children[uc] == -1) {
                curr = trie[curr].fail;
            }

            if (trie[curr].children[uc] != -1) {
                curr = trie[curr].children[uc];
            }

            for (int idx : trie[curr].out) {
                int len = words[idx].length();
                if (len == 1) continue;

                res[idx].push_back({ r - len + 1, c });
                res[idx].push_back({ r, c });
            }
        }
    }

    return res;
}


vector<vector<pair<int, int>>> AlgoNavigator(string algo, const vector<vector<char>>& grid, const vector<string>& words) {
    if (algo == "bf")
        return BruteForce(grid, words);
    else if (algo == "rk")
        return RabinKarp(grid, words);
    else if (algo == "kmp")
        return KMP(grid, words);
    else if (algo == "bm")
        return BoyerMoore(grid, words);
    else return AhoCorasick(grid, words);
}
