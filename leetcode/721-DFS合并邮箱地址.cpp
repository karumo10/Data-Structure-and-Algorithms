#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution_real {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, vector<string>> graph; // 用邮箱地址检索它的邻接表
        unordered_map<string, string> mail2usr; // (邮箱，用户名)
        vector<string> mails; // 存储首邮箱
        unordered_map<string, bool> vis; // 参观过的
        vector<vector<string>> ans; // 解
        for (auto& ac : accounts) {
            if (ac.size() <= 1) continue; // 没有邮箱
            mails.emplace_back(ac[1]);
            mail2usr.emplace(ac[1],ac[0]);
            // if (!isExist(graph, ac[1])) {
            //     graph.emplace(ac[1], vector<string>());
            // } 

            /*以普遍理性而论，如果是一个新的key被放进图里面，我们需要开辟一个新的节点给他放东西（line 20-22，line 28-30）对不对
            然而这是不必要的，直接graph接下标就能给你开辟船新的节点，stl，yyds！*/
            for (int i = 2; i < ac.size(); i++) { // 这样之后，同账户的点全部联通
                // 只要保证联通就好了，并不要连成完全图 这样可以O(N^2)变O(N)
                graph[ac[1]].emplace_back(ac[i]);
                // if (!isExist(graph, ac[i])) {
                //     graph.emplace(ac[i], vector<string>());
                // }
                graph[ac[i]].emplace_back(ac[1]);
                
            }
        }
        
        for (auto& mail : mails) {
            vector<string> curr;
            dfs(mail, graph, vis, curr);
            if (curr.empty()) continue; // 已经访问过，所以curr是空的
            string user = mail2usr[mail];
            integrate(user, curr);
            ans.emplace_back(curr);
        }
        return ans;
    }
    bool isExist(const unordered_map<string, vector<string>>& graph, const string& string) {
        return (graph.find(string) != graph.end());
    }
    void integrate(const string& user, vector<string>& vec) { 
        int s = vec.size();
        sort(vec.begin(), vec.end());
        vec.resize(s + 1);
        for (int i = s; i >= 1; i--) {
            vec[i] = vec[i-1];
        }
        vec[0] = user;
        
    }
    void dfs(const string& mail, unordered_map<string, vector<string>>& graph, unordered_map<string, bool>& vis, vector<string>& curr) {
        if (vis[mail]) return;
        vis[mail] = true;
        curr.emplace_back(mail);
        for (auto& linked : graph[mail]) {
            if (!vis[linked]) { // 虽然上面已经有剪枝了（line61），但是这样是不是可以降低栈空间利用率
                dfs(linked, graph, vis, curr);
            }
        }
    }
};























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