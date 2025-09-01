# Advanced String Matching

## Overview

Advanced string matching algorithms go beyond simple pattern matching to solve complex string processing problems. These algorithms are essential for text processing, bioinformatics, data compression, and many other applications.

## Suffix Array and Suffix Tree

### Suffix Array Construction

```cpp
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SuffixArray {
private:
    std::string text;
    std::vector<int> suffixArray;
    std::vector<int> lcpArray;
    
    // Compare suffixes for sorting
    struct SuffixComparator {
        const std::string& text;
        SuffixComparator(const std::string& t) : text(t) {}
        
        bool operator()(int a, int b) const {
            return text.substr(a) < text.substr(b);
        }
    };
    
public:
    SuffixArray(const std::string& t) : text(t) {
        buildSuffixArray();
        buildLCPArray();
    }
    
    // Build suffix array using sorting
    void buildSuffixArray() {
        int n = text.length();
        suffixArray.resize(n);
        
        for (int i = 0; i < n; ++i) {
            suffixArray[i] = i;
        }
        
        std::sort(suffixArray.begin(), suffixArray.end(), SuffixComparator(text));
    }
    
    // Build LCP array using Kasai's algorithm
    void buildLCPArray() {
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
    
    // Search for pattern using binary search
    std::vector<int> searchPattern(const std::string& pattern) const {
        std::vector<int> occurrences;
        int n = text.length();
        int m = pattern.length();
        
        // Binary search for first occurrence
        int left = 0, right = n - 1;
        int first = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int suffix = suffixArray[mid];
            int maxLen = std::min(n - suffix, m);
            
            int cmp = text.substr(suffix, maxLen).compare(pattern.substr(0, maxLen));
            if (cmp >= 0) {
                if (cmp == 0 && maxLen == m) {
                    first = mid;
                }
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        if (first == -1) return occurrences;
        
        // Binary search for last occurrence
        left = first, right = n - 1;
        int last = first;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int suffix = suffixArray[mid];
            int maxLen = std::min(n - suffix, m);
            
            int cmp = text.substr(suffix, maxLen).compare(pattern.substr(0, maxLen));
            if (cmp <= 0) {
                if (cmp == 0 && maxLen == m) {
                    last = mid;
                }
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        // Collect all occurrences
        for (int i = first; i <= last; ++i) {
            occurrences.push_back(suffixArray[i]);
        }
        
        return occurrences;
    }
    
    // Get longest common substring between two strings
    std::string getLongestCommonSubstring(const std::string& str1, const std::string& str2) {
        std::string combined = str1 + "#" + str2;
        SuffixArray sa(combined);
        
        int n = combined.length();
        int n1 = str1.length();
        int maxLen = 0;
        int startPos = 0;
        
        for (int i = 0; i < n - 1; ++i) {
            int pos1 = sa.suffixArray[i];
            int pos2 = sa.suffixArray[i + 1];
            
            // Check if suffixes belong to different strings
            bool fromStr1 = pos1 < n1;
            bool fromStr2 = pos2 < n1;
            
            if (fromStr1 != fromStr2) {
                int lcp = sa.lcpArray[i];
                if (lcp > maxLen) {
                    maxLen = lcp;
                    startPos = std::min(pos1, pos2);
                }
            }
        }
        
        return combined.substr(startPos, maxLen);
    }
    
    // Get all occurrences
    const std::vector<int>& getSuffixArray() const { return suffixArray; }
    const std::vector<int>& getLCPArray() const { return lcpArray; }
};
```

### Suffix Tree (Ukkonen's Algorithm)

