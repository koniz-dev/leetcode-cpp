class Solution {
    public:
        int minEatingSpeed(vector<int>& piles, int h) {
            int maxPile = piles[0];
            for (int i = 1; i <  piles.size(); i++) {
                if (maxPile < piles[i]) {
                    maxPile = piles[i];
                }
            }
    
            int left = 1;
            int right = maxPile;
    
            while (left <= right) {
                int mid = left + (right - left) / 2;
                
                long long hourNeeded = 0;
                for (int i = 0; i < piles.size(); i++) {
                    hourNeeded += (piles[i] + mid - 1) / mid;
                }
    
                if (hourNeeded <= h) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
    
            return left;
        }
    };