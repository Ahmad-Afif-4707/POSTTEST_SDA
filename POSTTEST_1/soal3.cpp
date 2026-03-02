#include <iostream>
using namespace std;

void balikArray(int* arr, int n) {
    int* awal = arr;
    int* akhir = arr + n - 1;

    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

int main() {
    int A[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "=== ARRAY SEBELUM DIBALIK ===" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(A + i)
             << " | Alamat: " << (A + i) << endl;
    }

    balikArray(A, 7);

    cout << "\n=== ARRAY SESUDAH DIBALIK ===" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "Nilai: " << *(A + i)
             << " | Alamat: " << (A + i) << endl;
    }

    return 0;
}