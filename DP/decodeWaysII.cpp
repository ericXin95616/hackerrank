//
// Created by bochao on 12/20/20.
//

/*
 * Question: https://leetcode.com/problems/decode-ways-ii/
 * level: hard
 */
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>

using std::string;

/*
 * Don't really like this question because there are
 * too many subcases that you need to pay attention to.
 *
 * For brevity, we use F to denote function numDecoding.
 * Base situation is the same as decodeWays:
 * IF S[0] == '0', F(S) = 0;
 * IF S[0-1] <= 26, F(S) = F(S - 1) + F(S - 2);
 * IF S[0-1] > 26, F(S) = F(S - 1);
 *
 * We need to add some cases to adapt to the newly emerged '*'.
 * IF S[0] == '*' && S[1] == '*',
 *      F(S) = 9F(S - 1) + 15 F(S - 2);
 *      => 9F(S - 1): S[0] | S[1], and S[0] has 9 possibility
 *      => 15F(S - 2): | S[0]S[1] |, S[0] and S[1] have 15 combinations within 26
 * IF S[0] == '*' && S[1] != '*',
 *      IF S[1] > 6, F(S) = 9F(S - 1) + F(S - 2);
 *      => S[0] have to be '1' to combine with S[1];
 *      IF S[1] <= 6, F(S) = 9F(S - 1) + 2F(S - 2);
 *      => S[0] have to be '1' or '2' to combine with S[2];
 * IF S[0] != '*' && S[1] == '*',
 *      IF S[0] == 1, F(S) = F(S - 1) + 9F(S - 2);
 *      IF S[0] == 2, F(S) = F(S - 1) + 6F(S - 2);
 *      IF S[0] > 2, F(S) = F(S - 1);
 *
 * Possible Improvement: only keep track of the last two values => Save space
 */
int numDecoding(string s) {
    // edge case - cannot combine 0 with previous character, 0 way to decode the string
    char zero = '0';
    char random = '*';
    int pos = s.find(zero);
    while(pos != std::string::npos) {
        // '0' is the first char
        if(0 == pos)
            return 0;
        // previous character is not '*' and previous character > 2 or previous character < 1
        if((s.at(pos - 1) != random) && (s.at(pos - 1) - zero > 2 || s.at(pos - 1) - zero < 1))
            return 0;
        pos = s.find(zero, pos + 1);
    }

    // use vector to store answers to the subproblems
    // so that we don't have to go through repeated computation
    std::vector<int> vec(s.size() + 1, 0);
    int mod_base = int(pow(10, 9)) + 7; // mod base is 10^9 + 7

    // find base case
    vec.at(0) = 1;
    const char last_char = s.back();
    switch (last_char) {
        case '*':
            vec.at(1) = 9;
            break;
        case '0':
            vec.at(1) = 0;
            break;
        default:
            vec.at(1) = 1;
    }

    int index = 2;
    for (std::string::const_reverse_iterator rit = s.rbegin() + 1; rit != s.rend(); ++rit) {
        const char first_char = *rit, second_char = *(rit - 1);
        const int first_num = first_char - zero, second_num = second_char - zero;

        if(first_char == zero) {
            vec.at(index) = 0;
            ++index;
            continue;
        }
        // check if first and second character have '*'
        if(first_char == random) {
            vec.at(index) = 9 * vec.at(index - 1);
            if(second_char == random) {
                // S[0] == '*' && S[1] == '*', 15 combinations within 26
                vec.at(index) += 15 * vec.at(index - 2);
            } else if(second_num > 6) {
                // S[0] == '*' && S[1] > '6', only S[0] == '1' can be combined
                vec.at(index) += vec.at(index - 2);
            } else if(second_num <= 6){
                // S[0] == '*' && S[1] <= '6', S[0] == '1' or '2' can be combined
                vec.at(index) += 2 * vec.at(index - 2);
            }
        } else if(second_char == random) {
            // S[0] != '*' && S[1] == '*'
            vec.at(index) = vec.at(index - 1);
            if(first_num == 1) {
                // S[0] == 1, 9 combinations with S[1]
                vec.at(index) += 9 * vec.at(index - 2);
            } else if(first_num == 2) {
                // S[0] == 2, 6 combinations with S[1]
                vec.at(index) += 6 * vec.at(index - 2);
            }
            // S[0] > 2, no way to combine S[0] and S[1], no need to add F(S-2)
        } else if(first_num > 2) {
            // normal case from here, code copyed from decodeWays.cpp
            vec.at(index) = vec.at(index-1);
        } else if(1 == first_num) {
            vec.at(index) = vec.at(index - 1) + vec.at(index - 2);
        } else if(2 == first_num) {
            // check next character to see if we could combine it with 2
            vec.at(index) = (second_num < 7) ? vec.at(index - 1) + vec.at(index - 2) : vec.at(index - 1);
        }

        vec.at(index) = vec.at(index) % mod_base;
        ++index;
    }
    return vec.at(s.size());
}

int main(){
    string input;
    input = "*0**0";
    assert(36 == numDecoding(input));
}
