#include <iostream>
#include <vector>
#include <string>
using namespace std;

// PART A: KMP — Longest Prefix Suffix (LPS) Array

vector<int> computeLPS(const string& pattern) {
    int M = pattern.size();
    vector<int> lps(M, 0);

    int len = 0; 
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void kmpSearch(const string& text, const string& pattern) {
    int N = text.size(), M = pattern.size();
    vector<int> lps = computeLPS(pattern);

    cout << "\nKMP Search: pattern \"" << pattern
         << "\" in text \"" << text << "\"\n";

    int i = 0, j = 0;
    while (i < N) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }
        if (j == M) {
            cout << "  Pattern found at index " << i - j << "\n";
            j = lps[j - 1]; 
        } else if (i < N && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

// PART B: Rabin-Karp Algorithm

/*
 * Uses rolling hash: instead of comparing characters one by one,
 * compare hash values. Only do full comparison when hashes match.
 *
 * Rolling hash formula:
 *   hash(s[i..i+M-1]) = (s[i]*d^(M-1) + s[i+1]*d^(M-2) + ... + s[i+M-1]) % q
 *
 * Slide window by 1:
 *   new_hash = (d*(old_hash - s[i]*h) + s[i+M]) % q
 *   where h = d^(M-1) % q
 */
void rabinKarp(const string& text, const string& pattern,
               int d = 256, int q = 101) {
    int N = text.size(), M = pattern.size();
    if (M > N) return;

    int h = 1;
    for (int i = 0; i < M - 1; i++)
        h = (h * d) % q;

    long long patHash = 0, winHash = 0;

    for (int i = 0; i < M; i++) {
        patHash = (d * patHash + pattern[i]) % q;
        winHash = (d * winHash + text[i]) % q;
    }

    int spurious = 0; 

    cout << "\nRabin-Karp Search: pattern \"" << pattern
         << "\" in text \"" << text << "\"\n";
    cout << "  (d=" << d << ", q=" << q << ")\n";

    for (int i = 0; i <= N - M; i++) {
        if (patHash == winHash) {
            if (text.substr(i, M) == pattern) {
                cout << "  Pattern found at index " << i << "\n";
            } else {
                spurious++;
                cout << "  Spurious hit at index " << i
                     << " (hash collision)\n";
            }
        }

        if (i < N - M) {
            winHash = (d * (winHash - text[i] * h) + text[i + M]) % q;
            if (winHash < 0) winHash += q; 
        }
    }

    cout << "  Total spurious hits (hash collisions): " << spurious << "\n";
}

int main() {
    cout << " Part A: KMP — LPS Array \n";

    string pattern = "ABABCABAB";
    vector<int> lps = computeLPS(pattern);

    cout << "Pattern : ";
    for (char c : pattern) cout << c << "  ";
    cout << "\nIndex   : ";
    for (int i = 0; i < (int)pattern.size(); i++) cout << i << "  ";
    cout << "\nLPS     : ";
    for (int x : lps) cout << x << "  ";
    cout << "\n";

    cout << "\n--- LPS Manual Trace for \"" << pattern << "\" ---\n";
    cout << "i=0: '" << pattern[0] << "' → lps[0]=0  (no proper prefix possible for single char)\n";
    cout << "i=1: '" << pattern[1] << "' != '" << pattern[0] << "' → lps[1]=0\n";
    cout << "i=2: '" << pattern[2] << "' == '" << pattern[0] << "' → len=1, lps[2]=1  (\"A\" is both prefix and suffix)\n";
    cout << "i=3: '" << pattern[3] << "' == '" << pattern[1] << "' → len=2, lps[3]=2  (\"AB\" is both prefix and suffix)\n";
    cout << "i=4: '" << pattern[4] << "' != '" << pattern[2] << "' → fallback: len=lps[1]=0, 'C'!='A' → lps[4]=0\n";
    cout << "i=5: '" << pattern[5] << "' == '" << pattern[0] << "' → len=1, lps[5]=1\n";
    cout << "i=6: '" << pattern[6] << "' == '" << pattern[1] << "' → len=2, lps[6]=2\n";
    cout << "i=7: '" << pattern[7] << "' == '" << pattern[2] << "' → len=3, lps[7]=3\n";
    cout << "i=8: '" << pattern[8] << "' == '" << pattern[3] << "' → len=4, lps[8]=4  (\"ABAB\" is both prefix and suffix)\n";
    cout << "\nKey insight: lps[8]=4 means if mismatch occurs after matching\n";
    cout << "8 chars, we don't restart from 0 — we restart from index 4.\n";
    cout << "This avoids redundant comparisons, giving KMP its O(N+M) guarantee.\n";

    // Demo KMP search
    kmpSearch("ABABDABABCABABCABAB", pattern);

    cout << "\n====== Part B: Rabin-Karp ======\n";
    rabinKarp("ABCCDABABABCABAB", "ABAB");

    cout << "\n====== Rabin-Karp Theory ======\n";
    cout << R"(
HASH COLLISION HANDLING:
  A hash collision (spurious hit) occurs when:
    hash(text_window) == hash(pattern) BUT text_window ≠ pattern
  Rabin-Karp handles this by always doing a full character-by-character
  verification whenever the hashes match. This ensures correctness at
  the cost of extra work when collisions occur.
  Using a large prime q and a good base d reduces collision probability.

TIME COMPLEXITY:
  Preprocessing : O(M)  — compute pattern hash and initial window hash
  Average case  : O(N + M) — hash comparisons O(1) per window slide,
                             few spurious hits → rare full comparisons
  Worst case    : O(N × M) — occurs when ALL windows produce hash
                             collisions (e.g., all same characters,
                             bad choice of q), forcing full comparison
                             at every position
  Space         : O(1) — only stores hash values, not substrings

COMPARISON WITH KMP:
  KMP guarantees O(N+M) always (no worst-case degradation)
  Rabin-Karp is O(N+M) on average but O(NM) worst case
  Rabin-Karp excels at MULTIPLE PATTERN matching — hash all patterns
  first, then a single pass detects any of them simultaneously
)";

    return 0;
}