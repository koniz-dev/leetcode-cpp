class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
            stack<pair<int, int>> st;
            int largestArea = 0;
    
            for (int i = 0; i < heights.size(); i++) {
                int start = i;
    
                while (!st.empty() && st.top().second > heights[i]) {
                    auto [index, height] = st.top();
                    st.pop();
                    largestArea = max(largestArea, height * (i - index));
                    start = index;
                }
    
                st.push({start, heights[i]});
            }
    
            int n = heights.size();
            while (!st.empty()) {
                auto [index, height] = st.top();
                st.pop();
                largestArea = max(largestArea, height * (n - index));
            }
    
            return largestArea;
        }
    };