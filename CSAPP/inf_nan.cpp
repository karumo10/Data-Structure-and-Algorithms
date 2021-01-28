#include <iostream>
#define POS_INFINITY 1.8e308
#define NEG_INFINITY -1.8e308
#define NEG_ZERO 1/-1.8e308
#define NAN POS_INFINITY+NEG_INFINITY
using namespace std;
int main() {
    double a = 1.7e308;
    cout << NEG_INFINITY << NEG_ZERO << NAN;
    return 0;
}