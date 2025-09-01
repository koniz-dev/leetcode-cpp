# String Algorithms

## Overview

String algorithms solve problems involving text processing, pattern matching, and string manipulation. These algorithms are fundamental to text processing, bioinformatics, data mining, and many other applications.

## Pattern Matching

### Naive String Matching

```cpp
#include <string>
#include <vector>
#include <iostream>

class StringMatcher {
public:
    // Naive pattern matching - O((n-m+1)*m)
    std::vector<int> naiveSearch(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        for (int i = 0; i <= n - m; ++i) {
            int j;
            for (j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                positions.push_back(i);
            }
        }
        
        return positions;
    }
    
    // Improved naive with early exit
    std::vector<int> improvedNaiveSearch(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        for (int i = 0; i <= n - m; ++i) {
            bool match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                positions.push_back(i);
            }
        }
        
        return positions;
    }
};
```

### Knuth-Morris-Pratt (KMP) Algorithm

```cpp
#include <string>
#include <vector>
#include <iostream>

class KMPMatcher {
private:
    std::vector<int> computeLPS(const std::string& pattern) {
        int m = pattern.length();
        std::vector<int> lps(m, 0);
        
        int len = 0;
        int i = 1;
        
        while (i < m) {
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
    
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        if (m > n) return positions;
        
        std::vector<int> lps = computeLPS(pattern);
        
        int i = 0; // index for text
        int j = 0; // index for pattern
        
        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;
            }
            
            if (j == m) {
                positions.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != text[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        
        return positions;
    }
};
```

### Boyer-Moore Algorithm

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class BoyerMooreMatcher {
private:
    std::unordered_map<char, int> badCharTable;
    
    void preprocessBadCharTable(const std::string& pattern) {
        int m = pattern.length();
        badCharTable.clear();
        
        for (int i = 0; i < m - 1; ++i) {
            badCharTable[pattern[i]] = m - 1 - i;
        }
    }
    
    std::vector<int> computeGoodSuffixTable(const std::string& pattern) {
        int m = pattern.length();
        std::vector<int> goodSuffix(m, m);
        std::vector<int> border(m, 0);
        
        // Case 1: Exact match
        int i = m, j = m + 1;
        border[i - 1] = j;
        
        while (i > 1) {
            while (j <= m && pattern[i - 1] != pattern[j - 1]) {
                if (goodSuffix[j - 1] == m) {
                    goodSuffix[j - 1] = j - i;
                }
                j = border[j - 1];
            }
            i--;
            j--;
            border[i - 1] = j;
        }
        
        // Case 2: Good suffix exists
        j = border[0];
        for (i = 1; i <= m; ++i) {
            if (goodSuffix[i - 1] == m) {
                goodSuffix[i - 1] = j;
            }
            if (i == j) {
                j = border[j - 1];
            }
        }
        
        return goodSuffix;
    }
    
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        if (m > n) return positions;
        
        preprocessBadCharTable(pattern);
        std::vector<int> goodSuffix = computeGoodSuffixTable(pattern);
        
        int i = m - 1;
        while (i < n) {
            int j = m - 1;
            int k = i;
            
            while (j >= 0 && text[k] == pattern[j]) {
                k--;
                j--;
            }
            
            if (j == -1) {
                positions.push_back(k + 1);
                i += goodSuffix[0];
            } else {
                int badCharShift = badCharTable.find(text[k]) != badCharTable.end() 
                    ? badCharTable[text[k]] : m;
                int goodSuffixShift = goodSuffix[j];
                i += std::max(badCharShift, goodSuffixShift);
            }
        }
        
        return positions;
    }
};
```

### Rabin-Karp Algorithm

```cpp
#include <string>
#include <vector>
#include <iostream>

class RabinKarpMatcher {
private:
    static const int PRIME = 101;
    static const int BASE = 256;
    
    int hash(const std::string& str, int length) {
        int hash = 0;
        for (int i = 0; i < length; ++i) {
            hash = (hash * BASE + str[i]) % PRIME;
        }
        return hash;
    }
    
    bool checkEqual(const std::string& text, const std::string& pattern, int start) {
        for (int i = 0; i < pattern.length(); ++i) {
            if (text[start + i] != pattern[i]) {
                return false;
            }
        }
        return true;
    }
    
public:
    std::vector<int> search(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        if (m > n) return positions;
        
        int patternHash = hash(pattern, m);
        int textHash = hash(text, m);
        
        // Calculate hash for first window
        int power = 1;
        for (int i = 0; i < m - 1; ++i) {
            power = (power * BASE) % PRIME;
        }
        
        // Slide the pattern over text one by one
        for (int i = 0; i <= n - m; ++i) {
            if (patternHash == textHash) {
                if (checkEqual(text, pattern, i)) {
                    positions.push_back(i);
                }
            }
            
            if (i < n - m) {
                textHash = (BASE * (textHash - text[i] * power) + text[i + m]) % PRIME;
                if (textHash < 0) {
                    textHash += PRIME;
                }
            }
        }
        
        return positions;
    }
};
```

## String Processing

### Longest Common Subsequence (LCS)

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class LCSFinder {
public:
    // Dynamic programming approach - O(m*n)
    std::string findLCS(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        
        // Fill DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Reconstruct LCS
        std::string lcs;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (str1[i - 1] == str2[j - 1]) {
                lcs = str1[i - 1] + lcs;
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        
        return lcs;
    }
    
    // Space-optimized version - O(n) space
    int findLCSLength(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        std::vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= m; ++i) {
            int prev = 0;
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];
                if (str1[i - 1] == str2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = std::max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
};
```

