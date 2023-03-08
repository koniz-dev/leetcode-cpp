/**
 * Solution 1
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function(a, b) {
    let result = []
    let carry = 0
    let i = a.length - 1
    let j = b.length - 1

    while (i >= 0 || j >= 0 || carry) {
        let total = carry

        if (i >= 0) {
            total += parseInt(a[i])
            i -= 1
        }

        if (j >= 0) {
            total += parseInt(b[j])
            j -= 1
        }

        result.push((total % 2).toString())
        carry = Math.floor(total / 2)
    }

    return result.reverse().join('')
};

/**
 * Solution 2
 * @param {string} a
 * @param {string} b
 * @return {string}
 */
var addBinary = function(a, b) {
    return (BigInt(`0b${a}`) + BigInt(`0b${b}`)).toString(2);
};