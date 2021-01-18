
/*
This is for a classical problem:
several lights are arranged in a circle,
at first all lights are not opened,
the task you should do is to open all the light.
However, whenever you open a light, the two lights next to it will change its state:
that is, if the light group 11010101's 3rd light is operated,
the group will be come 10100101.

Here the code just offer a brute-force algorithm with exponential time complexity.
If use Gauss elimination to solve the XOR linear equation group, maybe we can come up with algorithms which are more efficient.
*/
// 本来是拿来解原神的一个点火把问题的，然而原神那个火把点亮后就不能点灭了，太屑
#include <iostream>
using namespace std;
int howmany=7;

bool judge(const int* p, size_t length) {
    bool result = true;
    for (int i = 0; (size_t)i < length; i++) {
        if (i == 0) {
            result = result & (bool) ((p[i] + p[length-1] + p[1]) % 2);
        } else if (i== length-1) {
            result = result & (bool) ((p[i] + p[0] + p[i-1]) % 2);
        } else {
            result = result & (bool) ((p[i] + p[i-1] + p[i+1]) % 2);
        }
    }
    return result;
}



int* enumerating(int* p, int depth, size_t length) { // index: from 0 to depth, in total 1+depth; length is the size
    if (depth > 0) {
        for (int i = 0; i <= 1; i++) {
            *(p+depth)=i;
            p = enumerating(p, depth - 1, length);
        }
    } else {
        for (int i = 0; i <= 1; i++) {
            *(p+depth)=i;
            bool available = judge(p, length);
            if (available) {
                for (int j = 0; (size_t) j < length; j++) {
                    cout << *(p + j);
                }
                cout << endl;
            }

//            if (available) { cout << " is OK!"; }
//            else { cout << " is not OK!"; }

        }
        return p;
    }
    return p;
}


int main() {
    int* p = new int[howmany];
    for (int i = 0; i < howmany; i++) {
        *(p+i) = 0;
    }
    enumerating(p,howmany-1,howmany);
    delete[] p;
    return 0;
}