### Longest Common Substring

```cpp
#include <string>
#include <vector>
#include <iostream>

class LCSubstringFinder {
public:
    // Dynamic programming approach - O(m*n)
    std::string findLCSubstring(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        int maxLength = 0;
        int endPos = 0;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endPos = i - 1;
                    }
                }
            }
        }
        
        if (maxLength == 0) return "";
        
        int startPos = endPos - maxLength + 1;
        return str1.substr(startPos, maxLength);
    }
    
    // Suffix tree approach (simplified)
    std::string findLCSubstringSuffixTree(const std::string& str1, const std::string& str2) {
        std::string combined = str1 + "#" + str2 + "$";
        // Build suffix tree and find deepest common ancestor
        // This is a simplified version - full implementation would require suffix tree
        return findLCSubstring(str1, str2); // Fallback to DP
    }
};
```

### Edit Distance (Levenshtein Distance)

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class EditDistanceCalculator {
public:
    // Dynamic programming approach - O(m*n)
    int calculateEditDistance(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        
        // Initialize first row and column
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }
        
        // Fill DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + std::min({dp[i - 1][j],      // deletion
                                            dp[i][j - 1],      // insertion
                                            dp[i - 1][j - 1]}); // substitution
                }
            }
        }
        
        return dp[m][n];
    }
    
    // Space-optimized version - O(n) space
    int calculateEditDistanceOptimized(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        std::vector<int> dp(n + 1);
        
        // Initialize first row
        for (int j = 0; j <= n; ++j) {
            dp[j] = j;
        }
        
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0];
            dp[0] = i;
            
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];
                if (str1[i - 1] == str2[j - 1]) {
                    dp[j] = prev;
                } else {
                    dp[j] = 1 + std::min({dp[j - 1], dp[j], prev});
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
};
```

## Suffix Arrays and Trees

### Suffix Array Construction

```cpp
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class SuffixArray {
private:
    std::vector<int> suffixArray;
    std::vector<int> lcpArray;
    
    struct Suffix {
        int index;
        int rank[2];
        
        bool operator<(const Suffix& other) const {
            return (rank[0] == other.rank[0]) ? 
                   (rank[1] < other.rank[1]) : (rank[0] < other.rank[0]);
        }
    };
    
public:
    void buildSuffixArray(const std::string& text) {
        int n = text.length();
        std::vector<Suffix> suffixes(n);
        
        // Initialize suffixes with first character
        for (int i = 0; i < n; ++i) {
            suffixes[i].index = i;
            suffixes[i].rank[0] = text[i];
            suffixes[i].rank[1] = (i + 1 < n) ? text[i + 1] : -1;
        }
        
        // Sort by first two characters
        std::sort(suffixes.begin(), suffixes.end());
        
        // Sort by first 4, 8, 16, ... characters
        for (int k = 4; k < 2 * n; k *= 2) {
            int rank = 0;
            int prevRank = suffixes[0].rank[0];
            suffixes[0].rank[0] = rank;
            
            // Assign new ranks
            for (int i = 1; i < n; ++i) {
                if (suffixes[i].rank[0] == prevRank && 
                    suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                    prevRank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = rank;
                } else {
                    prevRank = suffixes[i].rank[0];
                    suffixes[i].rank[0] = ++rank;
                }
            }
            
            // Assign ranks for next iteration
            for (int i = 0; i < n; ++i) {
                int nextIndex = suffixes[i].index + k / 2;
                suffixes[i].rank[1] = (nextIndex < n) ? 
                    suffixes[nextIndex].rank[0] : -1;
            }
            
            std::sort(suffixes.begin(), suffixes.end());
        }
        
        // Extract suffix array
        suffixArray.resize(n);
        for (int i = 0; i < n; ++i) {
            suffixArray[i] = suffixes[i].index;
        }
        
        buildLCPArray(text);
    }
    
    void buildLCPArray(const std::string& text) {
        int n = text.length();
        lcpArray.resize(n - 1);
        
        std::vector<int> rank(n);
        for (int i = 0; i < n; ++i) {
            rank[suffixArray[i]] = i;
        }
        
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            
            int j = suffixArray[rank[i] + 1];
            while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
                k++;
            }
            
            lcpArray[rank[i]] = k;
            if (k > 0) k--;
        }
    }
    
    std::vector<int> searchPattern(const std::string& text, const std::string& pattern) {
        std::vector<int> positions;
        int n = text.length();
        int m = pattern.length();
        
        // Binary search for pattern
        int left = 0, right = n - 1;
        int start = -1, end = -1;
        
        // Find start position
        while (left <= right) {
            int mid = (left + right) / 2;
            int cmp = text.compare(suffixArray[mid], m, pattern);
            if (cmp >= 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        start = left;
        
        // Find end position
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int cmp = text.compare(suffixArray[mid], m, pattern);
            if (cmp > 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        end = right;
        
        // Collect positions
        for (int i = start; i <= end; ++i) {
            positions.push_back(suffixArray[i]);
        }
        
        return positions;
    }
    
    void printSuffixArray(const std::string& text) {
        std::cout << "Suffix Array:" << std::endl;
        for (int i = 0; i < suffixArray.size(); ++i) {
            std::cout << suffixArray[i] << ": " 
                      << text.substr(suffixArray[i]) << std::endl;
        }
        
        if (!lcpArray.empty()) {
            std::cout << "\nLCP Array:" << std::endl;
            for (int i = 0; i < lcpArray.size(); ++i) {
                std::cout << lcpArray[i] << " ";
            }
            std::cout << std::endl;
        }
    }
};
```

## String Compression

### Run-Length Encoding

```cpp
#include <string>
#include <iostream>

class RunLengthEncoder {
public:
    std::string encode(const std::string& input) {
        if (input.empty()) return "";
        
        std::string encoded;
        char current = input[0];
        int count = 1;
        
        for (size_t i = 1; i < input.length(); ++i) {
            if (input[i] == current) {
                count++;
            } else {
                encoded += std::to_string(count) + current;
                current = input[i];
                count = 1;
            }
        }
        
        encoded += std::to_string(count) + current;
        return encoded;
    }
    
    std::string decode(const std::string& encoded) {
        std::string decoded;
        
        for (size_t i = 0; i < encoded.length(); ++i) {
            if (std::isdigit(encoded[i])) {
                int count = 0;
                while (i < encoded.length() && std::isdigit(encoded[i])) {
                    count = count * 10 + (encoded[i] - '0');
                    i++;
                }
                
                if (i < encoded.length()) {
                    char c = encoded[i];
                    decoded.append(count, c);
                }
            }
        }
        
        return decoded;
    }
};
```

### Huffman Coding

```cpp
#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char d, int freq) : data(d), frequency(freq), 
                                   left(nullptr), right(nullptr) {}
    
    bool operator>(const HuffmanNode& other) const {
        return frequency > other.frequency;
    }
};

class HuffmanEncoder {
private:
    HuffmanNode* root;
    std::unordered_map<char, std::string> codes;
    
    void generateCodes(HuffmanNode* node, std::string code) {
        if (node == nullptr) return;
        
        if (node->left == nullptr && node->right == nullptr) {
            codes[node->data] = code;
            return;
        }
        
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }
    
    void deleteTree(HuffmanNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    
public:
    HuffmanEncoder() : root(nullptr) {}
    
    ~HuffmanEncoder() {
        deleteTree(root);
    }
    
    void buildHuffmanTree(const std::string& text) {
        // Count frequencies
        std::unordered_map<char, int> freq;
        for (char c : text) {
            freq[c]++;
        }
        
        // Create priority queue
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, 
                           std::greater<HuffmanNode*>> pq;
        
        for (const auto& pair : freq) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }
        
        // Build tree
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            
            HuffmanNode* internal = new HuffmanNode('\0', left->frequency + right->frequency);
            internal->left = left;
            internal->right = right;
            
            pq.push(internal);
        }
        
        root = pq.top();
        generateCodes(root, "");
    }
    
    std::string encode(const std::string& text) {
        std::string encoded;
        for (char c : text) {
            encoded += codes[c];
        }
        return encoded;
    }
    
    void printCodes() {
        std::cout << "Huffman Codes:" << std::endl;
        for (const auto& pair : codes) {
            std::cout << "'" << pair.first << "': " << pair.second << std::endl;
        }
    }
};
```

## Summary

String algorithms provide solutions for:
- **Pattern matching**: KMP, Boyer-Moore, Rabin-Karp
- **String comparison**: LCS, edit distance, common substrings
- **Suffix processing**: Suffix arrays, suffix trees
- **Compression**: Run-length encoding, Huffman coding

Key applications:
- **Text processing**: Search engines, text editors
- **Bioinformatics**: DNA sequence analysis
- **Data mining**: Pattern recognition
- **Compression**: File compression, data storage
- **Natural language processing**: Text analysis

These algorithms form the foundation for efficient string processing and are essential for many real-world applications involving text data.
