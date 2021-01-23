#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
class Solution {
public:
    typedef vector<int> Edge;
    int find(int a, vector<int>& djset) {
        if (djset[a] < 0) {
            return a;
        } else {
            return djset[a] = find(djset[a], djset); // 路径压缩
        }
    }
    void setUnion(int a, int b, vector<int>& djset) {
        int ra = find(a, djset), rb = find(b, djset);
        int sizea = -djset[ra], sizeb = -djset[rb];
        if (sizea > sizeb) {
            djset[rb] = ra;
            djset[ra] = -(sizea+sizeb); // 灵巧求并（按大小）
        } else {
            djset[ra] = rb;
            djset[rb] = -(sizea+sizeb);
        }
        
    }
    friend bool operator>(Edge a, Edge b);

    int kruskal(int n, vector<vector<int>>& edges, vector<int>& djset) { // kruskal 算法，返回最小生成树大小
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        for (auto edge : edges) {
            pq.push(edge);
        }
        int numEdges;
        int totalLength;
        while (numEdges < n-1) {
            Edge curr = pq.top();
            pq.pop();
            int ru = find(curr[0], djset);
            int rv = find(curr[1], djset);
            if (ru != rv) {
                setUnion(ru,rv, djset);
                numEdges++;
                totalLength += curr[2];
            }
        }
        return totalLength;
    }
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<int> djset(n,-1); // 并查集
        cout << kruskal(n, edges, djset) << endl;

    }
};

bool operator>(Solution::Edge a, Solution::Edge b) {
    return (a[2] > b[2]);
}
using namespace std;
int main() {
    // 测一下unordered_map的功能，发现const 的unordered_map是不能用下标读取的，可能是这个下标没有overloaded以常量形式访问。。
    // unordered_map<string,string> foo;
    // foo.emplace("1","haha");
    // const string p = "ppp";
    // foo.emplace("ppp","pp");
    // const unordered_map<string,string> bar = foo;
    // // cout << bar[p] << endl;
    // cout << foo["1"] << endl;
    // vector<int> boo(3,3);
    // for (auto i : boo) {
    //     cout << i << endl;
    // }


    
    return 0;
}