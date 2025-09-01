# Competitive Programming Techniques

## Overview

Competitive programming techniques are advanced algorithms and data structures used to solve complex problems efficiently within time and memory constraints. These techniques are essential for programming competitions, technical interviews, and real-world problem-solving.

## Fast I/O and Optimization

### Fast Input/Output

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

// Fast I/O for competitive programming
class FastIO {
private:
    static const int BUFFER_SIZE = 1 << 16;
    char buffer[BUFFER_SIZE];
    int bufferPos, bufferSize;
    FILE* file;
    
public:
    FastIO(FILE* f = stdin) : file(f), bufferPos(0), bufferSize(0) {}
    
    char getChar() {
        if (bufferPos >= bufferSize) {
            bufferSize = fread(buffer, 1, BUFFER_SIZE, file);
            bufferPos = 0;
            if (bufferSize == 0) return EOF;
        }
        return buffer[bufferPos++];
    }
    
    int readInt() {
        char c;
        int sign = 1, result = 0;
        
        // Skip whitespace
        while ((c = getChar()) == ' ' || c == '\n' || c == '\r' || c == '\t');
        
        // Handle sign
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        
        // Read digits
        while (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
            c = getChar();
        }
        
        return sign * result;
    }
    
    long long readLongLong() {
        char c;
        int sign = 1;
        long long result = 0;
        
        while ((c = getChar()) == ' ' || c == '\n' || c == '\r' || c == '\t');
        
        if (c == '-') {
            sign = -1;
            c = getChar();
        }
        
        while (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
            c = getChar();
        }
        
        return sign * result;
    }
    
    std::string readString() {
        std::string result;
        char c;
        
        while ((c = getChar()) == ' ' || c == '\n' || c == '\r' || c == '\t');
        
        while (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c != EOF) {
            result += c;
            c = getChar();
        }
        
        return result;
    }
    
    void writeInt(int x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        
        if (x == 0) {
            putchar('0');
            return;
        }
        
        char digits[20];
        int pos = 0;
        
        while (x > 0) {
            digits[pos++] = '0' + (x % 10);
            x /= 10;
        }
        
        while (pos > 0) {
            putchar(digits[--pos]);
        }
    }
    
    void writeLongLong(long long x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        
        if (x == 0) {
            putchar('0');
            return;
        }
        
        char digits[25];
        int pos = 0;
        
        while (x > 0) {
            digits[pos++] = '0' + (x % 10);
            x /= 10;
        }
        
        while (pos > 0) {
            putchar(digits[--pos]);
        }
    }
    
    void writeString(const std::string& s) {
        for (char c : s) {
            putchar(c);
        }
    }
    
    void writeChar(char c) {
        putchar(c);
    }
    
    void writeNewLine() {
        putchar('\n');
    }
    
    void writeSpace() {
        putchar(' ');
    }
};

// Usage example
FastIO io;
int n = io.readInt();
long long sum = io.readLongLong();
std::string s = io.readString();
io.writeInt(n);
io.writeNewLine();
```

### Template for Fast Solutions

```cpp
#include <bits/stdc++.h>
using namespace std;

// Fast I/O
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl '\n'

// Type definitions for convenience
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Constants
const int INF = 1e9;
const ll LLINF = 1e18;
const int MOD = 1e9 + 7;

// Debug macro
#define debug(x) cerr << #x << " = " << x << endl

// Custom hash for unordered_map/set
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// Usage: unordered_map<int, int, custom_hash> mp;
```

## Advanced Data Structures

### Persistent Segment Tree

```cpp
#include <vector>
#include <iostream>

struct Node {
    int left, right;
    int sum;
    Node() : left(-1), right(-1), sum(0) {}
};

class PersistentSegmentTree {
private:
    std::vector<Node> nodes;
    std::vector<int> roots;
    int n;
    
    int createNode() {
        nodes.emplace_back();
        return nodes.size() - 1;
    }
    
