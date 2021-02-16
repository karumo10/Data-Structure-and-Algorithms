#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


// 算法来自《数据结构与算法分析：c语言描述》9.6.3 欧拉回路，那一篇对O(V+E)的算法一笔带过，此处完善。

struct Edge {
    int u;
    int v; // the connected vtx
    Edge(int u, int v) : u(u), v(v) {} // constructor
    bool operator==(const Edge& rhs) const {
        return (u == rhs.u && v == rhs.v);
    }
};

struct hash_fn { // cpp不支持对struct的hash，从而不支持对struct的unordered_map，此处自己写一个。（来自cppreference）
    std::size_t operator() (const Edge& edge) const {
        std::size_t h1 = std::hash<int>{}(edge.u);
        std::size_t h2 = std::hash<int>{}(edge.v);
        return h1 ^ (h2 << 1);
    }
};

struct PathList {
    PathList* next;
    int curr;
    PathList(PathList* nxt, int a) : next(nxt), curr(a) {}
}; // used to save the path by linked list


unordered_map<Edge, bool, hash_fn> vis;
vector<vector<int>> adj;
vector<int> fdeg; // free (out) degree of each vertex (will be cost by the creation of a circuit)


// 怎么选出新顶点？从上一轮的拼接点开始，（把上轮刚刚拼接进去的loop放在后面）遍历整个路径，找出遇到的第一个free degree不是0的点。
// 这样做是保证一个循环不变式：每次的路径当中，新顶点前面的点必然已经free degree归零了，这样子当新顶点的free degree为零（也就是找不出新degree）的时候，就可以说循环结束了。


void init(int nv, int ne) {
    adj.resize(nv);
    fdeg.resize(nv);
    for (int i = 0; i < nv; i++) {
        fdeg[i] = 0;
    }
}

int readInGraph() {
    int nv, ne; // number of vertices/edges
    cin >> nv >> ne; 
    init(nv, ne);
    for (int i = 0; i < ne; i++) {
        int start, end; // input, two vertices (start to end)
        cin >> start >> end;
        adj[start].push_back(end);
        adj[end].push_back(start);
        vis[{start, end}] = true; 
        vis[{end, start}] = true;
        fdeg[end]++;
        fdeg[start]++; // indirected graph
    }    
    return ne;
}



bool isPossible() {
    bool possible = true;
    for (auto deg : fdeg) {
        if (!(possible = (deg % 2 == 0) && possible)) break;
    }
    return possible;
}





void decreaseFdeg(int u, int v) {
    fdeg[u]--;
    fdeg[v]--;
}




void dfs(PathList* sourceAds, int now, bool& startBackTracking, PathList*& nowAds, PathList* originalNextAds) {
    int source = sourceAds->curr;
    
    for (auto& adjv : adj[now]) {
        bool& isExist = vis[{adjv, now}];
        cout << "The edge (" << adjv << "," << now << ") is " << isExist << endl;
        if (!isExist) { continue; }
        vis[{adjv, now}] = false;
        vis[{now, adjv}] = false; // 删去这条边
        cout << "Now, edge (" << adjv << "," << now << ") is " << "deleted!" << endl;
        if (adjv == source) {
            startBackTracking = true;
            sourceAds->next = new PathList(nullptr, now); // 延长链表
            nowAds = sourceAds->next; // 指针的引用 更新到最新生成的节点
            decreaseFdeg(now, adjv);
            break;
        }        
        dfs(sourceAds, adjv, startBackTracking, nowAds, originalNextAds);
        if (startBackTracking) {
            if (now == source) { // 如果回到了这一次dfs的起点
                // 拼接链表，拼接原先path上，后面部分的路径
                nowAds->next = originalNextAds != nullptr ? originalNextAds : new PathList(nullptr, sourceAds->curr); // 如果原来只是一个点，就把自己也拼上
            } else {
                nowAds->next = new PathList(nullptr, now);
                nowAds = nowAds->next;
            }
            decreaseFdeg(now, adjv);
            break;
        }
        
        
    } 
}





PathList* chooseNext(PathList* startFindingPt, int ne) {
    PathList* listCurr = startFindingPt;
    int counter = 1;
    while (listCurr != nullptr && fdeg[listCurr->curr] == 0) {
        listCurr = listCurr->next;
        counter++; // 不做成循环链表。
    }
    return listCurr; // 返回下一个应该拼接的点（新顶点）的指针
}


void writeOutPath(int ne, PathList* head) {
    PathList* listCurr = head; // start from 0
    int counter = 1;
    cout << "Let's draw: ";
    while (counter <= ne) {
        cout << listCurr->curr << "->";
        listCurr = listCurr->next;
        counter++;
    }
    cout << listCurr->curr << endl;
}


int main() {
    int ne = readInGraph();
    PathList* pathList = new PathList(nullptr, 0);
    if (!isPossible()) {
        cout << "Not possible to form an Eular circuit!" << endl;
        return 0; 
    } else {
        PathList* adsIterator = pathList; // address interator
        // 上一次循环拼接点，然后经历adsIterator = chooseNext(adsIterator, ne)就变成下一次循环起始点
        while (1) {
            bool vari = false;
            dfs(adsIterator, adsIterator->curr, vari, adsIterator, adsIterator->next);
            adsIterator = chooseNext(adsIterator, ne); 
            if (adsIterator == nullptr) { break; }
        }
        writeOutPath(ne, pathList);
    }
    return 0;
}