```cpp
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct SuffixTreeNode {
    int start, end;
    std::map<char, SuffixTreeNode*> children;
    SuffixTreeNode* suffixLink;
    int suffixIndex;
    
    SuffixTreeNode(int start = -1, int end = -1) 
        : start(start), end(end), suffixLink(nullptr), suffixIndex(-1) {}
    
    int getLength() const {
        if (end == -1) return 0;
        return end - start + 1;
    }
};

class SuffixTree {
private:
    SuffixTreeNode* root;
    std::string text;
    int activeNode, activeEdge, activeLength;
    int remainingSuffixes;
    int leafEnd;
    
    SuffixTreeNode* newNode(int start, int end = -1) {
        return new SuffixTreeNode(start, end);
    }
    
    char getActiveEdge() const {
        return text[activeEdge];
    }
    
    bool walkDown(SuffixTreeNode* node) {
        int edgeLength = node->getLength();
        if (activeLength >= edgeLength) {
            activeEdge += edgeLength;
            activeLength -= edgeLength;
            activeNode = node->children[getActiveEdge()] - root;
            return true;
        }
        return false;
    }
    
    void extendSuffixTree(int pos) {
        leafEnd = pos;
        remainingSuffixes++;
        SuffixTreeNode* lastNewNode = nullptr;
        
        while (remainingSuffixes > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }
            
            char currentChar = text[pos];
            
            if (root->children.find(getActiveEdge()) == root->children.end()) {
                // Rule 1: Add new leaf edge
                root->children[getActiveEdge()] = newNode(pos, leafEnd);
                
                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = root;
                    lastNewNode = nullptr;
                }
            } else {
                SuffixTreeNode* next = root->children[getActiveEdge()];
                
                if (walkDown(next)) {
                    continue;
                }
                
                if (text[next->start + activeLength] == currentChar) {
                    // Rule 3: Extend current edge
                    activeLength++;
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = root;
                        lastNewNode = nullptr;
                    }
                    break;
                }
                
                // Rule 2: Split edge and add new leaf
                int splitEnd = next->start + activeLength - 1;
                SuffixTreeNode* split = newNode(next->start, splitEnd);
                
                root->children[getActiveEdge()] = split;
                split->children[text[next->start + activeLength]] = next;
                next->start += activeLength;
                split->children[currentChar] = newNode(pos, leafEnd);
                
                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }
                lastNewNode = split;
            }
            
            remainingSuffixes--;
            
            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixes + 1;
            } else if (activeNode != root) {
                activeNode = root->suffixLink - root;
            }
        }
    }
    
    void setSuffixIndex(SuffixTreeNode* node, int labelHeight) {
        if (node == nullptr) return;
        
        bool isLeaf = true;
        for (auto& child : node->children) {
            isLeaf = false;
            setSuffixIndex(child.second, labelHeight + child.second->getLength());
        }
        
        if (isLeaf) {
            node->suffixIndex = text.length() - labelHeight;
        }
    }
    
public:
    SuffixTree(const std::string& t) : text(t), activeNode(0), activeEdge(0), 
                                       activeLength(0), remainingSuffixes(0), leafEnd(-1) {
        root = newNode(-1, -1);
        root->suffixLink = root;
        
        for (int i = 0; i < text.length(); ++i) {
            extendSuffixTree(i);
        }
        
        setSuffixIndex(root, 0);
    }
    
    // Search for pattern in suffix tree
    bool searchPattern(const std::string& pattern) const {
        SuffixTreeNode* current = root;
        int patternIndex = 0;
        
        while (patternIndex < pattern.length()) {
            char currentChar = pattern[patternIndex];
            
            if (current->children.find(currentChar) == current->children.end()) {
                return false;
            }
            
            SuffixTreeNode* next = current->children[currentChar];
            int edgeLength = next->getLength();
            
            // Check if pattern matches the edge
            for (int i = 0; i < edgeLength && patternIndex < pattern.length(); ++i) {
                if (text[next->start + i] != pattern[patternIndex]) {
                    return false;
                }
                patternIndex++;
            }
            
            current = next;
        }
        
        return true;
    }
    
    // Get all occurrences of pattern
    std::vector<int> getAllOccurrences(const std::string& pattern) const {
        std::vector<int> occurrences;
        SuffixTreeNode* current = root;
        int patternIndex = 0;
        
        while (patternIndex < pattern.length()) {
            char currentChar = pattern[patternIndex];
            
            if (current->children.find(currentChar) == current->children.end()) {
                return occurrences;
            }
            
            SuffixTreeNode* next = current->children[currentChar];
            int edgeLength = next->getLength();
            
            for (int i = 0; i < edgeLength && patternIndex < pattern.length(); ++i) {
                if (text[next->start + i] != pattern[patternIndex]) {
                    return occurrences;
                }
                patternIndex++;
            }
            
            current = next;
        }
        
        // Collect all leaf nodes under current node
        collectLeafIndices(current, occurrences);
        return occurrences;
    }
    
private:
    void collectLeafIndices(SuffixTreeNode* node, std::vector<int>& indices) const {
        if (node == nullptr) return;
        
        if (node->suffixIndex != -1) {
            indices.push_back(node->suffixIndex);
        }
        
        for (auto& child : node->children) {
            collectLeafIndices(child.second, indices);
        }
    }
};
```

