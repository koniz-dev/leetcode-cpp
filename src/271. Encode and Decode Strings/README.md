# 271. Encode and Decode Strings

## Problem Description
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

**Key Challenge**: Handle strings that may contain any characters, including delimiters, numbers, and special characters.

**Examples**:
- Input: `["neet", "code", "love", "you"]` → Output: `["neet", "code", "love", "you"]`
- Input: `["we", "say", ":", "yes"]` → Output: `["we", "say", ":", "yes"]`

**Constraints**:
- `0 <= strs.length < 100`
- `0 <= strs[i].length < 200`
- `strs[i] contains only UTF-8 characters`

## DSA Concepts Used

### 1. String Manipulation & Encoding
- **Length-prefix encoding**: Prepend each string with its length for unambiguous parsing
- **Delimiter-based parsing**: Use a special character ('#') to separate length from content
- **Substring extraction**: Parse encoded data by extracting specific portions
- **String concatenation**: Efficiently combine multiple encoded strings

### 2. Parsing Algorithms
- **State machine parsing**: Track position and parse length then content sequentially
- **Boundary detection**: Find delimiters to separate different parts of encoded data
- **Sequential processing**: Process encoded data from left to right without backtracking

### 3. Memory Management & Optimization
- **Pre-allocation**: Calculate total size to avoid multiple reallocations
- **Move semantics**: Efficiently transfer string ownership without copying
- **Reserve capacity**: Use `reserve()` to optimize string growth

## Solution Approaches

### Approach 1: Length-Prefix Encoding (Optimal) ⭐
**Algorithm**: Use format `"length#string"` for each string

**Encode Process**:
1. For each string, prepend its length followed by '#'
2. Concatenate all encoded strings
3. Example: `["abc", "def"]` → `"3#abc3#def"`

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
- No ambiguity in parsing - each string boundary is clearly defined

**Example Walkthrough**:
```
Input: ["we", "say", ":", "yes"]
Encode: "2#we3#say1#:3#yes"
Decode: 
  - Read "2#" → length=2, read "we"
  - Read "3#" → length=3, read "say"  
  - Read "1#" → length=1, read ":"
  - Read "3#" → length=3, read "yes"
```

### Approach 2: Escape Character Encoding
**Algorithm**: Use escape sequences for special characters

**Implementation**: Replace special characters with escape sequences
- Use `\:` for colon, `\#` for hash, `\\` for backslash
- More complex parsing required

**Limitations**:
- More complex to implement and debug
- Requires defining comprehensive escape sequences
- Less efficient for strings with many special characters
- Error-prone if escape sequences are not handled correctly

### Approach 3: Base64 Encoding
**Algorithm**: Convert strings to base64 format

**Implementation**: Encode each string to base64, separate with delimiters

**Limitations**:
- Increases string size by ~33% (4/3 ratio)
- More complex encoding/decoding process
- Overkill for this problem - adds unnecessary complexity
- Requires base64 library or custom implementation

### Approach 4: JSON-like Encoding
**Algorithm**: Use JSON array format with proper escaping

**Limitations**:
- Requires JSON parsing library
- More overhead than needed
- Complex escaping rules
- Not suitable for simple string encoding

## Key Learning Points

### 1. Encoding Design Principles
- **Unambiguous**: Each part of encoded data must be clearly identifiable
- **Efficient**: Minimize overhead while maintaining clarity
- **Robust**: Handle edge cases (empty strings, special characters)
- **Self-describing**: Include metadata (length) to enable proper parsing
- **Delimiter choice**: Choose delimiters that won't conflict with data content

### 2. String Parsing Techniques
- **Delimiter-based**: Use special characters to separate data sections
- **Length-prefix**: Include size information to know exactly how much to read
- **State tracking**: Keep track of current position in parsing
- **Boundary detection**: Find clear markers between different data elements
- **Sequential processing**: Process data from left to right without backtracking

### 3. C++ Optimization Techniques
- **Memory pre-allocation**: Use `reserve()` to avoid multiple reallocations
- **Move semantics**: Use `move()` to transfer ownership efficiently
- **Const references**: Use `const auto&` to avoid unnecessary copies
- **Helper functions**: Extract common logic for better maintainability
- **Modern C++ features**: Leverage `size_t`, `constexpr` for better performance

### 4. Algorithm Design Patterns
- **Length-prefix encoding**: Fundamental pattern for variable-length data
- **State machine parsing**: Process data step by step with clear state transitions
- **Boundary-based parsing**: Use clear markers to separate data sections
- **Single-pass algorithms**: Process data in one traversal for efficiency

## Edge Cases Handled

1. **Empty strings**: Length 0 is correctly encoded and decoded (`""` → `"0#"`)
2. **Strings containing numbers**: Length prefix is clearly separated by '#'
3. **Strings containing '#'**: Length tells us exactly where string ends
4. **Single character strings**: Handled correctly with length 1
5. **Very long strings**: No size limitations in the algorithm
6. **Strings with special characters**: All UTF-8 characters are preserved
7. **Empty input list**: Returns empty string, decodes to empty list
8. **Single string input**: Works correctly with one element
9. **Strings starting with numbers**: Length prefix prevents confusion
10. **Mixed length strings**: Handles varying string lengths correctly

**Edge Case Examples**:
```
Input: [""] → Encode: "0#" → Decode: [""]
Input: ["#"] → Encode: "1##" → Decode: ["#"]
Input: ["123"] → Encode: "3#123" → Decode: ["123"]
Input: ["a#b"] → Encode: "3#a#b" → Decode: ["a#b"]
```

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
**Pros**: Clean syntax, automatic type conversion
**Cons**: Slightly more overhead due to stream operations

