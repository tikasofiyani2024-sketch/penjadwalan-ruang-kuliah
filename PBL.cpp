#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ========================= ARRAY 1D (array of struct) =========================
struct Jadwal {
    string kode;
    string mataKuliah;
    string hari;
    string jamMulai;
    string jamSelesai;
    string ruangan;
};

const int MAKS_JADWAL = 50;
Jadwal daftarJadwal[MAKS_JADWAL]; // <-- ARRAY 1D
int jumlahJadwal = 0;

// ========================= FUNGSI VALIDASI (Modular) =========================
bool validasiHari(string hari) {
    string daftarHari[5] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"}; // array 1D kecil
    for (int i = 0; i < 5; i++) {   // loop for
        if (hari == daftarHari[i]) return true;
    }
    return false;
}

bool validasiJam(int jam) { 
    return (jam >= 7 && jam <= 17); 
}

// ========================= FUNGSI PENCARIAN BENTROK =========================
int cariBentrok(string hari, string jamMulai, string ruangan) {
    for (int i = 0; i < jumlahJadwal; i++) { // loop for
        if (daftarJadwal[i].hari == hari &&
            daftarJadwal[i].jamMulai == jamMulai &&
            daftarJadwal[i].ruangan == ruangan)
            return i;
    }
    return -1;
}

// ========================= INPUT DATA (Modular) =========================
void tambahJadwal() {
    Jadwal j;
    cout << "\nMasukkan kode mata kuliah: ";
    cin >> ws;
    getline(cin, j.kode);

    cout << "Masukkan nama mata kuliah: ";
    getline(cin, j.mataKuliah);

    cout << "Masukkan hari (Senin–Jumat): ";
    getline(cin, j.hari);

    // VALIDASI HARI
    if (!validasiHari(j.hari)) {
        cout << "[ERROR] Input hari tidak valid. Hanya hari Senin sampai Jumat yang diizinkan.\n";
        return;
    }

    cout << "Masukkan jam mulai (07–17): ";
    getline(cin, j.jamMulai);

    cout << "Masukkan jam selesai: ";
    getline(cin, j.jamSelesai);

    cout << "Masukkan ruangan: ";
    getline(cin, j.ruangan);

    // VALIDASI JAM
    int jamMulaiJam = stoi(j.jamMulai.substr(0, 2));
    int jamMulaiMenit = stoi(j.jamMulai.substr(3, 2));
    int jamSelesaiJam = stoi(j.jamSelesai.substr(0, 2));
    int jamSelesaiMenit = stoi(j.jamSelesai.substr(3, 2));

    bool jamValid = true;
    if (jamMulaiMenit >= 60 || jamSelesaiMenit >= 60) jamValid = false;
    if (!validasiJam(jamMulaiJam)) jamValid = false;

    if (!jamValid) {
        cout << "[ERROR] Format jam tidak valid. Menit max 59 & jam mulai harus 07–17.\n";
        return;
    }

    // CEK BENTROK (Modular)
    if (cariBentrok(j.hari, j.jamMulai, j.ruangan) != -1) {
        cout << "[WARNING] Jadwal bentrok.\n";
        return;
    }

    daftarJadwal[jumlahJadwal++] = j;
    cout << "[SUCCESS] Jadwal berhasil ditambahkan.\n";
}

// ========================= FUNGSI URUT HARI =========================
int urutanHari(string hari) {
    string daftarHari[5] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat"};
    for (int i = 0; i < 5; i++) {
        if (hari == daftarHari[i]) return i;
    }
    return 999;
}

// ========================= BUBBLE SORT =========================
void urutkanJadwal() {
    for (int i = 0; i < jumlahJadwal - 1; i++) {          // loop luar bubble sort
        for (int j = 0; j < jumlahJadwal - i - 1; j++) {  // loop dalam bubble sort

            int hariA = urutanHari(daftarJadwal[j].hari);
            int hariB = urutanHari(daftarJadwal[j + 1].hari);

            // urut berdasarkan hari
            if (hariA > hariB) {
                swap(daftarJadwal[j], daftarJadwal[j + 1]);
            }
            // jika hari sama → urutkan berdasarkan jam
            else if (hariA == hariB) {
                if (daftarJadwal[j].jamMulai > daftarJadwal[j + 1].jamMulai) {
                    swap(daftarJadwal[j], daftarJadwal[j + 1]);
                }
            }
        }
    }
}

