#include <iostream>
#define POS_INFINITY 1.8e308 // overflow
#define NEG_INFINITY -1.8e308
#define NEG_ZERO 1/-1.8e308
#define NAN POS_INFINITY+NEG_INFINITY
using namespace std;
int main() {
    double a = 1.7e308;
    cout << NEG_INFINITY << NEG_ZERO << NAN << endl;
    cout << (int)a << endl; // overflow, intel cpu set 0x80000000 (1000....00) as the so-called "integer indefinite" to express those values that overflow by a cast from double/float to int
    return 0;
}