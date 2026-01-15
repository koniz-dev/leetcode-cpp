#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int m = static_cast<int>(nums1.size());
        int n = static_cast<int>(nums2.size());

        int leftSize = (m + n + 1) / 2;
        int low = 0;
        int high = m;

        while (low <= high) {
            int i = low + (high - low) / 2;
            int j = leftSize - i;

            int L1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int R1 = (i == m) ? INT_MAX : nums1[i];
            int L2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int R2 = (j == n) ? INT_MAX : nums2[j];

            if (L1 <= R2 && L2 <= R1) {
                if ((m + n) % 2 != 0) {
                    return static_cast<double>(max(L1, L2));
                }
                return (static_cast<double>(max(L1, L2)) + static_cast<double>(min(R1, R2))) / 2.0;
            }

            if (L1 > R2) {
                high = i - 1;
            } else {
                low = i + 1;
            }
        }

        return 0.0;
    }
};

