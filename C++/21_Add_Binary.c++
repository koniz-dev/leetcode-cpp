class Solution {
public:
    string addBinary(string a, string b) {
        string result;
        int carry = 0, total;
        int i = a.length() - 1;
        int j = b.length() - 1;
        while (i >= 0 || j >= 0 || carry) {
            total = carry;
            if (i >= 0) {
                total += int(a[i]) - 48;
                i -= 1;
            }
            if (j >= 0) {
                total += int(b[j]) - 48;
                j -= 1;
            }
            result.append(to_string(total % 2));
            carry = total / 2;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
