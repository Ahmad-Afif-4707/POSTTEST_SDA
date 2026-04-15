#include <iostream>
#include <cstdlib>
using namespace std;

struct Hewan {
    int id;
    string nama;
    string jenis;
    float harga;
};

struct NodeAntrian {
    int idHewan;
    string namaHewan;
    NodeAntrian *next;
};

struct NodeRiwayat {
    int idHewan;
    string namaHewan;
    string catatan;
    NodeRiwayat *next;
};

int jumlahData = 5;
Hewan listHewan[100] = {
    {101, "Oren",  "Kucing",  50000},
    {102, "Doggy", "Anjing",  75000},
    {103, "Bunny", "Kelinci", 40000},
    {104, "Mochi", "Hamster", 30000},
    {105, "Koi",   "Ikan",    25000}
};

NodeAntrian *headAntrian = nullptr;
NodeAntrian *tailAntrian = nullptr;
NodeRiwayat *headRiwayat = nullptr;

// fungsi hewan
void tukar(Hewan *a, Hewan *b){
    Hewan tmp = *a;
    *a = *b;
    *b = tmp;
}

void tampil(Hewan *arr){
    if(jumlahData == 0){
        cout << "data kosong\n";
        return;
    }
    cout << "\ndaftar hewan:\n";
    for(int i = 0; i < jumlahData; i++){
        cout << i+1 << ". ";
        cout << "ID: "   << (arr+i)->id;
        cout << " | "    << (arr+i)->nama;
        cout << " ("     << (arr+i)->jenis << ")";
        cout << " | Rp " << (arr+i)->harga << "\n";
    }
}

void tambah(Hewan *arr){
    if(jumlahData >= 100){
        cout << "data sudah penuh!\n";
        return;
    }

    int inputID;
    cout << "ID: ";
    cin  >> inputID;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "ID harus angka!\n";
        return;
    }

    for(int i = 0; i < jumlahData; i++){
        if((arr+i)->id == inputID){
            cout << "ID sudah dipakai!\n";
            return;
        }
    }

    string inputNama, inputJenis;
    float  inputHarga;

    cout << "Nama: ";  cin >> inputNama;
    cout << "Jenis: "; cin >> inputJenis;
    cout << "Harga: "; cin >> inputHarga;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "harga harus angka!\n";
        return;
    }

    char konfirmasi;
    cout << "simpan data " << inputNama << "? (y/n): ";
    cin  >> konfirmasi;
    if(konfirmasi != 'y' && konfirmasi != 'Y'){
        cout << "dibatalkan\n";
        return;
    }

    (arr+jumlahData)->id    = inputID;
    (arr+jumlahData)->nama  = inputNama;
    (arr+jumlahData)->jenis = inputJenis;
    (arr+jumlahData)->harga = inputHarga;
    jumlahData++;
    cout << inputNama << " berhasil ditambah!\n";
}

void hapusSemua(int &jumlah){
    if(jumlah == 0){
        cout << "sudah kosong!\n";
        return;
    }

    char konfirmasi;
    cout << "yakin hapus semua data? (y/n): ";
    cin  >> konfirmasi;
    if(konfirmasi != 'y' && konfirmasi != 'Y'){
        cout << "dibatalkan\n";
        return;
    }

    jumlah = 0;
    cout << "semua data dihapus\n";
}

void cariNama(Hewan *arr){
    if(jumlahData == 0){ cout << "data kosong\n"; return; }

    string kataCari;
    cout << "nama yang dicari: ";
    cin  >> kataCari;

    bool adaData = false;
    for(int i = 0; i < jumlahData; i++){
        if((arr+i)->nama == kataCari){
            cout << "ketemu!\n";
            cout << "ID    : " << (arr+i)->id    << "\n";
            cout << "Nama  : " << (arr+i)->nama  << "\n";
            cout << "Jenis : " << (arr+i)->jenis << "\n";
            cout << "Harga : " << (arr+i)->harga << "\n";
            adaData = true;
        }
    }
    if(!adaData) cout << kataCari << " tidak ditemukan\n";
}

