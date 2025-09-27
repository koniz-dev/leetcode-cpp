class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            if (nums.empty()) return 0;
    
            unordered_set<int> numSet;
    
            for (int i = 0; i < nums.size(); i++) {
                numSet.insert(nums[i]);
            }
    
            int longestConsecutiveSequence = 1;
            for (int num: numSet) {
                auto it = numSet.find(num - 1);
    
                if (it != numSet.end()) {
                    continue;
                } else {
                    int currNum = num;
                    int currentConsecutiveSequence = 1;
    
                    while (numSet.find(currNum + 1) != numSet.end()) {
                        currentConsecutiveSequence++;
                        currNum++;
                    }
                    longestConsecutiveSequence = max(currentConsecutiveSequence, longestConsecutiveSequence);
                }
            }
    
            return longestConsecutiveSequence;
        }
    };