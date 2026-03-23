#include <iostream>
#include <cstdlib>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    float harga;
};

int jumlahData = 5;

Hewan hewan[100] = {
    {101,"Oren","Kucing",50000},
    {102,"Doggy","Anjing",75000},
    {103,"Bunny","Kelinci",40000},
    {104,"Mochi","Hamster",30000},
    {105,"Koi","Ikan",25000}
};

void tukar(Hewan *a, Hewan *b){
    Hewan tmp = *a;
    *a = *b;
    *b = tmp;
}

void tampil(Hewan *arr){
    if(jumlahData == 0){ cout<<"Data kosong\n"; return; }
    for(int indexUrut=0; indexUrut<jumlahData; indexUrut++){
        cout<<(arr+indexUrut)->id<<" - "<<(arr+indexUrut)->nama<<" - "<<(arr+indexUrut)->jenis<<" - "<<(arr+indexUrut)->harga<<"\n";
    }
}

void tambah(Hewan *arr){
    cout<<"ID: "; cin>>(arr+jumlahData)->id;
    cout<<"Nama: "; cin>>(arr+jumlahData)->nama;
    cout<<"Jenis: "; cin>>(arr+jumlahData)->jenis;
    cout<<"Harga: "; cin>>(arr+jumlahData)->harga;
    jumlahData++;
    cout<<"Berhasil ditambah\n";
}

void hapusSemua(int &jumlah){
    jumlah = 0;
    cout<<"Data dihapus\n";
}

void cariNama(Hewan *arr){
    string kataCari;
    cout<<"Nama: "; cin>>kataCari;

    bool adaData = false;
    for(int indexUrut=0; indexUrut<jumlahData; indexUrut++){
        if((arr+indexUrut)->nama == kataCari){
            cout<<"Ketemu!\n";
            cout<<"ID: "<<(arr+indexUrut)->id<<"\n";
            cout<<"Nama: "<<(arr+indexUrut)->nama<<"\n";
            cout<<"Jenis: "<<(arr+indexUrut)->jenis<<"\n";
            cout<<"Harga: "<<(arr+indexUrut)->harga<<"\n";
            adaData = true;
        }
    }
    if(!adaData) cout<<"Tidak ditemukan\n";
}

void sortNama(Hewan *arr){
    for(int putaran=0; putaran<jumlahData-1; putaran++){
        for(int posisiCek=0; posisiCek<jumlahData-putaran-1; posisiCek++){
            if((arr+posisiCek)->nama > (arr+posisiCek+1)->nama){
                tukar(arr+posisiCek, arr+posisiCek+1);
            }
        }
    }
    cout<<"Selesai diurutkan\n";
    tampil(arr);
}

void sortHarga(Hewan *arr){
    for(int putaran=0; putaran<jumlahData-1; putaran++){
        int posisiTermurah = putaran;
        for(int posisiCek=putaran+1; posisiCek<jumlahData; posisiCek++){
            if((arr+posisiCek)->harga < (arr+posisiTermurah)->harga) posisiTermurah = posisiCek;
        }
        if(posisiTermurah != putaran) tukar(arr+putaran, arr+posisiTermurah);
    }
    cout<<"Selesai diurutkan\n";
    tampil(arr);
}

void urutID(Hewan *arr){
    for(int putaran=0; putaran<jumlahData-1; putaran++){
        for(int posisiCek=0; posisiCek<jumlahData-putaran-1; posisiCek++){
            if((arr+posisiCek)->id > (arr+posisiCek+1)->id){
                tukar(arr+posisiCek, arr+posisiCek+1);
            }
        }
    }
}

void cariID(Hewan *arr){
    int idDicari;
    cout<<"ID: "; cin>>idDicari;

    urutID(arr);

    int fibKedua=0, fibPertama=1, fibSekarang=fibPertama+fibKedua;
    while(fibSekarang < jumlahData){ fibKedua=fibPertama; fibPertama=fibSekarang; fibSekarang=fibPertama+fibKedua; }

    int posisiOffset = -1;

    // Proses Fibonacci Search:
    // - data harus terurut dulu sebelum dicari
    // - hitung index cek pakai rumus posisiOffset + fibKedua
    // - jika ID di index < yang dicari, geser pencarian ke kanan (naikkan offset)
    // - jika ID di index > yang dicari, geser pencarian ke kiri (turunkan fibonacci)
    // - jika ID sama, data ketemu
    // - jika fibSekarang sudah <= 1, cek satu elemen tersisa di offset+1
    while(fibSekarang > 1){
        int posisiCek = posisiOffset+fibKedua;
        if(posisiCek >= jumlahData) posisiCek = jumlahData-1;

        if((arr+posisiCek)->id < idDicari){
            fibSekarang=fibPertama;
            fibPertama=fibKedua;
            fibKedua=fibSekarang-fibPertama;
            posisiOffset=posisiCek;
        }
        else if((arr+posisiCek)->id > idDicari){
            fibSekarang=fibKedua;
            fibPertama=fibPertama-fibKedua;
            fibKedua=fibSekarang-fibPertama;
        }
        else{
            cout<<"Ketemu!\n";
            cout<<"ID: "<<(arr+posisiCek)->id<<"\n";
            cout<<"Nama: "<<(arr+posisiCek)->nama<<"\n";
            cout<<"Jenis: "<<(arr+posisiCek)->jenis<<"\n";
            cout<<"Harga: "<<(arr+posisiCek)->harga<<"\n";
            return;
        }
    }

    if(fibPertama && posisiOffset+1 < jumlahData && (arr+posisiOffset+1)->id == idDicari){
        cout<<"Ketemu!\n";
        cout<<"ID: "<<(arr+posisiOffset+1)->id<<"\n";
        cout<<"Nama: "<<(arr+posisiOffset+1)->nama<<"\n";
        cout<<"Jenis: "<<(arr+posisiOffset+1)->jenis<<"\n";
        cout<<"Harga: "<<(arr+posisiOffset+1)->harga<<"\n";
        return;
    }

    cout<<"Tidak ditemukan\n";
}

int main(){
    int pilihanMenu;
    do{
        cout<<"\n=== Pawcare Petshop ===\n";
        cout<<"1. Tampil data\n";
        cout<<"2. Tambah hewan\n";
        cout<<"3. Cari nama\n";
        cout<<"4. Cari ID\n";
        cout<<"5. Urutkan nama\n";
        cout<<"6. Urutkan harga\n";
        cout<<"7. Hapus semua\n";
        cout<<"8. Keluar\n";
        cout<<"Pilih: "; cin>>pilihanMenu;

        system("cls");

        switch(pilihanMenu){
            case 1: tampil(hewan); break;
            case 2: tambah(hewan); break;
            case 3: cariNama(hewan); break;
            case 4: cariID(hewan); break;
            case 5: sortNama(hewan); break;
            case 6: sortHarga(hewan); break;
            case 7: hapusSemua(jumlahData); break;
            case 8: cout<<"Sampai jumpa!\n"; break;
            default: cout<<"Pilihan salah\n";
        }

        if(pilihanMenu != 8){
            cout<<"\nEnter untuk kembali...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    }while(pilihanMenu!=8);

    return 0;
}