void sortNama(Hewan *arr){
    if(jumlahData == 0){ cout << "data kosong!\n"; return; }
    for(int putaran = 0; putaran < jumlahData-1; putaran++){
        for(int pos = 0; pos < jumlahData-putaran-1; pos++){
            if((arr+pos)->nama > (arr+pos+1)->nama){
                tukar(arr+pos, arr+pos+1);
            }
        }
    }
    cout << "urut nama selesai\n";
    tampil(arr);
}

void sortHarga(Hewan *arr){
    if(jumlahData == 0){ cout << "data kosong!\n"; return; }
    for(int putaran = 0; putaran < jumlahData-1; putaran++){
        int posTermurah = putaran;
        for(int pos = putaran+1; pos < jumlahData; pos++){
            if((arr+pos)->harga < (arr+posTermurah)->harga){
                posTermurah = pos;
            }
        }
        if(posTermurah != putaran){
            tukar(arr+putaran, arr+posTermurah);
        }
    }
    cout << "urut harga selesai\n";
    tampil(arr);
}

void urutID(Hewan *arr){
    for(int putaran = 0; putaran < jumlahData-1; putaran++){
        for(int pos = 0; pos < jumlahData-putaran-1; pos++){
            if((arr+pos)->id > (arr+pos+1)->id){
                tukar(arr+pos, arr+pos+1);
            }
        }
    }
}

void cariID(Hewan *arr){
    if(jumlahData == 0){ cout << "data kosong\n"; return; }

    int idDicari;
    cout << "ID yang dicari: ";
    cin  >> idDicari;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "ID harus angka!\n";
        return;
    }

    urutID(arr);

    int fibKedua    = 0;
    int fibPertama  = 1;
    int fibSekarang = fibPertama + fibKedua;

    while(fibSekarang < jumlahData){
        fibKedua    = fibPertama;
        fibPertama  = fibSekarang;
        fibSekarang = fibPertama + fibKedua;
    }

    int posisiOffset = -1;

    // data harus terurut dulu sebelum dicari
    // hitung index cek pakai rumus posisiOffset + fibKedua
    // kalau ID di index lebih kecil, geser ke kanan
    // kalau ID di index lebih besar, geser ke kiri
    // kalau sama berarti ketemu
    // kalau fibSekarang sudah <= 1 cek satu elemen sisa di offset+1
    while(fibSekarang > 1){
        int posCek = posisiOffset + fibKedua;
        if(posCek >= jumlahData) posCek = jumlahData - 1;

        if((arr+posCek)->id < idDicari){
            fibSekarang  = fibPertama;
            fibPertama   = fibKedua;
            fibKedua     = fibSekarang - fibPertama;
            posisiOffset = posCek;
        }
        else if((arr+posCek)->id > idDicari){
            fibSekarang = fibKedua;
            fibPertama  = fibPertama - fibKedua;
            fibKedua    = fibSekarang - fibPertama;
        }
        else{
            cout << "ketemu!\n";
            cout << "ID    : " << (arr+posCek)->id    << "\n";
            cout << "Nama  : " << (arr+posCek)->nama  << "\n";
            cout << "Jenis : " << (arr+posCek)->jenis << "\n";
            cout << "Harga : " << (arr+posCek)->harga << "\n";
            return;
        }
    }

    if(fibPertama && posisiOffset+1 < jumlahData && (arr+posisiOffset+1)->id == idDicari){
        cout << "ketemu!\n";
        cout << "ID    : " << (arr+posisiOffset+1)->id    << "\n";
        cout << "Nama  : " << (arr+posisiOffset+1)->nama  << "\n";
        cout << "Jenis : " << (arr+posisiOffset+1)->jenis << "\n";
        cout << "Harga : " << (arr+posisiOffset+1)->harga << "\n";
        return;
    }

    cout << "ID " << idDicari << " tidak ditemukan\n";
}

