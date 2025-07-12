function isValid(s) {
    const stack = [];
    const map = {')': '(', '}': '{', ']': '['};
    for (let c of s) {
        if (Object.values(map).includes(c)) {
            stack.push(c);
        } else if (map[c]) {
            if (stack.pop() !== map[c]) return false;
        }
    }
    return stack.length === 0;
}
