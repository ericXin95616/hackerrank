//
// Created by bochao on 12/23/20.
//

/*
 * Question: https://leetcode.com/problems/split-array-largest-sum/
 */

#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <iostream>

using std::vector;

/*
 *
 */
int splitArray(vector<int>& nums, int m) {
    vector<vector<int>> dp(nums.size() + 1, vector<int>(m + 1, INT_MAX));
    vector<int> sub(nums.size() + 1, 0);
    for (int i = 0; i < nums.size(); ++i) {
       sub.at(i + 1) = sub.at(i) + nums.at(i);
    }
    // base case - not really need it, just for clarify
    dp.at(0).at(0) = 0;

    for (int i = 1; i <= nums.size(); ++i) {
        for (int j = 1; j <= m; ++j) {
            // check all valid k, find smallest largest subarray sum
            for (int k = 0; k < i; ++k) {
                int tmp = sub[i] - sub[k];
                int largest_sum = std::max(tmp, dp.at(k).at(j - 1));
                dp.at(i).at(j) = std::min(largest_sum, dp.at(i).at(j));
            }
        }
    }
    return dp.at(nums.size()).at(m);
}

int main() {
    vector<int> nums = {7,2,5,10,8};
    int m = 2;
    std::cout << splitArray(nums, m) << std::endl;
}