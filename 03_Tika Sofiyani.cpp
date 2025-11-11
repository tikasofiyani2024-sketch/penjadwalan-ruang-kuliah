#include <iostream>
#include <string>
using namespace std;

struct Pasien {
    string nama;
    int lamaRawat;
    string kategori; 
};

string kategoriPasien(int lama) {
    return (lama >= 7) ? "Rawat Lama" : "Rawat Singkat";
}

void tampilkanData(Pasien data[], int n) {
    cout << "\n--- Data Pasien ---\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << data[i].nama
            << " | Lama Rawat: " << data[i].lamaRawat
            << " hari | " << data[i].kategori << endl;
    }
}


string kategoriUmum(int total) {
    if (total >= 10) return "Kasus Berat";
    else if (total >= 5) return "Kasus Sedang";
    else return "Kasus Ringan";
}

int main() {
    int n;
    cout << "Masukkan jumlah pasien: ";
    cin >> n;

    Pasien pasien[100];
    int totalHari = 0;

    for (int i = 0; i < n; i++) {
        cout << "\nPasien ke-" << i + 1 << endl;
        cout << "Nama Pasien      : ";
        cin >> pasien[i].nama;
        cout << "Lama Rawat Inap  : ";
        cin >> pasien[i].lamaRawat;

        pasien[i].kategori = kategoriPasien(pasien[i].lamaRawat);
        totalHari += pasien[i].lamaRawat;
    }

  
    tampilkanData(pasien, n);
 
    int maxHari = pasien[0].lamaRawat, minHari = pasien[0].lamaRawat;
    int posMax = 0, posMin = 0;

    for (int i = 1; i < n; i++) {
        if (pasien[i].lamaRawat > maxHari) {
            maxHari = pasien[i].lamaRawat;
            posMax = i;
        }
        if (pasien[i].lamaRawat < minHari) {
            minHari = pasien[i].lamaRawat;
            posMin = i;
        }
    }

    cout << "\n--- Analisis Rawat Inap Pasien ---\n";
    cout << "Rawat Terlama   : " << pasien[posMax].nama
        << " (" << maxHari << " hari), posisi ke-" << posMax + 1 << endl;
    cout << "Rawat Tersingkat: " << pasien[posMin].nama
        << " (" << minHari << " hari), posisi ke-" << posMin + 1 << endl;

    cout << "\nKategori Umum Rumah Sakit: " << kategoriUmum(totalHari / n) << endl;

    return 0;
}
