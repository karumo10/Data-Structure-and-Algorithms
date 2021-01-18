#include <iostream>

using namespace std;

int main() {
    int n;
    int counter = 0; //how many comparisons
    cout << "How many? ";
    cin >> n;
    cout << endl << "What are them? ";
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int x = a[i]; //current
        int left = 0, right = i-1, mid = (left+right)/2;
        while (left <= right) {
            if (a[mid] == x) {
                left = mid;
                counter ++;
                break;
            }
            else if (a[mid] > x) {
                right = mid-1;
                counter ++;
            }
            else {
                left = mid+1;
                counter ++;
            }
            mid = (left+right)/2;
        }
        for (int j = i; j >= left+1; j--) {
            a[j] = a[j-1];
        }
        a[left] = x;

        cout << counter << endl;
    }
    cout << "sorted by binary sort: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl << "times: " << counter << endl;
    delete[] a;
    return 0;
}