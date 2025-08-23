# Optimized.cpp File Checklist

## Before Creating optimized.cpp

- [ ] **main.cpp contains `class Solution`** - Only create optimized.cpp if user has a Solution class
- [ ] **Never modify main.cpp** - User's solution must remain untouched
- [ ] **Identify the most optimal approach** - Only include the best solution

## Comment Style Requirements

### Block Comment (Required)
- [ ] **Problem name and approach** in first line
- [ ] **Step-by-step approach** explanation
- [ ] **Time complexity** with brief explanation
- [ ] **Space complexity** with brief explanation
- [ ] **Use /* */ format** (not // comments)

### Inline Comments (Required)
- [ ] **Variable purpose** explained
- [ ] **Major algorithm steps** commented
- [ ] **Return values** explained
- [ ] **Edge cases** documented

### Code Structure
- [ ] **`using namespace std;`** included
- [ ] **Proper includes** for required headers
- [ ] **Consistent indentation** (4 spaces)
- [ ] **Clear variable names** with purpose

## Example Template

```cpp
/*
 * [Problem Name] - Optimized Solution using [Data Structure/Algorithm]
 * 
 * Approach:
 * - [Step 1 description]
 * - [Step 2 description]
 * - [Step 3 description]
 * 
 * Time Complexity: O(x) - [brief explanation]
 * Space Complexity: O(y) - [brief explanation]
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
```

## Quality Checks

- [ ] **Comments are informative** not redundant
- [ ] **Complexity analysis is accurate**
- [ ] **Code is the most optimal** solution
- [ ] **No brute force** or suboptimal approaches
- [ ] **Consistent with existing** optimized.cpp files

## File Location

- [ ] **Place in correct directory**: `src/[Problem Number]. [Problem Name]/optimized.cpp`
- [ ] **README.md created** in same directory
- [ ] **Documentation updated** if new concepts found
