class Solution {
    public:
        vector<string> generateParenthesis(int n) {
            vector<string> results;
            stack<tuple<string, int, int>> st;
    
            st.push(make_tuple("", 0, 0));
            while (!st.empty()) {
                auto [current, open, close] = st.top();
                if (open == close && close == n) results.push_back(current);
                st.pop();
    
                if (open < n) {
                    st.push(make_tuple(current + "(", open + 1, close));
                }
    
                if (close < open) {
                    st.push(make_tuple(current + ")", open, close + 1));
                }
            }
    
            return results;
        }
    };