    int update(int node, int start, int end, int pos, int val) {
        int newNode = createNode();
        nodes[newNode] = nodes[node];
        
        if (start == end) {
            nodes[newNode].sum = val;
            return newNode;
        }
        
        int mid = (start + end) / 2;
        if (pos <= mid) {
            nodes[newNode].left = update(nodes[node].left, start, mid, pos, val);
        } else {
            nodes[newNode].right = update(nodes[node].right, mid + 1, end, pos, val);
        }
        
        nodes[newNode].sum = (nodes[newNode].left != -1 ? nodes[nodes[newNode].left].sum : 0) +
                             (nodes[newNode].right != -1 ? nodes[nodes[newNode].right].sum : 0);
        return newNode;
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (node == -1 || start > r || end < l) return 0;
        if (l <= start && end <= r) return nodes[node].sum;
        
        int mid = (start + end) / 2;
        return query(nodes[node].left, start, mid, l, r) +
               query(nodes[node].right, mid + 1, end, l, r);
    }
    
public:
    PersistentSegmentTree(int size) : n(size) {
        roots.push_back(createNode()); // Root for version 0
    }
    
    void update(int pos, int val) {
        int newRoot = update(roots.back(), 0, n - 1, pos, val);
        roots.push_back(newRoot);
    }
    
    int query(int version, int l, int r) {
        return query(roots[version], 0, n - 1, l, r);
    }
    
    int getCurrentVersion() const {
        return roots.size() - 1;
    }
};
```

### Heavy Light Decomposition

```cpp
#include <vector>
#include <iostream>

class HeavyLightDecomposition {
private:
    std::vector<std::vector<int>> adj;
    std::vector<int> parent, depth, size, heavy;
    std::vector<int> chain, pos;
    int n, chainCount, posCount;
    
    int dfs(int v, int p) {
        parent[v] = p;
        depth[v] = (p == -1) ? 0 : depth[p] + 1;
        size[v] = 1;
        heavy[v] = -1;
        
        int maxChildSize = 0;
        for (int u : adj[v]) {
            if (u != p) {
                int childSize = dfs(u, v);
                size[v] += childSize;
                if (childSize > maxChildSize) {
                    maxChildSize = childSize;
                    heavy[v] = u;
                }
            }
        }
        
        return size[v];
    }
    
    void decompose(int v, int head) {
        chain[v] = chainCount;
        pos[v] = posCount++;
        
        if (heavy[v] != -1) {
            decompose(heavy[v], head);
        }
        
        for (int u : adj[v]) {
            if (u != parent[v] && u != heavy[v]) {
                chainCount++;
                decompose(u, u);
            }
        }
    }
    
public:
    HeavyLightDecomposition(const std::vector<std::vector<int>>& adjacency) 
        : adj(adjacency), n(adjacency.size()), chainCount(0), posCount(0) {
        
        parent.resize(n);
        depth.resize(n);
        size.resize(n);
        heavy.resize(n);
        chain.resize(n);
        pos.resize(n);
        
        dfs(0, -1);
        decompose(0, 0);
    }
    
    // Get LCA using HLD
    int getLCA(int u, int v) {
        while (chain[u] != chain[v]) {
            if (depth[chain[u]] > depth[chain[v]]) {
                u = parent[chain[u]];
            } else {
                v = parent[chain[v]];
            }
        }
        
        return (depth[u] < depth[v]) ? u : v;
    }
    
    // Get path from u to v
    std::vector<int> getPath(int u, int v) {
        std::vector<int> path;
        int lca = getLCA(u, v);
        
        // Path from u to LCA
        while (u != lca) {
            path.push_back(u);
            u = parent[u];
        }
        path.push_back(lca);
        
        // Path from LCA to v (in reverse)
        std::vector<int> pathToV;
        while (v != lca) {
            pathToV.push_back(v);
            v = parent[v];
        }
        
        for (int i = pathToV.size() - 1; i >= 0; --i) {
            path.push_back(pathToV[i]);
        }
        
        return path;
    }
};
```

## Advanced Algorithms

### Mo's Algorithm (Square Root Decomposition)

```cpp
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

struct Query {
    int left, right, index;
    
    Query(int l, int r, int idx) : left(l), right(r), index(idx) {}
    
    bool operator<(const Query& other) const {
        int block1 = left / BLOCK_SIZE;
        int block2 = other.left / BLOCK_SIZE;
        
        if (block1 != block2) {
            return block1 < block2;
        }
        
        return (block1 % 2 == 0) ? (right < other.right) : (right > other.right);
    }
};

