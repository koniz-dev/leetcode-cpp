class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }

        int m = nums1.size();
        int n = nums2.size();

        int leftSize = (m + n + 1) / 2;

        int low = 0, high = m;

        while (low <= high) {
            int i = (low + high) / 2;
            int j = leftSize - i;

            int L1 = (i == 0) ? INT_MIN : nums1[i - 1];
            int R1 = (i == m) ? INT_MAX : nums1[i];

            int L2 = (j == 0) ? INT_MIN : nums2[j - 1];
            int R2 = (j == n) ? INT_MAX : nums2[j];

            if (L1 <= R2 && L2 <= R1) {
                if ((m + n) % 2 != 0) {
                    return max(L1, L2);
                } else {
                    return (max(L1, L2) + min(R1, R2)) / 2.0;
                }
            } else if (L1 > R2) {
                high = i - 1;
            } else {
                low = i + 1;
            }
        }

        return 0.0;
    }
};