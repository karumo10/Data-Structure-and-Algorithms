#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static int infinity = 100000;


struct nextPoint {
    int vtx; // vertex
    int wei; // weight
};

static vector<int> set; // the set S_k
static vector<bool> inset; // whether the node is in set S_k (in the dijkstra set)
static vector<int> label; // label value
static vector<vector<nextPoint>> adj; // adjacent table

int readInGraph() {
    int nv, ne; // number of vertices/edges
    cin >> nv >> ne; 
    inset.resize(nv);
    label.resize(nv);
    adj.resize(nv);
    for (int i = 0; i < nv; i++) {
        inset[i] = false;
        label[i] = infinity;
    }
    for (int i = 0; i < ne; i++) {
        int start, end, weight; // input, two vertices (start to end)
        cin >> start >> end >> weight;
        adj[start].push_back({end,weight});
    }
    return nv;
}

void dijkstra(int source, int nv) {
    label[source] = 0;
    inset[source] = true;
    set.push_back(source);
    for (int k = 0; k < nv; k++) { // do k times updates (or use while there is still "infinity", or use priorty queue)
        int setSize = set.size();
        int i = set[setSize-1]; // take the last-added vtx
        // cout << "Now traverse to " << i << " (in set S_" << k <<endl;
        int adjSize = adj[i].size();
        for (int j = 0; j < adjSize; j++) { // traversal all the adj vtx and update them
            int currVtx = adj[i][j].vtx;
            int currWei = adj[i][j].wei;
            if (currWei + label[i] < label[currVtx]) {
                // cout << currVtx << "'s label is updated to " <<  currWei + label[i] << " from " << label[currVtx] << endl;
                label[currVtx] = currWei + label[i];
            }
        }    
        int minV = -1;
        int min = infinity; 
        for (int m = 0; m < nv; m++) {    
            if (!inset[m]) {
                // cout << m << " label is " << label[m] << endl;
                if (label[m] < min) {
                    min = label[m];
                    minV = m;
                }
            }
        }
        if (minV == -1) {
            return; // all the vertices are in set S!
        }
        set.push_back(minV);
        inset[minV] = true;
        // cout << minV <<" is added" << endl;
    }
}

void output(int nv) {
    for (int i = 0; i < nv; i++) {
        cout << "v" << i << ": " << label[i] << endl;
    }
}

int main() {
    int nv = readInGraph();
    dijkstra(0, nv);
    output(nv);
    return 0;
}


/*
易错点：
1.每一次更新dist的点，确实只是上一回合新加入set的点的邻接点
2.什么点能新加入set？dist最小的点。哪些里面找？所有不在set里的点里面找。
3.在所有点都加入set之前，如果遇见terminal（目标点），求出来的dist不是最终距离！不是最终距离！必须全部加入set之后，才能求dist


*/