fun isValid(s: String): Boolean {
    val stack = ArrayDeque<Char>()
    for (c in s) {
        when (c) {
            '(', '{', '[' -> stack.addLast(c)
            ')', '}', ']' -> {
                if (stack.isEmpty()) return false
                val top = stack.removeLast()
                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    return false
                }
            }
        }
    }
    return stack.isEmpty()
}
