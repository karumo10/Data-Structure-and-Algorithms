#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*这题就是个数学题...初看可能比较难，会想到用黑白灰 BFS 去找环然后把环拆掉去补没连上的边，但是发现只需要返回边数，并不需要知道拆的是哪里，补的又是哪里...emm...就很简单了你只要先用一个并查集，把 connected 的顶点归类一下，再数一数有多少个 connected 的群落（记为 n ）。
然后做一个问题的转化：把每个群落看做一个单点，我们如果要把这张图所有的点都连起来，本质上就是要把这张群落图全部连起来，这最少需要 n-1 条边。然后就秒掉了，好耶！
*/



class FUSet { // Find/Union Set
private:
    vector<int> set;
    int num; // 顶点数
    int clusters; // 群落数
public:
    FUSet() {};
    int size() {return num;}
    FUSet(int n) : num(n), clusters(n) {
        set.resize(n);
        for (int i = 0; i < n; i++) {
            set[i] = -1;
        } // 初始化，这里把并查集根元素的set值直接定义为：当前根下元素总数目的相反数（-size）
    };
    int find(int n) {
        if (set[n] < 0) return n; // 找到根
        else return set[n] = find(set[n]); // 路径压缩
    }
    void setUnion(int a, int b) {
        int roota = find(a), rootb = find(b);
        if (roota == rootb) return; // 防止重复合并，不然size会指数级放大！
        if (roota != rootb) {clusters--;}
        int sizea = -set[roota], sizeb = -set[rootb];
        if (sizea > sizeb) { // 按大小求并
            set[rootb] = roota;
            set[roota] = -sizea-sizeb;
        } else {
            set[roota] = rootb;
            set[rootb] = -sizea-sizeb;
        }
    }
    bool inSameClu(int a, int b) {return find(a) == find(b);} // 是否在一个群落里
    int getClu() {return clusters;} // 返回群落数目
    ~FUSet() {};
};


class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        int useless = 0; // 没用的边数目，可以拿来连接不同的群落
        FUSet vtcs(n);
        for (auto& edge : connections) {
            int u = edge[0], v = edge[1];
            if (vtcs.inSameClu(u,v)) {
                useless++; // 已经在一个群落里了
                continue;
            } else {
                vtcs.setUnion(u,v); // 连到一起
            }
        }
        int clusters = vtcs.getClu();
        if (clusters-1 > useless) { // 冗余边不够把群落连成树
            return -1;
        }
        else {
            return clusters-1; // 冗余边多，返回需要的最小边数
        }
    }
};

int main() {
    FUSet set(10);
    cout << set.size() << endl;
    return 0;
}


