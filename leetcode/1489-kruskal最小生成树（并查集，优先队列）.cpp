#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
// 没用优先队列反而过了，我麻了 
class Solution_real {
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

    void reloadHeap(vector<int>& djset) {
        for (auto& x : djset) {
            x = -1;
        }
    }

    int kruskalCore(int n, vector<vector<int>>& edges, vector<int>& djset, int currNumEdges, int probIndex, bool& isAllConnected) { // kruskal 算法，返回最小生成树大小. currNumEdges 是传进来的时候，图中已经有的边数
        // for (auto& x : edges) {
        //     cout << x[2] << ",";
        // }
        // cout << endl;
        int numEdges = currNumEdges;
        int totalLength = 0;

        int counter = 0;
        while (numEdges < n-1 && counter < edges.size()) {
            if (counter == probIndex) {
                counter++;
                continue;
            }
            Edge curr = edges[counter];
            counter++;
            int ru = find(curr[0], djset);
            int rv = find(curr[1], djset);
            if (ru != rv) {
                setUnion(ru, rv, djset);
                numEdges++;
                totalLength += curr[2];
            }           
        }
        isAllConnected = (numEdges == n-1);
        if (probIndex == 6) cout << totalLength;
        return totalLength;
    }
    int kruskal(int n, vector<vector<int>>& edges, vector<int>& djset) { // 正常接口
        reloadHeap(djset);
        bool nonsense = true;
        return kruskalCore(n, edges, djset, 0, -1 , nonsense);
    }
    int kruskalWithEdgeCut(int n, vector<vector<int>>& edges, vector<int>& djset, int aimEdgeInd, bool& isAllConnected) {
        reloadHeap(djset);
        Edge aimEdge = edges[aimEdgeInd];
        return kruskalCore(n, edges, djset, 0, aimEdgeInd, isAllConnected);
    }
    int kruskalWithEdgeKept(int n, vector<vector<int>>& edges, vector<int>& djset, int aimEdgeInd) { // 强行加上aimEdge这一边然后看最小生成树多大，如果比正常大小大就说明没有出现在任何最小生成树当中
        reloadHeap(djset);
        Edge aimEdge = edges[aimEdgeInd];
        setUnion(aimEdge[0], aimEdge[1], djset);
        bool nonsense = true;
        return aimEdge[2]+kruskalCore(n, edges, djset, 1, aimEdgeInd, nonsense);
    }
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<int> djset(n,-1); // 并查集
        
        vector<vector<int>> ans(2);
        for (int i = 0; i < edges.size(); i++) {
            edges[i].emplace_back(i); // 插入原顺序，便于输出
        }
        sort(edges.begin(), edges.end(), [](Edge left, Edge right) {
                return (left[2]) < (right[2]); 
            }
        ); // 在这里先排好序
        int len = kruskal(n, edges, djset);
        int counter = 0;
        for (auto& edge : edges) {
            bool isAllConnected = true;
            int currlen = kruskalWithEdgeCut(n, edges, djset, counter, isAllConnected);
            if (!isAllConnected || currlen > len) {
                cout << "critical:" << counter << endl;
                ans[0].emplace_back(edge[3]);
            } else {
                if (kruskalWithEdgeKept(n, edges, djset, counter) == len) {
                    cout << "non critical:" << counter << endl;
                    ans[1].emplace_back(edge[3]);
                }
            }
            counter++;
        }
        return ans;
    }
};
// 超时的优先队列
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
    void reloadHeap(vector<int>& djset) {
        for (auto& x : djset) {
            x = -1;
        }
    }
    int kruskalCore(int n, vector<vector<int>>& edges, vector<int>& djset, int currNumEdges, int probIndex) { // kruskal 算法，返回最小生成树大小. 最后一个参数是传进来的时候，图中已经有的边数
        auto cmp = [](Edge left, Edge right) { return (left[2]) > (right[2]); }; // lambda 表达式，重载优先队列的比较原则，实现小根堆
        priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);
        
        for (int i = 0; i < edges.size(); i++) {
            Edge& edge = edges[i];
            if (currNumEdges != 0 && i == probIndex) continue; 
            pq.push(edge);
        }
        int numEdges = currNumEdges;
        int totalLength = 0;

        while (numEdges < n-1) {
            Edge curr = pq.top();
            pq.pop();
            int ru = find(curr[0], djset);
            int rv = find(curr[1], djset);
            if (ru != rv) {
                setUnion(ru, rv, djset);
                numEdges++;
                totalLength += curr[2];
            }
        }
        return totalLength;
    }
    int kruskal(int n, vector<vector<int>>& edges, vector<int>& djset) { // 正常接口
        reloadHeap(djset);
        return kruskalCore(n, edges, djset, 0, -1);
    }
    int kruskalWithEdgeKept(int n, vector<vector<int>>& edges, vector<int>& djset, int aimEdgeInd) { // 强行加上aimEdge这一边然后看最小生成树多大，如果比正常大小大就说明没有出现在任何最小生成树当中
        reloadHeap(djset);
        Edge aimEdge = edges[aimEdgeInd];
        setUnion(aimEdge[0], aimEdge[1], djset);
        return aimEdge[2]+kruskalCore(n, edges, djset, 1, aimEdgeInd);
    }
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<int> djset(n,-1); // 并查集
        int len = kruskal(n, edges, djset);
        vector<vector<int>> ans(2);
        int infinity = 10000000;
        int counter = 0;
        for (auto& edge : edges) {
            int tmpwei = edge[2];
            edge[2] = infinity; // 去掉这一边
            int currlen = kruskal(n, edges, djset);
            if (currlen > len) {
                ans[0].emplace_back(counter);
                edge[2] = tmpwei;
            } else {
                edge[2] = tmpwei;
                if (kruskalWithEdgeKept(n, edges, djset, counter) == len) {
                    ans[1].emplace_back(counter);
                }
            }
            counter++;
        }
        return ans;
    }
};