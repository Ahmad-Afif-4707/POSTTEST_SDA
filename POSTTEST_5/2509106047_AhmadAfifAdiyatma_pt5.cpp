#include <iostream>
#include <string>
using namespace std;

/*
    Soal 1: Inventaris Toko Sembako
    
    Melengkapi fungsi tampilkanStokSembako() untuk melakukan
    traversal pada Circular Linked List tanpa infinite loop.
    
    Kunci penyelesaian:
    - Pakai do-while bukan while biasa
    - do-while memastikan head ikut tercetak sebelum dicek kondisinya
    - Berhenti ketika temp sudah balik ke head lagi
    - Kalau head nullptr langsung print "Gudang kosong" dan return
*/

struct BarangNode {
    string namaBarang;
    int stok;
    BarangNode* next;

    BarangNode(string nama, int jumlah) {
        namaBarang = nama;
        stok       = jumlah;
        next       = nullptr;
    }
};

BarangNode* tambahBarang(BarangNode* head, string nama, int jumlah) {
    BarangNode* newNode = new BarangNode(nama, jumlah);

    // kalau list masih kosong, node menunjuk ke dirinya sendiri
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }

    // kalau tidak, jalan sampai node terakhir dulu
    // node terakhir ditandai dengan next-nya yang balik ke head
    BarangNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    // sambung node baru di belakang, lalu arahkan next-nya ke head
    temp->next    = newNode;
    newNode->next = head;
    return head;
}

void tampilkanStokSembako(BarangNode* head) {
    if (head == nullptr) {
        cout << "Gudang kosong." << endl;
        return;
    }

    // do-while dipakai supaya head ikut tercetak
    // karena kalau while biasa, kondisi temp != head
    // langsung false di iterasi pertama sebelum head tercetak
    BarangNode* temp = head;
    do {
        cout << "- " << temp->namaBarang << ": " << temp->stok << endl;
        temp = temp->next;
    } while (temp != head);
}

int main() {
    BarangNode* head = nullptr;

    head = tambahBarang(head, "Beras",         50);
    head = tambahBarang(head, "Minyak Goreng", 30);
    head = tambahBarang(head, "Gula Pasir",    20);
    head = tambahBarang(head, "Tepung Terigu", 15);

    cout << "Daftar Stok Sembako:" << endl;
    tampilkanStokSembako(head);

    //  Output yang diharapkan:  - Beras: 50  - Minyak Goreng: 30 - Gula Pasir: 20 - Tepung Terigu: 15

    return 0;
}