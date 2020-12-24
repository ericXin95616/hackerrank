//
// Created by bochao on 12/21/20.
//

/*
 * Question: https://leetcode.com/problems/word-break/
 * level: medium
 */

#include <string>
#include <vector>
#include <cassert>
#include <unordered_set>

using std::string;
using std::vector;
using std::unordered_set;

/*
 * Recursion version
 * Fail - Time limit exceeded
 */
bool wordBreakRecursion(const string &s, const vector<string>& wordDict, size_t pos, vector<size_t> appear_pos) {
    if(pos == s.length())
        return true;
    for (size_t i = 0; i < appear_pos.size(); ++i) {
        if(pos != appear_pos.at(i))
            continue;
        size_t next_pos = pos + wordDict.at(i).length();
        // update appear_pos
        vector<size_t> new_appear_pos = appear_pos;
        for (size_t j = 0; j < new_appear_pos.size(); ++j) {
            if(new_appear_pos.at(j) < next_pos){
                new_appear_pos.at(j) = s.find(wordDict.at(j), next_pos);
            }
        }
        if(wordBreakRecursion(s, wordDict, next_pos, new_appear_pos))
            return true;
    }
    return false;
}

bool wordBreak_r(string s, vector<string>& wordDict) {
    vector<size_t> appear_pos(wordDict.size(), 0);

    // initialize the appear_pos vector
    for (size_t i = 0; i < wordDict.size(); ++i) {
        appear_pos.at(i) = s.find(wordDict.at(i));
    }

    size_t pos = 0;
    return wordBreakRecursion(s, wordDict, pos, appear_pos);
}

/*
 * Recursion with memorization
 */
bool wordBreakRecurse(const string& s, const vector<string>& wordDict, int init_x, int init_y, vector<vector<int>>& board) {
    if(init_y == s.length() - 1)
        return true;

    for (int i = 0; i < wordDict.size(); ++i) {
        int pos = s.find(wordDict.at(i), init_y + 1);
        if (pos != init_y + 1)
            continue;
        // pos == init_y + 1
        int next_y = init_y + wordDict.at(i).length();
        int next_x = init_y + 1;

        if(!board.at(next_x).at(next_y)) {
            continue;
        } else {
            board.at(next_x).at(next_y) = true;
        }

        if(wordBreakRecurse(s, wordDict, next_x, next_y, board)){
            return true;
        }
    }

    board.at(init_y + 1) = vector<int>(s.size(), false);
    return false;
}

bool wordBreak_m(string s, vector<string>& wordDict) {
    // initialize the board
    vector<vector<int>> board;
    board.resize(s.size(), vector<int>(s.size(), -1));

    int init_x = 0, init_y = -1;
    return wordBreakRecurse(s, wordDict, init_x, init_y, board);
}

/*
 * DP version - Solution
 */
bool wordBreak(string s, vector<string>& wordDict) {
    vector<int> dp(s.size()+1, false);
    unordered_set<string> dict;
    for (const string& str: wordDict) {
        dict.insert(str);
    }

    // base case
    dp.at(0) = true;
    for (int i = 1; i < dp.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            // if F(S[0-j]) is true and dict contains word S[j-(i - 1)], we could say F(S[0-i]) is true
            if(dp.at(j) && dict.end() != dict.find(s.substr(j,i-j))) {
                dp.at(i) = true;
                break;
            }
        }
    }

    return dp.back();
}

int main() {
    //string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    //vector<string> wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    //string s = "leetcode";
    //vector<string> wordDict = {"leet", "code"};
    string s = "cars";
    vector<string> wordDict = {"car", "ca", "rs"};
    assert(wordBreak(s, wordDict));
}