## Advanced Pattern Matching

### Aho-Corasick Algorithm

```cpp
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>

struct TrieNode {
    std::map<char, TrieNode*> children;
    TrieNode* failureLink;
    std::vector<int> patternIndices;
    bool isEndOfPattern;
    
    TrieNode() : failureLink(nullptr), isEndOfPattern(false) {}
};

class AhoCorasick {
private:
    TrieNode* root;
    std::vector<std::string> patterns;
    
    void buildTrie() {
        for (int i = 0; i < patterns.size(); ++i) {
            const std::string& pattern = patterns[i];
            TrieNode* current = root;
            
            for (char c : pattern) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            
            current->isEndOfPattern = true;
            current->patternIndices.push_back(i);
        }
    }
    
    void buildFailureLinks() {
        std::queue<TrieNode*> q;
        
        // Set failure links for depth 1 nodes
        for (auto& child : root->children) {
            child.second->failureLink = root;
            q.push(child.second);
        }
        
        // BFS to set failure links for deeper nodes
        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();
            
            for (auto& child : current->children) {
                char c = child.first;
                TrieNode* childNode = child.second;
                
                TrieNode* failure = current->failureLink;
                while (failure != nullptr && failure->children.find(c) == failure->children.end()) {
                    failure = failure->failureLink;
                }
                
                if (failure != nullptr) {
                    childNode->failureLink = failure->children[c];
                    // Merge pattern indices
                    childNode->patternIndices.insert(
                        childNode->patternIndices.end(),
                        childNode->failureLink->patternIndices.begin(),
                        childNode->failureLink->patternIndices.end()
                    );
                } else {
                    childNode->failureLink = root;
                }
                
                q.push(childNode);
            }
        }
    }
    
public:
    AhoCorasick(const std::vector<std::string>& pats) : patterns(pats) {
        root = new TrieNode();
        buildTrie();
        buildFailureLinks();
    }
    
    // Search for all patterns in text
    std::vector<std::pair<int, int>> searchPatterns(const std::string& text) {
        std::vector<std::pair<int, int>> matches;
        TrieNode* current = root;
        
        for (int i = 0; i < text.length(); ++i) {
            char c = text[i];
            
            // Follow failure links until we find a valid transition
            while (current != nullptr && current->children.find(c) == current->children.end()) {
                current = current->failureLink;
            }
            
            if (current == nullptr) {
                current = root;
                continue;
            }
            
            current = current->children[c];
            
            // Check for pattern matches
            for (int patternIndex : current->patternIndices) {
                int startPos = i - patterns[patternIndex].length() + 1;
                matches.push_back({startPos, patternIndex});
            }
        }
        
        return matches;
    }
    
    // Destructor to free memory
    ~AhoCorasick() {
        deleteTrie(root);
    }
    
private:
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        
        for (auto& child : node->children) {
            deleteTrie(child.second);
        }
        delete node;
    }
};
```

### Boyer-Moore-Horspool Algorithm

