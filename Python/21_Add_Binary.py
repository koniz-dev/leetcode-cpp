class Solution(object):
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        
        # Truth Table for Binary Addition:
        # A   B   Total   Carry
        # 0   0   0       0
        # 0   1   1       0
        # 1   0   1       0
        # 1   1   0       1
        """
        # Initialize an empty list to store the result bits
        result = []
        # Initialize a variable to store the carry
        carry = 0
        # Initialize pointers to the end of strings a and b
        i = len(a) - 1
        j = len(b) - 1

        # Loop until all digits are processed and there is no carry left
        while i >= 0 or j >= 0 or carry:
            # Start with the carry from the previous addition
            total = carry

            # Add the current digit of string a to total if within bounds
            if i >= 0:
                total += int(a[i])
                i -= 1  # Move to the next digit on the left

            # Add the current digit of string b to total if within bounds
            if j >= 0:
                total += int(b[j])
                j -= 1  # Move to the next digit on the left

            # Append the least significant bit of total to the result
            result.append(str(total % 2))
            # Calculate the carry for the next iteration
            carry = total // 2

        # Join the result list into a string and reverse it
        # (since we're adding digits from right to left)
        return ''.join(reversed(result))
