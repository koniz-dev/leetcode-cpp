/**
 * Solution 1
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function (a, b) {
  // Initialize an array to store the result bits
  let result = [];
  // Initialize a variable to store the carry
  let carry = 0;
  // Initialize pointers to the end of strings a and b
  let i = a.length - 1;
  let j = b.length - 1;

  // Loop until all digits are processed and there is no carry left
  while (i >= 0 || j >= 0 || carry) {
    // Start with the carry from the previous addition
    let total = carry;

    // Add the current digit of string a to total if within bounds
    if (i >= 0) {
      total += parseInt(a[i]);
      i -= 1; // Move to the next digit on the left
    }

    // Add the current digit of string b to total if within bounds
    if (j >= 0) {
      total += parseInt(b[j]);
      j -= 1; // Move to the next digit on the left
    }

    // Append the least significant bit of total to the result
    result.push((total % 2).toString());
    // Calculate the carry for the next iteration
    carry = Math.floor(total / 2);
  }

  // Reverse the result array and join to form the binary string
  return result.reverse().join("");
};

/**
 * Solution 2
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function (a, b) {
  // Convert binary strings to BigInt and perform addition, then convert back to binary string
  return (BigInt(`0b${a}`) + BigInt(`0b${b}`)).toString(2);
};
