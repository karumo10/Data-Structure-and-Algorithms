#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


// 并查集。关键就是：每次连接两个点的时候，如果这两个点已经在同一个集里了，则说明形成了一个多的环，形成多的环就说明多了一个area



class FUSet { // Find/Union Set
private:
    vector<int> set;
    int num; // 顶点数
public:
    FUSet() {};
    int size() {return num;}
    FUSet(int n) : num(n) {
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
    ~FUSet() {};
};

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) { // 算法：每把两个已经联通的点连起来，就添加一个区域
        int n = grid.size()+1;
        int tt = n*n;
        FUSet set(tt);
        for (int i = 0; i < n-1; i++) {
            set.setUnion(i, i+1);
            set.setUnion(i+n*(n-1), i+n*(n-1)+1);
        }
        for (int i = 0; i < n-1; i++) {
            set.setUnion(i*n, i*n+n);
            set.setUnion(i*n+n-1, i*n+n+n-1);
        }
        
        int len = grid.size();
        int areas = 1;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (grid[i][j] == ' ') continue;
                int u,v;
                int x = j + len * i;
                if (grid[i][j] == '/') {
                    u = i+x+1;
                    v = i+x+n;
                    if (set.inSameClu(u,v)) {
                        areas++;
                    }
                    set.setUnion(u,v);
                } else {
                    u = i+x;
                    v = i+x+n+1;
                    if (set.inSameClu(u,v)) {
                        areas++;
                    }
                    set.setUnion(u,v);
                }
            }
        }
        return areas;
    }
};

int main() {
    return 0;
}