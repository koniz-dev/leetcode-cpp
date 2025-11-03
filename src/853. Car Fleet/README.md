# [853. Car Fleet](https://leetcode.com/problems/car-fleet/)

## Problem Statement

There are `n` cars going to the same destination along a one-lane road. The destination is `target` miles away.

You are given two integer arrays `position` and `speed`, both of length `n`, where `position[i]` is the position of the `ith` car and `speed[i]` is the speed of the `ith` car (in miles per hour).

A car can never pass another car ahead of it, but it can catch up to it and drive together at the same speed. The faster car will slow down to match the slower car's speed. The distance between these two cars is ignored (i.e., they are assumed to have the same position).

A **car fleet** is some non-empty set of cars driving at the same position and same speed. Note that a single car is also a car fleet.

If a car catches up to a car fleet right at the destination point, it will still be considered as one car fleet.

Return *the number of car fleets that will arrive at the destination*.

**Example 1:**
```
Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
Output: 3
Explanation:
The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12.
The car starting at 0 (speed 1) does not catch up to any other car, so it is a fleet by itself.
The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6.
The fleet moves at speed 1 until it reaches target.
Note that no other cars meet these fleets before the destination, so the answer is 3.
```

**Example 2:**
```
Input: target = 10, position = [3], speed = [3]
Output: 1
Explanation: There is only one car, hence there is only one fleet.
```

**Example 3:**
```
Input: target = 100, position = [0,2,4], speed = [4,2,1]
Output: 1
Explanation:
The cars starting at 0 (speed 4) and 2 (speed 2) become a fleet at 4.
The car starting at 4 (speed 1) becomes a fleet at 4.
Then the two fleets become one fleet at 8.
```

**Constraints:**
- `n == position.length == speed.length`
- `1 <= n <= 10^5`
- `0 < position[i] < target`
- `1 <= speed[i] <= 10^6`

## Solutions

### 1. Optimized Solution (Stack with Sorting) - `optimized.cpp`

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

Uses stack to track fleet leaders and sorting to process cars in order of proximity to target. A car forms a new fleet only if it takes longer to reach the target than the fleet leader ahead of it.

**Implementation:** See `optimized.cpp`

### 2. Stack Implementation - `main.cpp`

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

Similar approach to optimized solution with alternative implementation style.

**Implementation:** See `main.cpp`

### 3. Brute Force Simulation

**Time Complexity:** O(n × target)  
**Space Complexity:** O(n)

Simulate each time step until all cars reach target. At each step, update positions and check for collisions/merging.

```cpp
int carFleet(int target, vector<int>& position, vector<int>& speed) {
    int n = position.size();
    if (n == 0) return 0;
    
    // Create pairs of (position, speed) and track fleet IDs
    vector<pair<int, int>> cars;
    vector<int> fleetId(n);  // Track which fleet each car belongs to
    for (int i = 0; i < n; i++) {
        cars.push_back({position[i], speed[i]});
        fleetId[i] = i;  // Initially, each car is its own fleet
    }
    
    vector<bool> reached(n, false);
    
    // Simulate until all cars reach target
    while (true) {
        bool allReached = true;
        
        // Update positions for cars not yet reached
        for (int i = 0; i < n; i++) {
            if (!reached[i]) {
                allReached = false;
                cars[i].first += cars[i].second;
                if (cars[i].first >= target) {
                    cars[i].first = target;
                    reached[i] = true;
                }
            }
        }
        
        if (allReached) break;
        
        // Check for merging: cars at same position form a fleet
        for (int i = 0; i < n; i++) {
            if (reached[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (reached[j]) continue;
                if (cars[i].first == cars[j].first) {
                    // Merge fleets: update fleet IDs to the smaller one
                    int minFleetId = min(fleetId[i], fleetId[j]);
                    int maxFleetId = max(fleetId[i], fleetId[j]);
                    
                    // Update all cars in the larger fleet to join the smaller fleet
                    for (int k = 0; k < n; k++) {
                        if (fleetId[k] == maxFleetId) {
                            fleetId[k] = minFleetId;
                        }
                    }
                    
                    // Set speed to the slower car (min speed)
                    int minSpeed = min(cars[i].second, cars[j].second);
                    cars[i].second = minSpeed;
                    cars[j].second = minSpeed;
                }
            }
        }
    }
    
    // Count unique fleet IDs
    set<int> uniqueFleets;
    for (int i = 0; i < n; i++) {
        uniqueFleets.insert(fleetId[i]);
    }
    
    return uniqueFleets.size();
}
```

**Note:** This approach is too slow for large inputs and is included for learning purposes only.

## DSA Concepts Used

### 1. Stack Data Structure
- **Purpose**: Track fleet leaders (slowest car in each fleet)
- **Why Important**: Helps determine if a car forms a new fleet or joins an existing one
- **Key Insight**: Stack stores the time to reach target for each fleet leader
- **Pattern**: Monotonic stack pattern for tracking fleet formation

### 2. Sorting
- **Purpose**: Process cars from closest to target to farthest
- **Why Important**: Enables efficient processing by handling cars in order of proximity to destination
- **Key Insight**: Sorting by position (descending) allows us to process cars sequentially

### 3. Greedy Algorithm
- **Strategy**: Determine fleet formation based on time to reach target
- **Optimization**: If a car's time > fleet leader's time, it forms a new fleet
- **Efficiency**: Single pass after sorting
- **Why It Works**: Each car's fleet membership only depends on the car immediately ahead

## Complexity Analysis

### Time Complexity: O(n log n)
- **Sorting**: O(n log n) - Dominates the algorithm
- **Stack Operations**: O(n) - Each car processed once
- **Overall**: O(n log n)

### Space Complexity: O(n)
- **Pairs Array**: O(n) - Store position and speed pairs
- **Stack**: O(n) - Worst case, each car forms its own fleet
- **Overall**: O(n)

## Key Insights

1. **Time Calculation**: Converting positions to time (`time = (target - position) / speed`) simplifies fleet comparison
2. **Fleet Formation**: A car forms a new fleet only if it takes longer to reach target than the fleet ahead
3. **Stack Pattern**: Using stack to track fleet leaders enables efficient sequential processing
4. **Sorting Strategy**: Processing cars closest to target first ensures correct fleet formation order

## Related Problems

- [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/) - Similar stack-based merging problem
- [1776. Car Fleet II](https://leetcode.com/problems/car-fleet-ii/) - Follow-up problem with more complex merging rules
- [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/) - Similar concept of merging overlapping intervals

