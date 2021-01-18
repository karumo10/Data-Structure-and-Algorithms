#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Vertex {
public:
    int index; // the index of this vertex in the graph. If needed, it can be get by hashing
    bool isVisited = false;
    int* adjVertices; // array of adjacent vertices' index(in the graph)
    int adjNum;
    int lastVisited = -2; // used to print out answer, only one.
    Vertex(){};
    Vertex(int index, int adjNum, int adjVertices[]);
    ~Vertex();
};

typedef Vertex* Graph; // array

void bfs(Vertex& start, Graph& graph, const int aim) {
    start.lastVisited = -1; // dummy vertice
    start.isVisited = true;
    graph[start.index] = start;
    queue<Vertex> q;
    q.push(start);
    while (!q.empty()) {
        Vertex curr = q.front();
        
        for (int i = 0; i < curr.adjNum; i++) {
            Vertex &adj = graph[curr.adjVertices[i]];
            if (!adj.isVisited) {
                
                adj.isVisited = true;
                adj.lastVisited = curr.index;
                q.push(adj);
                /*start print*/
                if (adj.index == aim) { // found
                    int ans[1000]{-1};
                    Vertex last = adj;
                    int counter = 0;
                    while (last.lastVisited != -1) {
                        ans[counter++] = last.index;
                        last = graph[last.lastVisited];
                    }
                    ans[counter] = last.index;
                    for (int j = counter; j >= 0; j--) {
                        cout << "v" << ans[j] << endl;
                    }
                }


            }
        }
        q.pop();
        
    }

}


Vertex::Vertex(int index, int adjNum, int adjVertices[]) 
    : index(index), adjNum(adjNum) {
    this->adjVertices = new int[adjNum];
    for (int i = 0; i < adjNum; i++) {
        this->adjVertices[i] = adjVertices[i];
    }
}

Vertex::~Vertex() {
    // delete[] this->adjVertices;
}

int main() {
    int a0[2] = {3,6}, a1[2] = {2,5}, a2[1] = {4}, a3[2] = {1,2},
        a4[1] = {5}, a5[1] = {2}, a6[2] = {2,3};
    Vertex v0 = Vertex(0,2,a0), v1 = Vertex(1,2,a1)
        , v2 = Vertex(2,1,a2), v3 = Vertex(3,2,a3)
        , v4 = Vertex(4,1,a4), v5 = Vertex(5,1,a5)
        , v6 = Vertex(6,2,a6);
    Vertex* g = new Vertex[7];
    g[0] = v0; g[1] = v1; g[2] = v2; g[3] = v3; g[4] = v4; g[5] = v5; g[6] = v6;
    bfs(v0,g,4);
    return 0;
}