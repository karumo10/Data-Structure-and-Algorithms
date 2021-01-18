#include <iostream>
#include <vector>

using namespace std;

static vector<bool> vis; // visited
static vector<vector<int>> adj; // adjacent table


void dfs(int start) {
    vis[start] = true;
    int curr = start;
    // cout << "Go into " << curr << endl;
    for (int i = 0; i < adj[curr].size(); i++) {
        if (!vis[adj[curr][i]]) {
            cout << curr << " " << adj[curr][i] << endl;
            vis[adj[curr][i]] = true;
            dfs(adj[curr][i]);
        }
        // cout << "Back to " << curr << endl;
    }
}

void readInGraph() {
    int nv, ne; // number of vertices/edges
    cin >> nv >> ne; 
    vis.resize(nv);
    adj.resize(nv);
    for (int i = 0; i < nv; i++) {
        vis[i] = false;
    }
    for (int i = 0; i < ne; i++) {
        int start, end; // input, two vertices (start to end)
        cin >> start >> end;
        adj[start].push_back(end);
    }    
}


int main() {
    readInGraph();
    cout << "Start output spanning tree..." << endl;
    dfs(0);
    return 0;
}