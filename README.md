# Program Hidrolisis Garam
ditujukan untuk memenuhi tugas mata kuliah struktur data dan algoritma

```mermaid
    flowchart TD
    A([Start]) --> B[Baca tabel_periodik.txt]
    B --> C[Muat data ke array (element.c)]
    C --> D[Tampilkan Menu Utama]
    D --> |1. Tampilkan Tabel Periodik| E[Tampilkan data dari array]
    D --> |2. Cari Elemen| F[Input kriteria pencarian]
    F --> G[Cari di BST]
    G --> |Ditemukan| H[Tampilkan konfigurasi elektron]
    G --> |Tidak ditemukan| I[Error: Unsur tidak ada]
    H --> J[Push ke Stack (History)]
    D --> |3. Gabungkan Garam| K[Input kation & anion]
    K --> L[Cek di daftar_garam.c]
    L --> |Valid| M[Tampilkan hasil & reaksi]
    L --> |Tidak valid| N[Error: Kombinasi tidak valid]
    M --> O[Push ke Stack & Enqueue ke Queue]
    D --> |4. Tampilkan History| P[Pop dari Stack]
    D --> |5. Tampilkan Proses| Q[Dequeue dari Queue]
    D --> |6. Keluar| R([End])