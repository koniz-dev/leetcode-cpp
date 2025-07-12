/**
 * Solution 1
 * @param a - Binary string
 * @param b - Binary string
 * @returns Binary string representing the sum of a and b
 */
export function addBinary(a: string, b: string): string {
    let result: string[] = [];
    let carry: number = 0;
    let i: number = a.length - 1;
    let j: number = b.length - 1;
    while (i >= 0 || j >= 0 || carry) {
        let total: number = carry;
        if (i >= 0) {
            total += parseInt(a[i]);
            i -= 1;
        }
        if (j >= 0) {
            total += parseInt(b[j]);
            j -= 1;
        }
        result.push((total % 2).toString());
        carry = Math.floor(total / 2);
    }
    return result.reverse().join('');
}

/**
 * Solution 2
 * @param a - Binary string
 * @param b - Binary string
 * @returns Binary string representing the sum of a and b
 */
function addBinary_v2(a: string, b: string): string {
    return (BigInt(`0b${a}`) + BigInt(`0b${b}`)).toString(2);
}
