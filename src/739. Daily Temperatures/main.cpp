class Solution {
    public:
        vector<int> dailyTemperatures(vector<int>& temperatures) {
            vector<int> results(temperatures.size());
            stack<int> st;
    
            st.push(0);
            for (int i = 1; i < temperatures.size(); i++) {
                while (!st.empty()) {
                    int top = st.top();
                    results[top] = 0;
    
                    if (temperatures[top] < temperatures[i]) {
                        results[top] = i - top;
                        st.pop();
                    } else {
                        break;
                    }
                }
    
                st.push(i);
            }
    
            return results;
        }
    };