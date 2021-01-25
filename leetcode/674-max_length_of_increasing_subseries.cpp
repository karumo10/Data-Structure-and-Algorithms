#include <vector>
using namespace std;

// O(N) online算法
// 比起最大子序列和，这个简单多了
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int counter = 1;
        int maxLen = 1;
        int size = nums.size();
        if (size == 0) return 0;
        for (int i = 0; i < size-1; i++) {
            if (nums[i+1] > nums[i]) {
                counter++;
            } else {
                counter = 1;
            }
            if (counter > maxLen) {maxLen = counter;}
        }
        return maxLen;
    }
};