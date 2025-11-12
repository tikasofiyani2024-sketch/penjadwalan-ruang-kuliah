#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ========================= STRUKTUR DATA =========================
struct Jadwal {
    string kode;
    string mataKuliah;
    string hari;
    string jamMulai;
    string jamSelesai;
    string ruangan;
};

const int MAKS_JADWAL = 50;
Jadwal daftarJadwal[MAKS_JADWAL];
int jumlahJadwal = 0;

// ========================= VALIDASI INPUT =========================
bool validasiHari(string hari) {
    string daftarHari[5] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    for (int i = 0; i < 5; i++) {
        if (hari == daftarHari[i]) return true;
    }
    return false;
}

bool validasiJam(int jam) {
    return (jam >= 7 && jam <= 17);
}

// ========================= CARI DAN CEK BENTROK =========================
int cariBentrok(string hari, string jamMulai, string ruangan) {
    for (int i = 0; i < jumlahJadwal; i++) {
        if (daftarJadwal[i].hari == hari && daftarJadwal[i].jamMulai == jamMulai && daftarJadwal[i].ruangan == ruangan) {
            return i; // ditemukan bentrok
        }
    }
    return -1; // tidak bentrok
}

// ========================= TAMBAH JADWAL =========================
void tambahJadwal() {
    Jadwal j;
    cout << "\nMasukkan kode mata kuliah: ";
    cin >> ws;
    getline(cin, j.kode);
    cout << "Masukkan nama mata kuliah: ";
    getline(cin, j.mataKuliah);
    cout << "Masukkan hari (Senin–Jumat): ";
    getline(cin, j.hari);
    cout << "Masukkan jam mulai (07–17): ";
    getline(cin, j.jamMulai);
    cout << "Masukkan jam selesai: ";
    getline(cin, j.jamSelesai);
    cout << "Masukkan ruangan: ";
    getline(cin, j.ruangan);

    if (!validasiHari(j.hari)) {
        cout << "❌ Input hari tidak valid. Hanya Senin–Jumat yang diterima.\n";
        return;
    }

    int jamValid = stoi(j.jamMulai.substr(0, 2)); // ambil dua digit pertama
    if (!validasiJam(jamValid)) {
        cout << "❌ Jam di luar batas (07–17).\n";
        return;
    }

    if (cariBentrok(j.hari, j.jamMulai, j.ruangan) != -1) {
        cout << "⚠️  Jadwal bentrok dengan data yang sudah ada!\n";
        return;
    }

    daftarJadwal[jumlahJadwal++] = j;
    cout << "✅ Jadwal berhasil ditambahkan!\n";
}

// ========================= URUTKAN (BUBBLE SORT) =========================
void urutkanJadwal() {
    for (int i = 0; i < jumlahJadwal - 1; i++) {
        for (int j = 0; j < jumlahJadwal - i - 1; j++) {
            if (daftarJadwal[j].ruangan > daftarJadwal[j + 1].ruangan) {
                swap(daftarJadwal[j], daftarJadwal[j + 1]);
            }
        }
    }
}

// ========================= TAMPILKAN JADWAL =========================
void tampilkanJadwal() {
    if (jumlahJadwal == 0) {
        cout << "📭 Belum ada jadwal yang tersimpan.\n";
        return;
    }

    urutkanJadwal();

    cout << left << setw(8) << "Kode"
         << setw(35) << "Mata Kuliah"
         << setw(10) << "Hari"
         << setw(8) << "Mulai"
         << setw(8) << "Selesai"
         << setw(20) << "Ruangan" << endl;
    cout << string(90, '-') << endl;

    for (int i = 0; i < jumlahJadwal; i++) {
        cout << left << setw(8) << daftarJadwal[i].kode
             << setw(35) << daftarJadwal[i].mataKuliah
             << setw(10) << daftarJadwal[i].hari
             << setw(8) << daftarJadwal[i].jamMulai
             << setw(8) << daftarJadwal[i].jamSelesai
             << setw(20) << daftarJadwal[i].ruangan << endl;
    }
}

// ========================= CEK KESEDIAAN RUANGAN =========================
void cekKetersediaan() {
    string hari, jam, ruang;
    cout << "\nMasukkan hari: ";
    cin >> ws;
    getline(cin, hari);
    cout << "Masukkan jam mulai: ";
    getline(cin, jam);
    cout << "Masukkan ruangan: ";
    getline(cin, ruang);

    int posisi = cariBentrok(hari, jam, ruang);
    if (posisi == -1)
        cout << "✅ Ruangan " << ruang << " kosong pada " << hari << " jam " << jam << endl;
    else
        cout << "❌ Ruangan " << ruang << " sedang dipakai untuk " << daftarJadwal[posisi].mataKuliah << endl;
}

// ========================= DATA AWAL (DARI KRS) =========================
void inisialisasiData() {
    Jadwal dataAwal[] = {
        {"MWK60207", "PENDIDIKAN KEWARGANEGARAAN", "Rabu", "07:30", "09:10", "RF7"},
        {"MWP60201", "ILMU PENDIDIKAN", "Rabu", "09:11", "10:51", "Theater1"},
        {"MWP60202", "PSIKOLOGI PENDIDIKAN", "Selasa", "07:30", "09:09", "R_AVA_B"},
        {"MWU60201", "BAHASA INGGRIS TUJUAN KHUSUS", "Jumat", "07:30", "09:10", "RE4"},
        {"PTF60205", "ALGORITMA PEMROGRAMAN", "Kamis", "09:11", "10:50", "R_AVA_A"},
        {"PTF60206", "PRAKTIK ALGORITMA PEMROGRAMAN", "Selasa", "14:10", "17:30", "Lab_Telekomunikasi"},
        {"PTF60213", "BASIS DATA", "Rabu", "14:14", "15:54", "RF8"},
        {"PTF60214", "PRAKTIK BASIS DATA", "Selasa", "10:51", "14:10", "Lab_SI"},
        {"PTF60215", "REKAYASA PERANGKAT LUNAK", "Kamis", "07:30", "09:10", "RF8"},
        {"PTF60216", "PRAKTIK REKAYASA PERANGKAT LUNAK", "Senin", "07:30", "10:50", "Lab_AI"},
        {"PTF60217", "INTERAKSI MANUSIA KOMPUTER", "Jumat", "14:11", "15:51", "R_AVA_B"},
        {"PTF60218", "PRAKTIK UI/UX", "Rabu", "11:31", "13:52", "Lab_SI"}};

    for (int i = 0; i < 12; i++) {
        daftarJadwal[jumlahJadwal++] = dataAwal[i];
    }
}

// ========================= MENU UTAMA =========================
void menu() {
    int pilih;
    do {
        cout << "\n===== SISTEM PENJADWALAN RUANG KULIAH =====\n";
        cout << "1. Tambah Jadwal\n";
        cout << "2. Cek Ketersediaan Ruangan\n";
        cout << "3. Tampilkan Semua Jadwal\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu (1–4): ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahJadwal(); break;
            case 2: cekKetersediaan(); break;
            case 3: tampilkanJadwal(); break;
            case 4: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 4);
}

// ========================= FUNGSI UTAMA =========================
int main() {
    inisialisasiData();
    menu();
    return 0;
}
