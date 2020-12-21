//
// Created by bochao on 12/20/20.
//

/*
 * Question: https://leetcode.com/problems/decode-ways/
 * level: medium
 */

#include <vector>
#include <string>
#include <cassert>

using std::string;

/*
 * recursion version
 * Fail - Time Limit Exceeded for input "111111111111111111111111111111111111111111111"
 */
int numDecodingsRecursion(string s) {
    // s is guaranteed to not be empty
    if(s.empty())
        return 1;

    char first_char = s.at(0);
    int first_num = first_char - '0';

    if(0 == first_num)
        return 0;
    int pick_first_case = numDecodingsRecursion(s.substr(1));
    if(1 == first_num)
        return (1 == s.size()) ? pick_first_case : pick_first_case + numDecodingsRecursion(s.substr(2));
    if(2 == first_num) {
        // check if there is a second char
        if(1 == s.size())
            return pick_first_case;
        int second_num  = s.at(1) - '0';
        // 26 is the upper limit
        return (second_num < 7) ? pick_first_case + numDecodingsRecursion(s.substr(2)) : pick_first_case;
    }
    return pick_first_case;
}

/*
 * DP version - Bottom-up with Tabulation
 * We use S to represent the input.
 * S - 1 means the substring without the first character.
 * S[0] is the first character.
 * For example: S == "123456", S - 1 == "23456", S[0] = '1'.
 * We could easily find that:
 * IF S[0-1] > '26', numDecoding(S) = numDecoding(S - 1)
 *  => because it cannot be combined with second character;
 * IF S[0-1] <= "26", numDecoding(S) = numDecoding(S - 1) + numDecoding(S - 2)
 *  => because now it can be combined;
 * IF S[0] == '0', no way to decode this string.
 * We could use this base logic to fill our tabulation bottom-up so that we avoid
 * repeated computation.
 */
int numDecoding(string s) {
    // edge case - cannot combine 0 with previous character, 0 way to decode the string
    char zero = '0';
    int pos = s.find(zero);
    while(pos != std::string::npos) {
        // '0' is the first char or previous character > 2 or previous character < 1
        if(0 == pos || s.at(pos - 1) - zero > 2 || s.at(pos - 1) - zero < 1)
            return 0;
        pos = s.find(zero, pos + 1);
    }

    // use vector to store answers to the subproblems
    // so that we don't have to go through repeated computation
    std::vector<int> vec(s.size() + 1, 0);

    // find base case
    vec.at(0) = 1;
    const char last_char = s.back();
    vec.at(1) = last_char != zero;
    int index = 2;
    for (std::string::const_reverse_iterator rit = s.rbegin() + 1; rit != s.rend(); ++rit) {
        // edge case - trailing 0
        if(2 == index && 0 == vec.at(1)) {
            vec.at(index) = 1;
            ++index;
            continue;
        }

        const char c = *rit;
        int first_num = c - zero;
        if(first_num > 2) {
            vec.at(index) = vec.at(index-1);
        } else if(1 == first_num) {
            vec.at(index) = vec.at(index - 1) + vec.at(index - 2);
        } else if(2 == first_num) {
            // check next character to see if we could combine it with 2
            const char next_char = *(rit - 1);
            int second_num = next_char - zero;
            vec.at(index) = (second_num < 7) ? vec.at(index - 1) + vec.at(index - 2) : vec.at(index - 1);
        } else {
            // first num is 0, no way to decode this substring
            // this branch is redundant, but it clarifies our logic process
            vec.at(index) = 0;
        }
        ++index;
    }
    return vec.at(s.size());
}

int main(){
    string input;
    //input = "111111111111111111111111111111111111111111111";
    //assert(numDecoding(input) == numDecodingsRecursion(input));
    input = "1";
    assert(numDecoding(input) == numDecodingsRecursion(input));
    input = "0";
    assert(numDecoding(input) == numDecodingsRecursion(input));
}