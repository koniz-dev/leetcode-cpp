public class Solution {
    public string AddBinary(string a, string b) {
        // Initialize an empty string to store the result and variables for carry and total.
        string result = "";
        int carry = 0, total;
        
        // Set pointers i and j to the end of strings a and b, respectively.
        int i = a.Length - 1;
        int j = b.Length - 1;

        // Loop until all digits are processed and there is no carry left.
        while (i >= 0 || j >= 0 || Convert.ToBoolean(carry)) {
            // Start with the carry from the previous addition.
            total = carry;

            // Add the current digit of string a to total if within bounds.
            if (i >= 0) {
                total += Convert.ToInt32(a[i]) - 48;  // Convert char '0' or '1' to integer 0 or 1.
                i -= 1;  // Move to the next digit on the left.
            }

            // Add the current digit of string b to total if within bounds.
            if (j >= 0) {
                total += Convert.ToInt32(b[j]) - 48;  // Convert char '0' or '1' to integer 0 or 1.
                j -= 1;  // Move to the next digit on the left.
            }

            // Append the least significant bit of total to the result.
            result = string.Concat(result, (total % 2).ToString());

            // Calculate the carry for the next iteration.
            carry = total / 2;
        }

        // Convert result string to a character array to reverse it.
        char[] charArray = result.ToCharArray();
        Array.Reverse(charArray);

        // Return the reversed result string.
        return new string(charArray);
    }
}
