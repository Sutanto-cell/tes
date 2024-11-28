/**************************************************************************************************
 * Kelompok 3 from A1
 * Sutanto
 * Naulia Situmeang
 * Sofwan Alhawari
 * Firdauszy Melati
 * Qiara Azqiya
 * Rania
 * Project Dasar Pemrograman untuk Pemenuhan Tugas Besar 
 * Goals : bisa menampilkan data mahasiswa, dan menambahkan datanya.
 *         Datanya gabole ilang kalo misal programnya udha selesai (Disimpan ke file).
 *         Selebihnya kalo kalian mau buat gimana bebas sesuka hati kalian!!!
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Struktur Data Mahasiswa
struct Data
{
    int id;             
    int umur;           
    char nama[50];      
    char nim[15];       
    char hobi[50];      
    char cita_cita[50]; 
};

// Variabel global
struct Data hehe; // Data mahasiswa yang akan diinput
char nitip[200];  // Buffer untuk menyimpan input pengguna

void tambahData()
{
    FILE *file = fopen("stress.txt", "a"); 
    int i;
    if (!file) // Jika file gagal dibuka, keluar dari fungsi
    {
        printf("Gagal membuka file!\n");
        return; 
    }

    // Loop untuk meminta input sampai data valid
    while (1)
    {   
        flag: // Label untuk pengulangan input jika terjadi kesalahan
        int valid = 1;  // Menetapkan nilai awal valid dalam setiap iterasi, Variabel untuk menandakan validitas input
        printf("Masukkan Data (ID/Nama/NIM/Hobi/Cita_cita/Umur): ");
        fgets(nitip, sizeof(nitip), stdin); // Membaca input satu baris

        // Memparse input dengan format ID/Nama/NIM/Hobi/Cita_cita/Umur
        if (sscanf(nitip, "%d/%49[^/]/%14[^/]/%49[^/]/%49[^/]/%d",
                   &hehe.id, hehe.nama, hehe.nim, hehe.hobi, hehe.cita_cita, &hehe.umur) == 6)
        {   
            // Validasi Nama (hanya boleh huruf dan spasi)
            for (i = 0; hehe.nama[i] != '\0'; i++){
                if (!isalpha(hehe.nama[i]) && !isspace(hehe.nama[i])){
                    valid = 0; // Nama tidak valid
                    break;
                }
            }
            if (valid == 0){
                printf("\033[1;31m"); // Merah untuk kesalahan
                printf("Nama Ga boleh ada angka DEKSS\n");
                printf("\033[0m");
                goto flag; // Kembali ke tempat tertanda
            }

            // Validasi NIM (hanya boleh angka)
            for (i = 0; hehe.nim[i] !='\0'; i++) {
                if (!isdigit(hehe.nim[i]))
                {
                    valid = 0; // NIM tidak valid
                    break;
                }
            }

            if (!valid){
                printf("\033[1;31m"); 
                printf("NIM angka doang deks\n");
                printf("\033[0m");
                goto flag; 
            }

            // Validasi Umur (harus lebih besar dari 0)
            if (hehe.umur <= 0){
                printf("\033[1;31m");
                printf("Umur harus lebih dari 0 ya deks\n");
                printf("\033[0m");
                goto flag; 
            }
        break; // Jika semua validasi lulus, keluar dari loop
        }
        else
        {
            // Jika format input salah
            printf("\033[1;31m");
            printf("Format input salah!\nHarus menggunakan format: Id/Nama/NIM/Hobi/Cita_cita/Umur\n");
            printf("\033[0m");
        }
    }

    // Menyimpan data ke dalam file
    fprintf(file, "%d/%s/%s/%s/%s/%d\n", hehe.id, hehe.nama, hehe.nim, hehe.hobi, hehe.cita_cita, hehe.umur);
    printf("\033[1;32m");
    printf("Data berhasil ditambahkan!\n");
    printf("\033[0m");
    fclose(file);    
    system("pause"); 
}


void tampilkanData()
{
    FILE *file = fopen("stress.txt", "r"); 

    if (!file)
    {
        printf("File tidak ditemukan atau kosong!\n");
        return; 
    }

    // Menampilkan header tabel
    printf("Data saat ini:\n");
    printf("\033[1;33m");
    printf("ID\tNama\t\t\t\tNIM\t\tHobi\t\tCita-cita\tUmur\n");
    printf("\033[0m");
    printf("\033[1;90m");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("\033[0m");

    while (fgets(nitip, sizeof(nitip), file) != NULL)
    {
        // Menggunakan sscanf untuk memparse setiap baris
        if (sscanf(nitip, "%d/%49[^/]/%14[^/]/%49[^/]/%49[^/]/%d", &hehe.id, hehe.nama, hehe.nim, hehe.hobi, hehe.cita_cita, &hehe.umur) == 6)
        {
            // Menampilkan data mahasiswa
            printf("\033[1;32m");
            printf("%d\t%-25.25s\t%-10.10s\t%-10.10s\t%-15.15s\t%d\n", hehe.id, hehe.nama, hehe.nim, hehe.hobi, hehe.cita_cita, hehe.umur);
            printf("\033[0m");
        }
    }

    fclose(file);  
    system("pause"); 
}

// Fungsi utama program
int main()
{
    int pilihan;

    // Loop utama untuk menampilkan menu
    do
    {
        printf("\033[4;90mMenu:\033[0m\n");
        printf("\033[1;95m"); 
        printf("1. Tambah Data\n");
        printf("2. Tampilkan Data\n");
        printf("3. Keluar\n");
        printf("\033[0m");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        getchar(); // Membersihkan buffer input setelah scanf

        switch (pilihan)
        {
        case 1:
            tambahData(); // Memanggil fungsi untuk menambah data
            break;
        case 2:
            tampilkanData(); // Memanggil fungsi untuk menampilkan data
            break;
        case 3:
            printf("Keluar program.\n"); // Keluar dari program
            break;
        default:
            printf("Pilihan tidak valid!\n"); // Menangani input tidak valid
        }
    } while (pilihan != 3); // Ulangi menu hingga pengguna memilih keluar

    return 0;
}