void enqueue(NodeAntrian *&head, NodeAntrian *&tail){
    if(jumlahData == 0){ cout << "belum ada data hewan!\n"; return; }

    int idCari;
    cout << "ID hewan: ";
    cin  >> idCari;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "ID harus angka!\n";
        return;
    }

    for(int i = 0; i < jumlahData; i++){
        if((listHewan+i)->id == idCari){
            char konfirmasi;
            cout << "daftarkan " << (listHewan+i)->nama << " ke antrian? (y/n): ";
            cin  >> konfirmasi;
            if(konfirmasi != 'y' && konfirmasi != 'Y'){
                cout << "dibatalkan\n";
                return;
            }

            NodeAntrian *nodeBaru = new NodeAntrian;
            nodeBaru->idHewan   = idCari;
            nodeBaru->namaHewan = (listHewan+i)->nama;
            nodeBaru->next      = nullptr;

            if(head == nullptr){
                head = nodeBaru;
                tail = nodeBaru;
            } else {
                tail->next = nodeBaru;
                tail       = nodeBaru;
            }

            cout << (listHewan+i)->nama << " masuk antrian\n";
            return;
        }
    }
    cout << "ID tidak ditemukan\n";
}

void dequeue(NodeAntrian *&head, NodeAntrian *&tail){
    if(head == nullptr){
        cout << "antrian kosong!\n";
        return;
    }

    cout << "pasien berikutnya: " << head->namaHewan << "\n";

    char konfirmasi;
    cout << "panggil sekarang? (y/n): ";
    cin  >> konfirmasi;
    if(konfirmasi != 'y' && konfirmasi != 'Y'){
        cout << "dibatalkan\n";
        return;
    }

    int    idDipanggil   = head->idHewan;
    string namaDipanggil = head->namaHewan;

    NodeAntrian *temp = head;
    head              = head->next;
    if(head == nullptr) tail = nullptr;
    delete temp;

    cout << "memanggil " << namaDipanggil << " (ID: " << idDipanggil << ")\n";

    string catatan;
    cout << "catatan tindakan: ";
    cin  >> catatan;

    NodeRiwayat *nodeRiwayat = new NodeRiwayat;
    nodeRiwayat->idHewan   = idDipanggil;
    nodeRiwayat->namaHewan = namaDipanggil;
    nodeRiwayat->catatan   = catatan;
    nodeRiwayat->next      = headRiwayat;
    headRiwayat            = nodeRiwayat;

    cout << "dicatat ke riwayat\n";
}

void tampilAntrian(NodeAntrian *head){
    if(head == nullptr){
        cout << "antrian kosong\n";
        return;
    }

    cout << "terdepan : " << head->namaHewan;
    cout << " (ID: " << head->idHewan << ")\n";

    cout << "\nsemua antrian:\n";
    NodeAntrian *temp = head;
    int urutan = 1;
    while(temp != nullptr){
        cout << urutan << ". ";
        cout << temp->namaHewan;
        cout << " (ID: " << temp->idHewan << ")\n";
        temp = temp->next;
        urutan++;
    }
}

void peekAntrian(NodeAntrian *head){
    if(head == nullptr){
        cout << "antrian kosong\n";
        return;
    }
    cout << "pasien terdepan: " << head->namaHewan;
    cout << " (ID: " << head->idHewan << ")\n";
}

// fungsi stack
void push(NodeRiwayat *&head){
    if(jumlahData == 0){ cout << "belum ada data hewan!\n"; return; }

    int idCari;
    cout << "ID hewan: ";
    cin  >> idCari;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "ID harus angka!\n";
        return;
    }

    string catatan;
    cout << "catatan tindakan: ";
    cin  >> catatan;

    for(int i = 0; i < jumlahData; i++){
        if((listHewan+i)->id == idCari){
            NodeRiwayat *nodeBaru = new NodeRiwayat;
            nodeBaru->idHewan   = idCari;
            nodeBaru->namaHewan = (listHewan+i)->nama;
            nodeBaru->catatan   = catatan;
            nodeBaru->next      = head;
            head                = nodeBaru;
            cout << "riwayat berhasil ditambahkan\n";
            return;
        }
    }
    cout << "ID tidak ditemukan\n";
}

