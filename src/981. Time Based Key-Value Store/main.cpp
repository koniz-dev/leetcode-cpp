class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> map;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        map[key].push_back({ timestamp, value });
    }
    
    string get(string key, int timestamp) {
        if (map.find(key) == map.end()) return "";

        auto &vec = map[key];
        int left = 0;
        int right = vec.size() - 1;
        string result = "";

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (vec[mid].first <= timestamp) {
                result = vec[mid].second;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */