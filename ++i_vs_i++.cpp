#include <iostream>

using namespace std;

int main() {
    int a[5]{0};
    int i,j = 0;
    // a[i++] = 1;
    a[++j] = 1;
    for (int k = 0; k < 5; k++) {
        cout << a[k] << endl;
    }
    return 0;

}