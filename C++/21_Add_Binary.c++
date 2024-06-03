class Solution {
public:
    string addBinary(string a, string b) {
        // Initialize an empty string to store the result and a variable for the carry
        string result;
        int carry = 0, total;

        // Set pointers i and j to the end of strings a and b, respectively
        int i = a.length() - 1;
        int j = b.length() - 1;

        // Loop until all digits are processed and there is no carry left
        while (i >= 0 || j >= 0 || carry) {
            // Start with the carry from the previous addition
            total = carry;

            // Add the current digit of string a to total if within bounds
            if (i >= 0) {
                total += int(a[i]) - 48;  // Convert char '0' or '1' to integer 0 or 1
                i -= 1;  // Move to the next digit on the left
            }

            // Add the current digit of string b to total if within bounds
            if (j >= 0) {
                total += int(b[j]) - 48;  // Convert char '0' or '1' to integer 0 or 1
                j -= 1;  // Move to the next digit on the left
            }

            // Append the least significant bit of total to the result
            result.append(to_string(total % 2));

            // Calculate the carry for the next iteration
            carry = total / 2;
        }

        // Reverse the result string as the digits were added in reverse order
        reverse(result.begin(), result.end());

        // Return the final result
        return result;
    }
};