class MosAlgorithm {
private:
    static const int BLOCK_SIZE = 450; // sqrt(2e5)
    std::vector<int> arr;
    std::vector<Query> queries;
    std::vector<int> frequency;
    int currentSum;
    
public:
    MosAlgorithm(const std::vector<int>& array) : arr(array), currentSum(0) {
        frequency.resize(100001, 0);
    }
    
    void addQuery(int left, int right, int index) {
        queries.emplace_back(left, right, index);
    }
    
    std::vector<int> solve() {
        std::sort(queries.begin(), queries.end());
        
        std::vector<int> results(queries.size());
        int currentLeft = 0, currentRight = -1;
        
        for (const Query& query : queries) {
            // Expand range to include query
            while (currentLeft > query.left) {
                currentLeft--;
                add(currentLeft);
            }
            
            while (currentRight < query.right) {
                currentRight++;
                add(currentRight);
            }
            
            // Contract range to exclude query
            while (currentLeft < query.left) {
                remove(currentLeft);
                currentLeft++;
            }
            
            while (currentRight > query.right) {
                remove(currentRight);
                currentRight--;
            }
            
            results[query.index] = currentSum;
        }
        
        return results;
    }
    
private:
    void add(int index) {
        int val = arr[index];
        if (frequency[val] == 0) {
            currentSum++;
        }
        frequency[val]++;
    }
    
    void remove(int index) {
        int val = arr[index];
        frequency[val]--;
        if (frequency[val] == 0) {
            currentSum--;
        }
    }
};
```

### Centroid Decomposition

```cpp
#include <vector>
#include <iostream>

class CentroidDecomposition {
private:
    std::vector<std::vector<int>> adj;
    std::vector<bool> removed;
    std::vector<int> size;
    std::vector<int> parent;
    int n;
    
    int getSize(int v, int p) {
        size[v] = 1;
        for (int u : adj[v]) {
            if (u != p && !removed[u]) {
                size[v] += getSize(u, v);
            }
        }
        return size[v];
    }
    
    int findCentroid(int v, int p, int totalSize) {
        for (int u : adj[v]) {
            if (u != p && !removed[u] && size[u] > totalSize / 2) {
                return findCentroid(u, v, totalSize);
            }
        }
        return v;
    }
    
    void decompose(int v, int p) {
        int totalSize = getSize(v, -1);
        int centroid = findCentroid(v, -1, totalSize);
        
        removed[centroid] = true;
        parent[centroid] = p;
        
        for (int u : adj[centroid]) {
            if (!removed[u]) {
                decompose(u, centroid);
            }
        }
    }
    
public:
    CentroidDecomposition(const std::vector<std::vector<int>>& adjacency) 
        : adj(adjacency), n(adjacency.size()) {
        
        removed.resize(n, false);
        size.resize(n);
        parent.resize(n, -1);
        
        decompose(0, -1);
    }
    
    // Get centroid tree parent
    int getCentroidParent(int v) const {
        return parent[v];
    }
    
    // Check if node is removed (is a centroid)
    bool isCentroid(int v) const {
        return removed[v];
    }
};
```

## Mathematical Techniques

### Fast Fourier Transform (FFT)

```cpp
#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

class FFT {
private:
    static const double PI = 3.14159265358979323846;
    
    static void fft(std::vector<std::complex<double>>& a, bool invert) {
        int n = a.size();
        
        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) {
                j ^= bit;
            }
            j ^= bit;
            
            if (i < j) {
                std::swap(a[i], a[j]);
            }
        }
        
        // FFT computation
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            std::complex<double> wlen(cos(ang), sin(ang));
            
            for (int i = 0; i < n; i += len) {
                std::complex<double> w(1);
                for (int j = 0; j < len / 2; ++j) {
                    std::complex<double> u = a[i + j];
                    std::complex<double> v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        
        if (invert) {
            for (auto& x : a) {
                x /= n;
            }
        }
    }
    
public:
    // Multiply two polynomials
    static std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<std::complex<double>> fa(a.begin(), a.end());
        std::vector<std::complex<double>> fb(b.begin(), b.end());
        
        int n = 1;
        while (n < a.size() + b.size()) {
            n <<= 1;
        }
        
        fa.resize(n);
        fb.resize(n);
        
        fft(fa, false);
        fft(fb, false);
        
        for (int i = 0; i < n; ++i) {
            fa[i] *= fb[i];
        }
        
        fft(fa, true);
        
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = round(fa[i].real());
        }
        
        return result;
    }
};
```

### Extended Euclidean Algorithm

```cpp
#include <iostream>
#include <tuple>

