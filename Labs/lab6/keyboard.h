#include <string>
/*
One day, you decided to design a new keyboard, and you put all of the keys in one row.
Instead of using both hands, you decided to just use one finger at a time.
You place the keys such that it takes you one second to get from one key to each of its direct neighbors.
Given the layout of your keyboard (of 26 letters), calculate how long it will take to type a given word.
You start with your finger is at index 0.
To type a character, you have to move your finger to the index of the desired character.
The time taken to move your finger from index i to index j is |i - j| seconds.
Example 1:
Input: keyboard = "abcdefghijklmnopqrstuvwxyz", word = "cba"
Output: 4
Explanation: The index moves from 0 to 2 to write 'c' then to 1 to write 'b' then to 0 again to write 'a'.
Total time = 2 + 1 + 1 = 4.
Example 2:
Input: keyboard = "pqrstuvwxyzabcdefghijklmno", word = "csci"
Output: 39
 
Constraints:
keyboard.length == 26
keyboard contains each English lowercase letter exactly once in some order.
word[i] is an English lowercase letter.
*/

int calculateTime(std::string keyboard, std::string word);