### Using Modern C++ Features (Functional Style)
```cpp
string encode(vector<string>& strs) {
    return accumulate(strs.begin(), strs.end(), string{},
        [](string acc, const string& str) {
            return acc + to_string(str.length()) + "#" + str;
        });
}
```
**Pros**: Functional programming style, concise
**Cons**: Less readable, potential performance overhead from lambda

### Using Manual String Building
```cpp
string encode(vector<string>& strs) {
    string result;
    for (const auto& str : strs) {
        result += to_string(str.length()) + "#" + str;
    }
    return result;
}
```
**Pros**: Simple, direct, good performance
**Cons**: Multiple string concatenations (can be optimized with reserve)

### Using Reserve Optimization
```cpp
string encode(vector<string>& strs) {
    string result;
    size_t totalSize = 0;
    for (const auto& str : strs) {
        totalSize += str.length() + to_string(str.length()).length() + 1;
    }
    result.reserve(totalSize);
    
    for (const auto& str : strs) {
        result += to_string(str.length()) + "#" + str;
    }
    return result;
}
```
**Pros**: Optimal memory usage, single allocation
**Cons**: Slightly more complex code

## Real-World Applications

1. **Network Protocols**: Encoding data for transmission over TCP/UDP
   - HTTP headers, message framing, protocol buffers
   - Binary protocols that need to embed string data

2. **File Formats**: Storing multiple strings in a single file
   - Configuration files, data serialization, backup formats
   - Custom file formats that need to store string collections

3. **Database Storage**: Efficiently storing string arrays
   - Serializing string arrays for database storage
   - Custom data types that need string collection support

4. **Message Queues**: Serializing string collections
   - RabbitMQ, Apache Kafka message serialization
   - Inter-service communication with string arrays

5. **Configuration Files**: Storing multiple configuration values
   - Application settings, environment variables
   - Multi-value configuration parameters

6. **Binary Data Formats**: Embedding strings in binary data
   - Custom binary protocols, file formats
   - Efficient storage of mixed data types

7. **Caching Systems**: Serializing cache keys and values
   - Redis, Memcached string array serialization
   - Distributed caching with string collections

## Related Problems

### String Encoding/Decoding
- **394. Decode String**: Nested string decoding with brackets `3[a2[c]]`
- **443. String Compression**: Compressing strings in-place `aabcccccaaa` → `a2b1c5a3`
- **271. Encode and Decode Strings**: This problem - length-prefix encoding

### String Manipulation & Parsing
- **68. Text Justification**: Formatting strings with specific constraints
- **151. Reverse Words in a String**: String manipulation and parsing
- **186. Reverse Words in a String II**: In-place string reversal
- **557. Reverse Words in a String III**: Reverse individual words

### String Processing Patterns
- **8. String to Integer (atoi)**: Parsing strings with state machines
- **65. Valid Number**: Complex string validation with multiple states
- **125. Valid Palindrome**: String processing with two pointers
- **344. Reverse String**: Basic string manipulation

### Advanced String Algorithms
- **28. Find the Index of the First Occurrence in a String**: String searching
- **459. Repeated Substring Pattern**: Pattern recognition in strings
- **647. Palindromic Substrings**: String analysis and counting

## Practice Recommendations

### Implementation Practice
1. **Implement without looking**: Try to solve from scratch first
2. **Handle edge cases**: Test with empty strings, special characters, numbers
3. **Optimize memory usage**: Use pre-allocation and move semantics
4. **Test thoroughly**: Verify with various input combinations
5. **Consider alternatives**: Think about other encoding schemes

### Testing Strategy
```cpp
// Test cases to verify
vector<string> testCases = {
    {},                    // Empty list
    {""},                  // Empty string
    {"a"},                 // Single character
    {"abc"},               // Single word
    {"a", "b", "c"},       // Multiple single chars
    {"hello", "world"},    // Multiple words
    {"123", "456"},        // Numbers
    {"#", ":", ";"},       // Special characters
    {"a#b", "c:d"},        // Mixed content
    {"", "a", "", "b"}     // Empty strings mixed
};
```

### Optimization Practice
1. **Memory pre-allocation**: Calculate total size before encoding
2. **Move semantics**: Use `move()` for string transfers
3. **Const correctness**: Use `const` references where possible
4. **Helper functions**: Extract common logic for reusability

## Key Takeaways

### Algorithm Design
- **Length-prefix encoding** is a fundamental technique for handling variable-length data
- **Delimiter-based parsing** provides clear boundaries between data sections
- **Self-describing data** includes metadata (length) to enable proper parsing
- **Single-pass algorithms** are efficient and avoid backtracking

### C++ Best Practices
- **Memory optimization** through pre-allocation can significantly improve performance
- **Edge case handling** is crucial for robust string manipulation algorithms
- **Modern C++ features** like move semantics can improve efficiency without changing algorithm complexity
- **Const correctness** and proper reference usage prevent unnecessary copies

### Problem-Solving Skills
- **Think about edge cases** early in the design process
- **Choose appropriate data structures** for the problem constraints
- **Consider multiple approaches** before settling on a solution
- **Test thoroughly** with various input scenarios

### Real-World Applications
- **Encoding/decoding** is fundamental to data serialization and network protocols
- **String manipulation** skills are essential for text processing and parsing
- **Memory management** optimization is crucial for performance-critical applications
- **Robust error handling** is necessary for production systems