```cpp
#include <vector>
#include <string>
#include <iostream>

class BoyerMooreHorspool {
private:
    std::string pattern;
    std::vector<int> badCharTable;
    
    void buildBadCharTable() {
        int m = pattern.length();
        badCharTable.resize(256, m);
        
        for (int i = 0; i < m - 1; ++i) {
            badCharTable[pattern[i]] = m - 1 - i;
        }
    }
    
public:
    BoyerMooreHorspool(const std::string& pat) : pattern(pat) {
        buildBadCharTable();
    }
    
    std::vector<int> search(const std::string& text) {
        std::vector<int> occurrences;
        int n = text.length();
        int m = pattern.length();
        
        if (m > n) return occurrences;
        
        int i = m - 1;
        while (i < n) {
            int j = m - 1;
            int k = i;
            
            while (j >= 0 && text[k] == pattern[j]) {
                k--;
                j--;
            }
            
            if (j == -1) {
                occurrences.push_back(k + 1);
            }
            
            i += badCharTable[text[i]];
        }
        
        return occurrences;
    }
};
```

## String Compression and Encoding

### Run-Length Encoding (RLE)

```cpp
#include <string>
#include <iostream>

class RunLengthEncoding {
public:
    static std::string encode(const std::string& input) {
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
    
    static std::string decode(const std::string& encoded) {
        std::string decoded;
        int i = 0;
        
        while (i < encoded.length()) {
            // Extract count
            int count = 0;
            while (i < encoded.length() && std::isdigit(encoded[i])) {
                count = count * 10 + (encoded[i] - '0');
                i++;
            }
            
            if (i < encoded.length()) {
                char c = encoded[i];
                decoded.append(count, c);
                i++;
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
    HuffmanNode* left, *right;
    
    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
    
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCoding {
private:
    HuffmanNode* root;
    std::unordered_map<char, std::string> encodingTable;
    
    void buildEncodingTable(HuffmanNode* node, std::string code) {
        if (node == nullptr) return;
        
        if (node->isLeaf()) {
            encodingTable[node->data] = code;
            return;
        }
        
        buildEncodingTable(node->left, code + "0");
        buildEncodingTable(node->right, code + "1");
    }
    
    void deleteTree(HuffmanNode* node) {
        if (node == nullptr) return;
        
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    HuffmanCoding(const std::string& text) : root(nullptr) {
        buildHuffmanTree(text);
        if (root != nullptr) {
            buildEncodingTable(root, "");
        }
    }
    
    void buildHuffmanTree(const std::string& text) {
        // Count frequencies
        std::unordered_map<char, int> frequencies;
        for (char c : text) {
            frequencies[c]++;
        }
        
        if (frequencies.empty()) return;
        
        // Create priority queue
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
        
        for (const auto& pair : frequencies) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }
        
        // Build tree
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();
            
            HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;
            
            pq.push(parent);
        }
        
        root = pq.top();
    }
    
    std::string encode(const std::string& text) {
        std::string encoded;
        for (char c : text) {
            if (encodingTable.find(c) != encodingTable.end()) {
                encoded += encodingTable[c];
            }
        }
        return encoded;
    }
    
    std::string decode(const std::string& encoded) {
        std::string decoded;
        HuffmanNode* current = root;
        
        for (char bit : encoded) {
            if (bit == '0') {
                current = current->left;
            } else if (bit == '1') {
                current = current->right;
            }
            
            if (current->isLeaf()) {
                decoded += current->data;
                current = root;
            }
        }
        
        return decoded;
    }
    
    void printEncodingTable() const {
        std::cout << "Huffman Encoding Table:\n";
        for (const auto& pair : encodingTable) {
            std::cout << "'" << pair.first << "' -> " << pair.second << "\n";
        }
    }
    
    ~HuffmanCoding() {
        deleteTree(root);
    }
};
```

## Summary

Advanced string matching algorithms provide solutions for:

- **Suffix structures**: Suffix arrays and suffix trees for efficient substring operations
- **Multi-pattern matching**: Aho-Corasick for finding multiple patterns simultaneously
- **Optimized pattern matching**: Boyer-Moore-Horspool for fast single pattern search
- **String compression**: RLE and Huffman coding for data compression

Key applications:
- **Bioinformatics**: DNA/RNA sequence analysis
- **Text processing**: Search engines, plagiarism detection
- **Data compression**: File compression, network protocols
- **Information retrieval**: Document search, pattern recognition
- **Natural language processing**: Text analysis, language modeling

These algorithms form the foundation for efficient string processing in various computational domains.
