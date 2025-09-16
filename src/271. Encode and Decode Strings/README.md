# 271. Encode and Decode Strings

## Problem Description
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

**Key Challenge**: Handle strings that may contain any characters, including delimiters, numbers, and special characters.

## DSA Concepts Used

### 1. String Manipulation
- **Length-prefix encoding**: Prepend each string with its length
- **Delimiter-based parsing**: Use a special character ('#') to separate length from content
- **Substring extraction**: Parse encoded data by extracting specific portions

### 2. Parsing Algorithms
- **State machine parsing**: Track position and parse length then content
- **Boundary detection**: Find delimiters to separate different parts of encoded data

### 3. Memory Management
- **Pre-allocation**: Calculate total size to avoid multiple reallocations
- **Move semantics**: Efficiently transfer string ownership

## Solution Approaches

### Approach 1: Length-Prefix Encoding (Optimal)
**Algorithm**: Use format `"length#string"` for each string

**Encode Process**:
1. For each string, prepend its length followed by '#'
2. Concatenate all encoded strings

**Decode Process**:
1. Find the '#' delimiter to separate length from content
2. Extract the length (number before '#')
3. Extract exactly that many characters after '#'
4. Move to next encoded string

**Time Complexity**: O(n) where n is total characters in all strings
**Space Complexity**: O(1) excluding input/output

**Why This Works**:
- Length prefix tells us exactly how many characters to read
- '#' delimiter clearly separates length from content
- Handles any characters in strings (including numbers and '#')

### Approach 2: Escape Character Encoding
**Algorithm**: Use escape sequences for special characters

**Limitations**:
- More complex to implement
- Requires defining escape sequences
- Less efficient for strings with many special characters

### Approach 3: Base64 Encoding
**Algorithm**: Convert strings to base64 format

**Limitations**:
- Increases string size by ~33%
- More complex encoding/decoding
- Overkill for this problem

## Key Learning Points

### 1. Encoding Design Principles
- **Unambiguous**: Each part of encoded data must be clearly identifiable
- **Efficient**: Minimize overhead while maintaining clarity
- **Robust**: Handle edge cases (empty strings, special characters)

### 2. String Parsing Techniques
- **Delimiter-based**: Use special characters to separate data sections
- **Length-prefix**: Include size information to know exactly how much to read
- **State tracking**: Keep track of current position in parsing

### 3. C++ Optimization Techniques
- **Memory pre-allocation**: Use `reserve()` to avoid multiple reallocations
- **Move semantics**: Use `move()` to transfer ownership efficiently
- **Const references**: Use `const auto&` to avoid unnecessary copies

## Edge Cases Handled

1. **Empty strings**: Length 0 is correctly encoded and decoded
2. **Strings containing numbers**: Length prefix is clearly separated by '#'
3. **Strings containing '#'**: Length tells us exactly where string ends
4. **Single character strings**: Handled correctly with length 1
5. **Very long strings**: No size limitations in the algorithm

## Complexity Analysis

### Time Complexity: O(n)
- **Encode**: Single pass through all characters in all strings
- **Decode**: Single pass through encoded string, each character processed once

### Space Complexity: O(1)
- **Encode**: Only output string space (not counted as extra space)
- **Decode**: Only output vector space (not counted as extra space)
- **No additional data structures** used during processing

## Alternative Implementations

### Using String Streams
```cpp
string encode(vector<string>& strs) {
    stringstream ss;
    for (const auto& str : strs) {
        ss << str.length() << "#" << str;
    }
    return ss.str();
}
```

### Using Modern C++ Features
```cpp
string encode(vector<string>& strs) {
    return accumulate(strs.begin(), strs.end(), string{},
        [](string acc, const string& str) {
            return acc + to_string(str.length()) + "#" + str;
        });
}
```

## Real-World Applications

1. **Network Protocols**: Encoding data for transmission
2. **File Formats**: Storing multiple strings in a single file
3. **Database Storage**: Efficiently storing string arrays
4. **Message Queues**: Serializing string collections
5. **Configuration Files**: Storing multiple configuration values

## Related Problems

- **394. Decode String**: Nested string decoding with brackets
- **443. String Compression**: Compressing strings in-place
- **68. Text Justification**: Formatting strings with specific constraints
- **151. Reverse Words in a String**: String manipulation and parsing

## Practice Recommendations

1. **Implement without looking**: Try to solve from scratch
2. **Handle edge cases**: Test with empty strings, special characters
3. **Optimize memory usage**: Use pre-allocation and move semantics
4. **Test thoroughly**: Verify with various input combinations
5. **Consider alternatives**: Think about other encoding schemes

## Key Takeaways

- **Length-prefix encoding** is a fundamental technique for handling variable-length data
- **Delimiter-based parsing** provides clear boundaries between data sections
- **Memory optimization** through pre-allocation can significantly improve performance
- **Edge case handling** is crucial for robust string manipulation algorithms
- **Modern C++ features** like move semantics can improve efficiency without changing algorithm complexity
