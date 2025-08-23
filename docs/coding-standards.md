# C++ Coding Standards

## Comment Style for optimized.cpp Files

### Block Comment Template
All `optimized.cpp` files should use this professional comment style:

```cpp
/*
 * [Problem Name] - Optimized Solution using [Data Structure/Algorithm]
 * 
 * Approach:
 * - [Step 1 description]
 * - [Step 2 description]
 * - [Step 3 description]
 * - [Continue for all steps]
 * 
 * Time Complexity: O(x) - [brief explanation]
 * Space Complexity: O(y) - [brief explanation]
 */
```

### Inline Comments
- Add comments for variable declarations explaining their purpose
- Comment each major step in the algorithm
- Explain return values and edge cases

### Example Implementation
```cpp
#include <vector>
#include <[required_headers]>
using namespace std;

class Solution {
public:
    /*
     * [Problem Name] - Optimized Solution using [Data Structure/Algorithm]
     * 
     * Approach:
     * - [Detailed step-by-step explanation]
     * - [Continue for all steps]
     * 
     * Time Complexity: O(x) - [explanation]
     * Space Complexity: O(y) - [explanation]
     */
    [return_type] [function_name]([parameters]) {
        [data_structure] [variable_name]; // Purpose of variable
        
        for ([loop_condition]) {
            // Explain what this step does
            if ([condition]) {
                return [value];  // Explain return value
            }
            
            // Explain next step
            [operation];
        }
        
        return [default_value];  // Explain default return
    }
};
```

## Key Principles

1. **Always include `using namespace std;`** for consistency
2. **Use block comments** for function-level documentation
3. **Use inline comments** for important steps
4. **Explain complexity** with brief reasoning
5. **Keep comments concise but informative**
6. **Use consistent formatting** across all files

## File Structure Rules

- **main.cpp**: User's personal solution - NEVER modify
- **optimized.cpp**: Most efficient solution with professional comments
- **README.md**: Comprehensive documentation with all approaches

## Content Guidelines

- Include practical examples and usage patterns
- Cross-reference between related concepts
- Add new C++ concepts when they appear in solutions
- Provide clear explanations with code snippets
- Organize information by categories
