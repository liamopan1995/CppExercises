class Solution {
public:
    bool isPalindrome(int x) {
        if( x<0 || x%10==0 && x!=0) return false;

        int reversedNum = 0; 

        while ( x>reversedNum ){
            reversedNum = reversedNum *10 + x%10;
            x /=10;
        }
        return x == reversedNum || x == reversedNum / 10;
    }
// Now, think about how the loop progresses:

// When we start, reversedNum is 0 and x is the original number.
// With each iteration of the loop, we chop off the last digit of x and append it to reversedNum.
// x becomes half of its size (number of digits wise) when we've moved half its digits to reversedNum.
// Let's illustrate with an example:

// Suppose x = 1221

// Start: x = 1221, reversedNum = 0
// After 1st iteration: x = 122, reversedNum = 1
// After 2nd iteration: x = 12, reversedNum = 12
// The loop stops here because x <= reversedNum. Notice how we've reversed exactly half of x.

// If x is odd, say x = 12321:

// Start: x = 12321, reversedNum = 0
// After 1st iteration: x = 1232, reversedNum = 1
// After 2nd iteration: x = 123, reversedNum = 12
// After 3rd iteration: x = 12, reversedNum = 123
// Again, the loop stops when x <= reversedNum. This time, we've reversed just over half of x because of the odd number of digits. But this is okay because when we compare x and reversedNum/10, we're effectively ignoring the middle digit of the palindrome.


    
};