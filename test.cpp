#include <iostream>
#include <vector>
#include <unordered_map>

// 测一下unordered_map的功能，发现const 的unordered_map是不能用下标读取的，可能是这个下标没有overloaded以常量形式访问。。
using namespace std;
int main() {
    unordered_map<string,string> foo;
    foo.emplace("1","haha");
    const string p = "ppp";
    foo.emplace("ppp","pp");
    const unordered_map<string,string> bar = foo;
    // cout << bar[p] << endl;
    cout << foo["1"] << endl;
    vector<int> boo(3,3);
    for (auto i : boo) {
        cout << i << endl;
    }
    return 0;
}