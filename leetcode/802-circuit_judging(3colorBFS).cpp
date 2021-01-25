#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    enum Color {WHITE, GREY, BLACK};
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        
        vector<int> sol;
        int size = graph.size();
        vector<Color> vis;
        vector<int> isSol;
        for (int i = 0; i < size; i++) {
            vis.push_back(WHITE);
            isSol.push_back(-1); // -1:unknown
        } // initialize
        for (int i = 0; i < size; i++) {
            // reloadVisited(vis, size); // before every dfs, clear the visited array
            // 不需要！见line 58
            if (dfs(i,graph,vis,isSol)) {
                sol.push_back(i);
                isSol[i] = 1; //1:is a solution
            } else {
                isSol[i] = 0; // 0:not a solution!
            }
        }
        return sol;
    }
    // void reloadVisited(vector<Color>& vis, int size) {
    //     for (int i = 0; i < size; i++) {
    //         vis[i] = WHITE;
    //     }
    // }
    bool dfs(int s, const vector<vector<int>>& g, vector<Color>& vis, vector<int>& isSol) {
        vis[s] = GREY;
        vector<int> adj = g[s];
        int size = adj.size();
        if (size == 0) {
            vis[s] = BLACK;
            return true; // find the terminal
        }
        bool isSSafe = isSol[s] == -1 ? true : isSol[s]; // 直接返回当前记忆的值，避免重复调用
        for (int i = 0; i < size; i++) {
            if (isSol[adj[i]] == 0) {
                isSSafe = false;
                break;
            } // 子节点不安全，则比不安全
            if (vis[adj[i]] == WHITE) {
                isSSafe = isSSafe && dfs(adj[i], g, vis, isSol);
            } else if (vis[adj[i]] == GREY) {
                isSSafe = false;
                break;
            }
        }
        vis[s] = BLACK;
        isSol[s] = isSSafe; // 黑色的节点必然是已经知道safe/unsafe的节点，下次dfs的时候遇到他，只需要调用isSol当中的数据即可。
        return isSSafe;
    }
};

int main() {
    return 0;
}