#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// 这题一开始写萎了，试图把原图读到邻接表里。然而在原图里做就可以了。。
class Solution {
public:
    struct edge {
            int vtx;
            int wei;
    };
    int infinity = 1000000;
    
    int minCost(vector<vector<int>>& grid) {
        vector<vector<edge>> adjTable; 
        int m = grid.size(); // m rows
        int n = grid[0].size(); // n columns
        if (m == n && m == 1)
            return 0;
        int size = m * n;
        adjTable.resize(size);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int currnum = i * n + j;
                int currdir = grid[i][j];
                if (i == 0) {
                    if (j == 0) {
                        if (currdir == 1) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,0});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1}); 
                        } else if (currdir == 2) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1});  
                        } else if (currdir == 3) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,0});
                        } else {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            if (m > 1)    
                                adjTable[currnum].push_back({currnum+n,1});
                        }
                    } else if (j == n-1) {
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1}); 
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum-1,0});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,0});
                        } else {
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1});
                        }
                    } else {
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum+1,0});
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1}); 
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,0});
                            // cout << m << endl;
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1});                    
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,0}); 
                        } else {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            if (m > 1)
                                adjTable[currnum].push_back({currnum+n,1}); 
                        }
                    }
                } else if (i == m-1) {
                    if (j == 0) {
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum-n,1});
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,0});
                        } else if (currdir == 2) {
                            
                            adjTable[currnum].push_back({currnum-n,1});
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum-n,1});
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                        } else {
                            adjTable[currnum].push_back({currnum-n,0});
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                        }
                    } else if (j == n-1) {
                        // cout << "now:" << i << "," << j <<endl;
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,1});
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,0});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,1});
                        } else {
                            adjTable[currnum].push_back({currnum-n,0});
                            adjTable[currnum].push_back({currnum-1,1});
                        }
                    } else {
                        
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum+1,0});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,0});
                            adjTable[currnum].push_back({currnum-n,1});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                        } else {
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,0});
                        }
                    }
                } else {
                    if (j == 0) {
                        if (currdir == 1) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,0});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 2) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 3) {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,0});
                        } else {
                            if (n > 1)
                                adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum-n,0});
                            adjTable[currnum].push_back({currnum+n,1});
                        }
                    } else if (j == n-1) {
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum-1,0});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum+n,0});
                        } else {
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum-n,0});
                            adjTable[currnum].push_back({currnum+n,1});
                        }
                    } else {
                        if (currdir == 1) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum+1,0});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 2) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,0});
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        } else if (currdir == 3) {
                            adjTable[currnum].push_back({currnum-n,1});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum+n,0});
                        } else {
                            adjTable[currnum].push_back({currnum-n,0});
                            adjTable[currnum].push_back({currnum-1,1});
                            adjTable[currnum].push_back({currnum+1,1});
                            adjTable[currnum].push_back({currnum+n,1});
                        }
                    }
                }


                
            }
        }

        int start = 0;
        int end = m*n-1;
        vector<bool> inset;
        vector<int> label;
        for (int i = 0; i < m*n; i++) {
            inset.push_back(false);
            label.push_back(infinity);
        }
        label[start] = 0;

        vector<int> set;
        return dijkstra(start, end, inset, label, adjTable, set, size);
    }
    
    int dijkstra(int start, int end, vector<bool>& inset, vector<int>& label, const vector<vector<edge>>& adjTable, vector<int>& set, int size) {
        while (set.size() < size) {
            const vector<edge>& curradj = adjTable[start];
            for (int i = 0; i < curradj.size(); i++) {
                int vtx = curradj[i].vtx;
                int wei = curradj[i].wei;
                if (!inset[vtx] && wei + label[start] < label[vtx]) {
                    label[vtx] = wei + label[start];  
                }
            }
            int min = infinity;
            int minvtx = -1;
            for (int i = 0; i < size; i++) {
                if (!inset[i] && min > label[i]) {
                    min = label[i];
                    minvtx = i;             
                }
            }
            start = minvtx;
            inset[minvtx] = true;
            set.push_back(minvtx);
        }
        return label[end];
    }
};

 // dijkstra, 时间复杂度为O(V^2+E), 过不了最后一个节点

class Solution_real {
public:
    int dirx[5] = {0,1,-1,0,0};
    int diry[5] = {0,0,0,1,-1};
    int infinity = 1000000;
    
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(); // m rows
        int n = grid[0].size(); // n columns
        if (m == n && m == 1)
            return 0;
        vector<int> dist, vis; deque<int> d;
        for (int i = 0; i < m*n; i++) {
            dist.push_back(infinity);
            vis.push_back(false);
        }
        int start = 0; int end = n*m-1;
        d.push_back(start); vis[start] = true; dist[start] = 0;
        int curr = start;
        while (d.size() > 0) {
            int cx = curr % n, cy = curr / n;
            int dir = grid[cy][cx];
            for (int i = 1; i <= 4; i++) {
                int ax = cx+dirx[i], ay = cy+diry[i];
                if (cx+dirx[i] < 0 || cx+dirx[i] >= n || cy+diry[i] < 0 || cy+diry[i] >= m) { 
                    continue; 
                } else {
                    int aim = ay*n+ax;
                    if (!vis[aim]) {
                        if (i == dir && dist[aim] > dist[curr]) {
                            d.push_front(aim);
                            dist[aim] = dist[curr];
                        } else if (dist[aim] > dist[curr] + 1){
                            d.push_back(aim);
                            dist[aim] = dist[curr] + 1;
                        } else continue;
                    }
                }
            }
            curr = d.front();
            vis[curr] = true;
            d.pop_front();
        }
        return dist[m*n-1];
    }   
};
// 01BFS, 快，时间复杂度O(E+V)

int main () {
    Solution sol1;
    vector<vector<int>> grid1;
    vector<int> line1;
    line1.push_back(1);
    grid1.push_back(line1);
    cout << sol1.minCost(grid1);
    return 0;
}