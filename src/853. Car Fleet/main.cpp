class Solution {
    public:
        int carFleet(int target, vector<int>& position, vector<int>& speed) {
            vector<pair<int, int>> cars;
            for (int i = 0; i < position.size(); i++) {
                cars.push_back({position[i], speed[i]});
            }
            sort(cars.rbegin(), cars.rend(), [] (const pair<int, int> &a, const pair<int, int> &b) {
                return a.first < b.first;
            });
    
            stack<double> st;
            st.push(double (target - cars[0].first) / cars[0].second);
            for (int i = 1; i < cars.size(); i++) {
                double avgTime = double (target - cars[i].first) / cars[i].second;
                double top = st.top();
    
                if (avgTime > top) st.push(avgTime);
            }
    
            int countFleet = 0;
            while(!st.empty()) {
                countFleet++;
                st.pop();
            }
    
            return countFleet;
        }
    };