interface IBracketMapping {
    [key: string]: string;
}

export function isValid(s: string): boolean {
    const stack: string[] = [];
    const mapping: IBracketMapping = {
        ')': '(',
        '}': '{',
        ']': '['
    };

    for (const char of s) {
        if (char in mapping) {
            const topElement = stack.pop();
            if (topElement !== mapping[char]) {
                return false;
            }
        } else {
            stack.push(char);
        }
    }

    return stack.length === 0;
}