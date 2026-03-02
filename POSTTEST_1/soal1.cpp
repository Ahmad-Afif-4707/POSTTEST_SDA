#include <iostream>
using namespace std;

int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];
    indexMin = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            indexMin = i;
        }
    }
    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int idx;

    int minimum = FindMin(A, 8, idx);

    cout << "Nilai minimum : " << minimum << endl;
    cout << "Indeks minimum: " << idx << endl;

    return 0;
}

/*
Tmin(n) =
C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8 + C9
= an + b
= O(n)

Tmax(n) =
C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1)
+ C7n + C8 + C9
= an + b
= O(n)

Kesimpulan:
Best Case  = O(n)
Worst Case = O(n)
Kompleksitas Linear
*/