// ========================= TAMPILKAN DATA =========================
void tampilkanJadwal() {
    if (jumlahJadwal == 0) {
        cout << "[INFO] Belum ada jadwal yang tersimpan.\n";
        return;
    }

    urutkanJadwal(); // panggil bubble sort

    cout << left << setw(8) << "Kode"
         << setw(35) << "Mata Kuliah"
         << setw(10) << "Hari"
         << setw(8) << "Mulai"
         << setw(8) << "Selesai"
         << setw(20) << "Ruangan" << endl;
    cout << string(90, '-') << endl;

    for (int i = 0; i < jumlahJadwal; i++) { // loop for
        cout << left
             << setw(9) << (daftarJadwal[i].kode + "  ")
             << setw(35) << daftarJadwal[i].mataKuliah
             << setw(10) << daftarJadwal[i].hari
             << setw(8) << daftarJadwal[i].jamMulai
             << setw(8) << daftarJadwal[i].jamSelesai
             << setw(20) << daftarJadwal[i].ruangan
             << endl;
    }
}

// ========================= HAPUS (Shifting Array 1D) =========================
void hapusJadwal() {
    if (jumlahJadwal == 0) {
        cout << "[INFO] Tidak ada jadwal yang bisa dihapus.\n";
        return;
    }

    string kodeHapus;
    cout << "\nMasukkan kode mata kuliah yang ingin dihapus: ";
    cin >> ws;
    getline(cin, kodeHapus);

    bool ditemukan = false;

    for (int i = 0; i < jumlahJadwal; i++) { // loop pencarian
        if (daftarJadwal[i].kode == kodeHapus) {
            ditemukan = true;

            // SHIFTING ARRAY 1D
            for (int j = i; j < jumlahJadwal - 1; j++) {
                daftarJadwal[j] = daftarJadwal[j + 1];
            }

            jumlahJadwal--;
            cout << "[SUCCESS] Jadwal dengan kode " << kodeHapus << " berhasil dihapus.\n";
            break;
        }
    }

    if (!ditemukan)
        cout << "[WARNING] Jadwal dengan kode tersebut tidak ditemukan.";
}

// ========================= CEK KETERSEDIAAN =========================
void cekKetersediaan() {
    string hari, jam, ruang;

    cout << "\nMasukkan hari: ";
    cin >> ws;
    getline(cin, hari);

    cout << "Masukkan jam mulai: ";
    getline(cin, jam);

    cout << "Masukkan ruangan: ";
    getline(cin, ruang);

    if (hari.empty() || jam.empty() || ruang.empty()) {
        cout << "[ERORR], Mohon isi lengkap.\n";
        return;
    }

    int posisi = cariBentrok(hari, jam, ruang);

    if (posisi == -1)
        cout << "[INFO] Ruangan kosong.\n";
    else
        cout << "[INFO] Ruangan digunakan untuk " << daftarJadwal[posisi].mataKuliah << endl;
}

// ========================= DATA AWAL =========================
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
        {"PTF60218", "PRAKTIK UI/UX", "Rabu", "11:31", "13:52", "Lab_SI"}
    };

    for (int i = 0; i < 12; i++) {
        daftarJadwal[jumlahJadwal++] = dataAwal[i];
    }
}

// ========================= MENU (do-while) =========================
void menu() {
    int pilih;
    do { // DO-WHILE LOOP
        cout << "\n===== Sistem Pengecekan Ruangan Kelas Berdasarkan Hari dan Jam =====\n";
        cout << "1. Tambah Jadwal\n";
        cout << "2. Cek Ketersediaan Ruangan\n";
        cout << "3. Tampilkan Semua Jadwal\n";
        cout << "4. Hapus Jadwal\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilih;

         (pilih) {
            case 1: tambahJadwal(); break;
            case 2: cekKetersediaan(); break;
            case 3: tampilkanJadwal(); break;
            case 4: hapusJadwal(); break;
            case 5:
                char yakin;
                cout << "Yakin keluar? (y/n): ";
                cin >> yakin;
                if (yakin == 'y' || yakin == 'Y') {
                    cout << "Program selesai.\n";
                } else pilih = 0;
                break;
            default: 
                cout << "[ERROR] Pilihan tidak valid.\n";
        }
    } while (pilih != 5);
}

// ========================= MAIN =========================
int main() {
    inisialisasiData(); // (Modular)
    menu();
    return 0;switch
}
