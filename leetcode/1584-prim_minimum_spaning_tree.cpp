#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
// 感觉prim和dijkstra一毛一样，都是每次找出dist最小的点，加进inset集合里，然后下一次迭代的时候，以上一次迭代找出的dist最小的那个点为基础，更新与它相邻且不在inset里的点，一步一步扩大，直到整张图都被吃进就ok了
// 唯一不同的是prim的dist指的是某个点到已经生成的spanning tree（也就是当前的inset集合）的最短距离，而dijkstra的dist是某个点到起始点，只经过inset内的点，的距离。所以前者的松弛判断条件式是dist(v)>weight(u,v) 而后者是 dist(v)>weight(u,v)+dist(v)
// 所以同样，这个方法也不适用于负权图
class Solution {
public:
    int infinity = 10000000;
    int minCostConnectPoints(vector<vector<int>>& points) {
        int size = points.size();
        vector<vector<int>> adjMatrix(size);
        for (int i = 0; i < size; i++) {
            adjMatrix[i].resize(size);
            for (int j = 0; j < size; j++) {
                int xi = points[i][0], yi = points[i][1], xj = points[j][0], yj = points[j][1];
                adjMatrix[i][j] = abs(xi - xj) + abs(yi - yj);
            }
        } //邻接矩阵
        
        vector<int> inset;
        vector<bool> vis(size, false);
        vector<int> dist(size, infinity);
        inset.emplace_back(0); int total = 0;
        dist[0] = 0; // 到已知最小生成树的最短距离
        vis[0] = true;
        return prim(0, inset, dist, vis, adjMatrix);
    }
    int prim(int start, vector<int>& inset, vector<int>& dist, vector<bool>& vis, vector<vector<int>>& adjMatrix) {
        int curr = start;
        int size = adjMatrix.size();
        int total = 0;
        while (inset.size() < size) { // prim算法
            vector<int>& weighs = adjMatrix[curr]; // 引用赋值省空间
            for (int i = 0; i < weighs.size(); i++) {
                if (vis[i]) continue;
                if (weighs[i] < dist[i]) {
                    dist[i] = weighs[i];
                }
            }
            int minDist = infinity;
            int minVtx = -1;
            for (int i = 0; i < size; i++) {
                if (vis[i]) continue;
                if (dist[i] < minDist) {
                    minDist = dist[i];
                    minVtx = i;
                }
            }
            vis[minVtx] = true;
            dist[minVtx] = 0;
            curr = minVtx;
            inset.emplace_back(minVtx);
            total += minDist;
        }
        return total;
    }
};

int main() {
    return 0;
}