class ExtendedEuclidean {
public:
    // Returns {gcd, x, y} where ax + by = gcd(a, b)
    static std::tuple<long long, long long, long long> extendedGcd(long long a, long long b) {
        if (b == 0) {
            return {a, 1, 0};
        }
        
        auto [gcd, x1, y1] = extendedGcd(b, a % b);
        long long x = y1;
        long long y = x1 - (a / b) * y1;
        
        return {gcd, x, y};
    }
    
    // Find modular multiplicative inverse
    static long long modInverse(long long a, long long m) {
        auto [gcd, x, y] = extendedGcd(a, m);
        
        if (gcd != 1) {
            return -1; // Inverse doesn't exist
        }
        
        return (x % m + m) % m;
    }
    
    // Solve linear congruence ax ≡ b (mod m)
    static std::pair<long long, long long> solveLinearCongruence(long long a, long long b, long long m) {
        auto [gcd, x, y] = extendedGcd(a, m);
        
        if (b % gcd != 0) {
            return {-1, -1}; // No solution
        }
        
        long long x0 = (x * (b / gcd)) % m;
        long long period = m / gcd;
        
        return {x0, period};
    }
};
```

## Optimization Techniques

### Binary Search on Answer

```cpp
#include <vector>
#include <iostream>

class BinarySearchOnAnswer {
public:
    // Binary search for minimum value that satisfies condition
    template<typename F>
    static long long binarySearchMin(long long left, long long right, F&& check) {
        long long result = right;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            if (check(mid)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
    // Binary search for maximum value that satisfies condition
    template<typename F>
    static long long binarySearchMax(long long left, long long right, F&& check) {
        long long result = left;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            
            if (check(mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Binary search with doubles (for precision problems)
    template<typename F>
    static double binarySearchDouble(double left, double right, F&& check, double epsilon = 1e-9) {
        while (right - left > epsilon) {
            double mid = left + (right - left) / 2;
            
            if (check(mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        
        return left;
    }
};
```

### Two Pointers Technique

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

class TwoPointers {
public:
    // Find pairs with given sum in sorted array
    static std::vector<std::pair<int, int>> findPairsWithSum(const std::vector<int>& arr, int target) {
        std::vector<std::pair<int, int>> pairs;
        int left = 0, right = arr.size() - 1;
        
        while (left < right) {
            int sum = arr[left] + arr[right];
            
            if (sum == target) {
                pairs.push_back({arr[left], arr[right]});
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return pairs;
    }
    
    // Find minimum subarray with sum >= target
    static int minSubarrayLength(const std::vector<int>& arr, int target) {
        int n = arr.size();
        int left = 0, sum = 0;
        int minLength = n + 1;
        
        for (int right = 0; right < n; ++right) {
            sum += arr[right];
            
            while (sum >= target) {
                minLength = std::min(minLength, right - left + 1);
                sum -= arr[left];
                left++;
            }
        }
        
        return minLength <= n ? minLength : 0;
    }
    
    // Find longest subarray with at most k distinct elements
    static int longestSubarrayWithKDistinct(const std::vector<int>& arr, int k) {
        std::unordered_map<int, int> frequency;
        int left = 0, maxLength = 0;
        
        for (int right = 0; right < arr.size(); ++right) {
            frequency[arr[right]]++;
            
            while (frequency.size() > k) {
                frequency[arr[left]]--;
                if (frequency[arr[left]] == 0) {
                    frequency.erase(arr[left]);
                }
                left++;
            }
            
            maxLength = std::max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
```

## Summary

Competitive programming techniques provide solutions for:

- **Fast I/O**: Optimized input/output for large datasets
- **Advanced data structures**: Persistent structures, HLD, centroid decomposition
- **Advanced algorithms**: Mo's algorithm, FFT, extended Euclidean
- **Optimization techniques**: Binary search on answer, two pointers

Key applications:
- **Programming competitions**: ICPC, Codeforces, TopCoder
- **Technical interviews**: Algorithm design, optimization
- **Real-world problems**: Large-scale data processing, optimization
- **Algorithm research**: New algorithm development, complexity analysis

These techniques form the foundation for solving complex algorithmic problems efficiently.
