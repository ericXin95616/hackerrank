//
// Created by bochao on 12/24/20.
//

/*
 * Question: https://leetcode.com/problems/word-break-ii/
 */

#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <gtest/gtest.h>

using std::vector;
using std::string;
using std::unordered_set;

void findAllPossibleSentences(vector<string>& sentences, const vector<vector<bool>>& dp, int index, const string& s, string tmp) {
    for (int i = 0; i < dp.at(0).size(); ++i) {
        if(!dp.at(index).at(i))
            continue;
        string next_tmp;
        if(0 != i) {
            next_tmp = " " + s.substr(i, index - i) + tmp;
            findAllPossibleSentences(sentences, dp, i, s, next_tmp);
        } else {
            next_tmp = s.substr(i, index - i) + tmp;
            sentences.push_back(next_tmp);
        }
    }
}

/*
 * 
 */
vector<string> wordBreak(string s, vector<string>& wordDict) {
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(s.size() + 1, false));
    unordered_set<string> dict;
    for (auto& str: wordDict) {
        dict.insert(str);
    }

    // Base case
    dp.at(0).at(0) = true;
    for (int i = 1; i <= s.size() ; ++i) {
        for (int j = 0; j < i; ++j) {
            bool tmp = false;
            for (int k = 0; k <= s.size(); ++k) {
                tmp |= dp.at(j).at(k);
            }
            dp.at(i).at(j) = tmp && (dict.end() != dict.find(s.substr(j, i - j)));
        }
    }

    // backtracking to build the output
    vector<string> allPossibleSentences;
    findAllPossibleSentences(allPossibleSentences, dp, s.size(), s, "");
    return allPossibleSentences;
}

TEST (WordBreakIITest, StandardTest) {
    string s;
    vector<string> wordDict;
    vector<string> ans;

    s = "catsanddog";
    wordDict = {"cat", "cats", "and", "sand", "dog"};
    ans = {
            "cats and dog",
            "cat sand dog"
    };
    EXPECT_EQ(ans, wordBreak(s, wordDict));

    s = "pineapplepenapple";
    wordDict = {"apple", "pen", "applepen", "pine", "pineapple"};
    ans = {
            "pine apple pen apple",
            "pineapple pen apple",
            "pine applepen apple"
    };
    EXPECT_EQ(ans, wordBreak(s, wordDict));

    s = "catsandog";
    wordDict = {"cats", "dog", "sand", "and", "cat"};
    ans = {};
    EXPECT_EQ(ans, wordBreak(s, wordDict));
}

int main(int argc, char** argv) {
    // InitGoogleTest must be called before calling RUN_ALL_TESTS
    // You could use different command line arguments to specify different
    // behaviors for the testing framework
    ::testing::InitGoogleTest(&argc, argv);

    // RUN_ALL_TESTS must be called only once
    return RUN_ALL_TESTS();
}