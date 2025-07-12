public class Solution {
    public string AddBinary(string a, string b) {
        string result = "";
        int carry = 0, total;
        int i = a.Length - 1;
        int j = b.Length - 1;
        while (i >= 0 || j >= 0 || Convert.ToBoolean(carry)) {
            total = carry;
            if (i >= 0) {
                total += Convert.ToInt32(a[i]) - 48;
                i -= 1;
            }
            if (j >= 0) {
                total += Convert.ToInt32(b[j]) - 48;
                j -= 1;
            }
            result = string.Concat(result, (total % 2).ToString());
            carry = total / 2;
        }
        char[] charArray = result.ToCharArray();
        Array.Reverse(charArray);
        return new string(charArray);
    }
}
