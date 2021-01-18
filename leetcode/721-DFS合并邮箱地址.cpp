#include <iostream>
#include <vector>

using namespace std;

// 失败算法：O(size^2*len^2), len是vector<string>的长，size是vector<vector<string>>的长。。最后超时了。。
// 正确解法好像是存到graph里，再dfs，这也太骚了😅
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int size = accounts.size();
        vector<bool> vis(size, false);
        vector<vector<string>> newac;
        for (int i = 0; i < size; i++) {
            if (vis[i]) continue;
            vector<string> newcurr(1, accounts[i][0]);
            vector<string> oldcurr(1, accounts[i][0]);
            bool flag = false;
            while (newcurr != oldcurr || !flag) { // 不停地融合后面的accounts[j]，直到再没有可融的为止。每个节点至多访问一次（好像很优秀的样子
                if (flag) {
                    oldcurr = newcurr;
                } // 第一次进来，flag是false，后面都是true，用oldcurr暂存一下来达到目的：newcurr不变的时候就立刻跳出循环。
                for (int j = i; j < size; j++) {
                    if (vis[j]) continue;
                    if (isSame(newcurr, accounts[j])) {
                        vis[j] = true;
                        insertWithNoRepeat(newcurr, accounts[j]);                
                    }
                }
                sort(newcurr);
                flag = true;
            }
            newac.push_back(newcurr);
        }
        return newac;
    }

    bool isInside(const vector<string>& a, const string& s) {
        int size = a.size();
        for (int i = 1; i < size; i++) { // 0 is the name
            if (a[i] == s) return true;
        }
        return false;
    }
    void insertWithNoRepeat(vector<string>& t, const vector<string>& s) {
        int size = s.size();
        for (int k = 1; k < size; k++) {
            if (!isInside(t, s[k])) {
                t.push_back(s[k]);
            }
        }
        
    }
    void sort(vector<string>& a) {
        int size = a.size();
        string temp;
        for (int i = 1; i < size; i++) { // 0 is the name
            for (int j = i+1; j < size; j++) {
                if (a[i] > a[j]) {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }
    }
    bool isSame(const vector<string>& a, const vector<string>& b) {
        if (a[0] == b[0]) {
            if (a.size() == 1 || b.size() == 1)
                return true;
            for (int i = 1; i < a.size(); i++) {
                for (int j = 1; j < b.size(); j++) {
                    if (b[j] == a[i]) return true;
                }
            }
            return false;
        } else return false;
    }
};