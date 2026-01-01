#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
 * Time Based Key-Value Store - Optimized Solution using Hash Map and Binary Search
 * 
 * Approach:
 * - Use an unordered_map to map keys to a vector of {timestamp, value} pairs.
 * - The problem guarantees that set() is called with strictly increasing timestamps.
 *   This means the vector for each key is naturally sorted by timestamp.
 * - For get(key, timestamp), we need to find the largest timestamp <= target_timestamp.
 * - Since the vector is sorted, we can use Binary Search (specifically upper_bound).
 * 
 * Time Complexity: 
 *   - set: O(1) - Amortized constant time to append to vector.
 *   - get: O(log n) - Binary search on the vector of size n (number of entries for that key).
 * Space Complexity: O(n) - To store all key-value-timestamp entries.
 */
class TimeMap {
private:
    // Key -> Vector of pairs (timestamp, value)
    unordered_map<string, vector<pair<int, string>>> store;

public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        // Since timestamps are strictly increasing, we can just append
        store[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        // If key doesn't exist, return empty string
        if (store.find(key) == store.end()) {
            return "";
        }
        
        const auto& values = store[key];
        
        // Use upper_bound to find the first element with timestamp > target
        // We want to search for a pair with {timestamp, ""} but since we only care about
        // the first element of the pair for comparison, we need a custom comparator 
        // or construct a dummy pair with a value that handles strict ordering correctly.
        // Actually, default pair comparison compares first element, then second.
        // We want first element > timestamp.
        // So we can search for {timestamp, [max_string]} so that it's strictly greater?
        // No, cleaner to use a lambda comparator or just write the binary search manually if pair comparison is tricky.
        // But let's try std::upper_bound with a custom comparator comparing only the integer timestamp.
        
        auto it = upper_bound(values.begin(), values.end(), timestamp,
            [](int val, const pair<int, string>& p) {
                return val < p.first;
            });
            
        // 'it' points to the first element > timestamp.
        // The element we want is the one just before 'it'.
        
        if (it == values.begin()) {
            // All timestamps are > target, so no valid value exists
            return "";
        }
        
        // Return the value of the element before 'it'
        return prev(it)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
