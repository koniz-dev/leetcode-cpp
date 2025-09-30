# [271. Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/)

## Problem Statement
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

**Key Challenge**: Handle strings that may contain any characters, including delimiters, numbers, and special characters.

### Examples
```
Input: strs = ["neet", "code", "love", "you"]
Output: ["neet", "code", "love", "you"]

Input: strs = ["we", "say", ":", "yes"]
Output: ["we", "say", ":", "yes"]
```

### Constraints
- `0 <= strs.length < 100`
- `0 <= strs[i].length < 200`
- `strs[i] contains only UTF-8 characters`

## Solution Approaches

### Approach 1: Length-Prefix Encoding (Optimal) ⭐
**Time Complexity:** O(n) where n is total characters in all strings  
**Space Complexity:** O(1) excluding input/output

Use format `"length#string"` for each string. The length prefix tells us exactly how many characters to read, and the '#' delimiter clearly separates length from content.

**Encode Process:**
1. For each string, prepend its length followed by '#'
2. Concatenate all encoded strings
3. Example: `["abc", "def"]` → `"3#abc3#def"`

**Decode Process:**
1. Find the '#' delimiter to separate length from content
2. Extract the length (number before '#')
3. Extract exactly that many characters after '#'
4. Move to next encoded string

**Why This Works:**
- Length prefix tells us exactly how many characters to read
- '#' delimiter clearly separates length from content
- Handles any characters in strings (including numbers and '#')
- No ambiguity in parsing - each string boundary is clearly defined

**Example Walkthrough:**
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
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

Use escape sequences for special characters (e.g., `\:` for colon, `\#` for hash).

```cpp
class Codec {
public:
    string encode(vector<string>& strs) {
        string result;
        for (const string& str : strs) {
            for (char c : str) {
                if (c == '\\') {
                    result += "\\\\";  // Escape backslash
                } else if (c == ':') {
                    result += "\\:";   // Escape colon
                } else {
                    result += c;
                }
            }
            result += ":;";  // Delimiter between strings
        }
        return result;
    }
    
    vector<string> decode(string s) {
        vector<string> result;
        string current;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '\\' && i + 1 < s.length()) {
                // Handle escape sequence
                if (s[i + 1] == '\\') {
                    current += '\\';
                    i++; // Skip next backslash
                } else if (s[i + 1] == ':') {
                    current += ':';
                    i++; // Skip next colon
                }
            } else if (s[i] == ':' && i + 1 < s.length() && s[i + 1] == ';') {
                // End of string delimiter
                result.push_back(current);
                current.clear();
                i++; // Skip semicolon
            } else {
                current += s[i];
            }
        }
        
        return result;
    }
};
```

**Limitations:**
- More complex to implement and debug
- Requires defining comprehensive escape sequences
- Less efficient for strings with many special characters

### Approach 3: Base64 Encoding
**Time Complexity:** O(n)  
**Space Complexity:** O(1)

Convert strings to base64 format, separate with delimiters.

```cpp
#include <sstream>
#include <iomanip>

class Codec {
private:
    string base64_encode(const string& input) {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        string result;
        int val = 0, valb = -6;
        
        for (unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                result.push_back(chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) result.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (result.size() % 4) result.push_back('=');
        return result;
    }
    
    string base64_decode(const string& input) {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        string result;
        int val = 0, valb = -8;
        
        for (char c : input) {
            if (chars.find(c) == string::npos) break;
            val = (val << 6) + chars.find(c);
            valb += 6;
            if (valb >= 0) {
                result.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }
        return result;
    }
    
public:
    string encode(vector<string>& strs) {
        string result;
        for (const string& str : strs) {
            result += base64_encode(str) + "|";
        }
        return result;
    }
    
    vector<string> decode(string s) {
        vector<string> result;
        stringstream ss(s);
        string token;
        
        while (getline(ss, token, '|')) {
            if (!token.empty()) {
                result.push_back(base64_decode(token));
            }
        }
        
        return result;
    }
};
```

**Limitations:**
- Increases string size by ~33%
- More complex encoding/decoding process
- Overkill for this problem

## C++ Concepts Used

### String Manipulation
- **Length-prefix encoding**: Prepend each string with its length for unambiguous parsing
- **Delimiter-based parsing**: Use special character ('#') to separate length from content
- **Substring extraction**: Parse encoded data by extracting specific portions
- **String concatenation**: Efficiently combine multiple encoded strings

### Parsing Algorithms
- **State machine parsing**: Track position and parse length then content sequentially
- **Boundary detection**: Find delimiters to separate different parts of encoded data
- **Sequential processing**: Process encoded data from left to right without backtracking

### C++ Features
- **`string`**: Text manipulation and processing
- **`vector<string>`**: Dynamic array of strings
- **`to_string()`**: Convert integer to string
- **`substr()`**: Extract substring from string
- **`stoi()`**: Convert string to integer

## Edge Cases Handled

1. **Empty strings**: Length 0 is correctly encoded and decoded (`""` → `"0#"`)
2. **Strings containing numbers**: Length prefix is clearly separated by '#'
3. **Strings containing '#'**: Length tells us exactly where string ends
4. **Empty input list**: Returns empty string, decodes to empty list
5. **Single string input**: Works correctly with one element

**Edge Case Examples:**
```
Input: [""] → Encode: "0#" → Decode: [""]
Input: ["#"] → Encode: "1##" → Decode: ["#"]
Input: ["123"] → Encode: "3#123" → Decode: ["123"]
Input: ["a#b"] → Encode: "3#a#b" → Decode: ["a#b"]
```

## Related Problems
- [394. Decode String](https://leetcode.com/problems/decode-string/) - Nested string decoding with brackets
- [443. String Compression](https://leetcode.com/problems/string-compression/) - Compressing strings in-place
- [151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) - String manipulation and parsing
- [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/) - Parsing strings with state machines

## Practice Tips
1. **Think about edge cases** early in the design process
2. **Choose appropriate delimiters** that won't conflict with data content
3. **Consider memory optimization** through pre-allocation
4. **Test thoroughly** with various input combinations
5. **Understand the encoding format** before implementing
