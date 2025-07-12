class Solution {
    func isValid(_ s: String) -> Bool {
        var stack: [Character] = []
        for c in s {
            if c == "(" || c == "{" || c == "[" {
                stack.append(c)
            } else {
                if stack.isEmpty { return false }
                let top = stack.removeLast()
                if (c == ")" && top != "(") ||
                   (c == "}" && top != "{") ||
                   (c == "]" && top != "[") {
                    return false
                }
            }
        }
        return stack.isEmpty
    }
}