void pop(NodeRiwayat *&head){
    if(head == nullptr){
        cout << "riwayat kosong!\n";
        return;
    }

    cout << "hapus tindakan: ";
    cout << head->namaHewan;
    cout << " - " << head->catatan << "\n";

    char konfirmasi;
    cout << "yakin? (y/n): ";
    cin  >> konfirmasi;
    if(konfirmasi != 'y' && konfirmasi != 'Y'){
        cout << "dibatalkan\n";
        return;
    }

    NodeRiwayat *temp = head;
    head              = head->next;
    delete temp;
    cout << "tindakan terakhir dihapus\n";
}

void peekRiwayat(NodeRiwayat *head){
    if(head == nullptr){
        cout << "riwayat kosong\n";
        return;
    }
    cout << "tindakan terakhir: " << head->namaHewan;
    cout << " - " << head->catatan << "\n";
}

void tampilRiwayat(NodeRiwayat *head){
    if(head == nullptr){
        cout << "riwayat kosong\n";
        return;
    }

    cout << "terakhir  : " << head->namaHewan;
    cout << " - " << head->catatan << "\n";

    cout << "\nriwayat tindakan:\n";
    NodeRiwayat *temp = head;
    int urutan = 1;
    while(temp != nullptr){
        cout << urutan << ". ";
        cout << temp->namaHewan;
        cout << " - " << temp->catatan;
        cout << " (ID: " << temp->idHewan << ")\n";
        temp = temp->next;
        urutan++;
    }
}

// menu
int main(){
    int pilihanMenu;
    do{
        cout << "\n";
        cout << "|------------------------|------------------------|\n";
        cout << "|      Pawcare Petshop   |    Antrian & Riwayat   |\n";
        cout << "|------------------------|------------------------|\n";
        cout << "| 1. lihat data          |  8. enqueue            |\n";
        cout << "| 2. tambah hewan        |  9. dequeue            |\n";
        cout << "| 3. cari nama           | 10. tampil antrian     |\n";
        cout << "| 4. cari ID             | 11. peek antrian       |\n";
        cout << "| 5. urut nama           | 12. push riwayat       |\n";
        cout << "| 6. urut harga          | 13. pop riwayat        |\n";
        cout << "| 7. hapus semua         | 14. tampil riwayat     |\n";
        cout << "|                        | 15. peek riwayat       |\n";
        cout << "|                        |  0. keluar             |\n";
        cout << "|------------------------|------------------------|\n";
        cout << "pilih: ";
        cin  >> pilihanMenu;

        if(cin.fail()){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "pilihannya angka ya...\n";
            continue;
        }

        system("cls");

        switch(pilihanMenu){
            case 1:  tampil(listHewan);                        break;
            case 2:  tambah(listHewan);                        break;
            case 3:  cariNama(listHewan);                      break;
            case 4:  cariID(listHewan);                        break;
            case 5:  sortNama(listHewan);                      break;
            case 6:  sortHarga(listHewan);                     break;
            case 7:  hapusSemua(jumlahData);                   break;
            case 8:  enqueue(headAntrian, tailAntrian);        break;
            case 9:  dequeue(headAntrian, tailAntrian);        break;
            case 10: tampilAntrian(headAntrian);               break;
            case 11: peekAntrian(headAntrian);                 break;
            case 12: push(headRiwayat);                        break;
            case 13: pop(headRiwayat);                         break;
            case 14: tampilRiwayat(headRiwayat);               break;
            case 15: peekRiwayat(headRiwayat);                 break;
            case 0:  cout << "sampai jumpa...\n";              break;
            default: cout << "pilihan tidak ada\n";
        }

        if(pilihanMenu != 0){
            cout << "\nenter untuk lanjut...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    }while(pilihanMenu != 0);

    return 0;
}