#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class Solution {
public:
    /*
     * Car Fleet - Optimized Solution using Stack and Sorting
     * 
     * Approach:
     * - Sort cars by position (closest to target first, descending order)
     * - Calculate time to reach target for each car: (target - position) / speed
     * - Use stack to track fleet leaders (slowest car in each fleet)
     * - If current car's time > top of stack, it forms a new fleet
     * - Otherwise, current car will catch up to the fleet ahead (same fleet)
     * - Return the number of distinct fleets (stack size)
     * 
     * Time Complexity: O(n log n) - Sorting dominates the algorithm
     * Space Complexity: O(n) - Stack and pairs array for sorting
     */
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;
        
        // Create pairs of (position, speed) for each car
        vector<pair<int, int>> cars;
        cars.reserve(n);  // Reserve space for efficiency
        for (int i = 0; i < n; i++) {
            cars.push_back({position[i], speed[i]});
        }
        
        // Sort cars by position in descending order (closest to target first)
        // This allows us to process cars from closest to farthest
        sort(cars.begin(), cars.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;  // Sort descending by position
        });
        
        // Stack stores the time to reach target for each fleet leader
        // Fleet leader is the slowest car in each fleet (takes longest to reach target)
        stack<double> fleetStack;
        
        // Process each car from closest to target to farthest
        for (const auto& car : cars) {
            // Calculate time for current car to reach target
            double timeToTarget = static_cast<double>(target - car.first) / car.second;
            
            // If stack is empty, this is the first car (creates first fleet)
            if (fleetStack.empty()) {
                fleetStack.push(timeToTarget);
                continue;
            }
            
            // If current car takes longer than the fleet leader ahead,
            // it cannot catch up, so it forms a new fleet
            if (timeToTarget > fleetStack.top()) {
                fleetStack.push(timeToTarget);  // New fleet created
            }
            // Otherwise, current car will catch up to the fleet ahead
            // (same fleet, no need to push to stack)
        }
        
        // Number of fleets equals the number of fleet leaders (stack size)
        return fleetStack.size();
    }
};

