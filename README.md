# Program Sistem Operasi Kimia
Sistem operasi kimia adalah program berbasis konsol/terminal yang dirancang untuk membantu pengguna dalam mempelajari dan mengelola informasi kimia, khususnya tabel periodik, reaksi hidrolisis garam, dan kombinasi garam. Program ini menyediakan fungsi untuk menampilkan tabel periodik, mencari elemen berdasarkan nomor atom atau simbol, mengelola daftar garam, melakukan analisis reaksi hidrolisis, dan kombinasi antar garam.

Repositori ini berisi program C untuk:
- Menampilkan dan mencari data tabel periodik unsur kimia
- Visualisasi konfigurasi elektron (termasuk pohon orbital)
- Mengelola daftar garam dan proses hidrolisis
- Kalkulator massa molar relatif senyawa
- Fitur stack (history operasi) dan queue (antrian proses)
- Database Ka/Kb asam-basa
- Struktur data: array, linked list, binary search tree, stack, queue

## Struktur Berkas
- **element.c/h**: Manajemen data unsur kimia (tabel periodik, pencarian, parsing senyawa, massa molar)
- **chem_tree.c/h**: Struktur pohon BST untuk tabel periodik
- **electron_config.c/h**: Visualisasi dan perhitungan konfigurasi elektron
- **salt.c/h**: Manajemen daftar garam (linked list)
- **hidrolisis.c/h**: Proses hidrolisis garam dan perhitungan pH
- **db_ph.c/h**: Database Ka/Kb asam-basa
- **stack.c/h**: Stack untuk riwayat operasi
- **queue.c/h**: Queue untuk antrian proses
- **main.c**: Menu utama dan integrasi seluruh fitur
- **tabel_Periodik.txt**: Data tabel periodik unsur
- **Daftar_Garam.txt**: Data garam
- **ph.txt**: Data Ka/Kb asam-basa

## Flowchart Program

```mermaid
flowchart TD
    A([Start]) --> B[Inisialisasi: Baca tabel periodik, garam, Ka/Kb, stack, queue]
    B --> C{Menu Utama}
    C -->|1. Tampilkan Tabel Periodik| D[Tampilkan seluruh unsur]
    C -->|2. Tampilkan BST| E[Tampilkan tabel periodik (BST)]
    C -->|3. Cari Unsur (No Atom)| F[Cari & tampilkan unsur berdasarkan nomor atom]
    C -->|4. Cari Unsur (Simbol)| G[Cari & tampilkan unsur berdasarkan simbol]
    C -->|5. Konfigurasi Elektron| H[Tampilkan konfigurasi elektron & visualisasi tree]
    C -->|6. Daftar Garam & Hidrolisis| I[Tampilkan daftar garam & proses hidrolisis]
    C -->|7. History Operasi| J[Tampilkan riwayat operasi (stack)]
    C -->|8. Queue Proses| K[Tampilkan antrian proses (queue)]
    C -->|9. Kalkulator Massa Molar| L[Hitung massa molar dua senyawa]
    C -->|0. Keluar| M([Selesai])
    D --> C
    E --> C
    F --> C
    G --> C
    H --> C
    I --> C
    J --> C
    K --> C
    L --> C
```

## Cara Kompilasi
```sh
gcc *.c -o program
```

## Cara Menjalankan
```sh
./program
```

---

**Catatan:**  
Pastikan file data (`tabel_Periodik.txt`, `Daftar_Garam.txt`, `ph.txt`) berada di direktori yang sama dengan program.

---

# Kontributor

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/vermilion10">
        <img src="https://avatars.githubusercontent.com/u/180294769?s=64&v=4" width="80" alt="Fathin"/><br>
        <sub><b>241524041<br> Fathin Yassarahman</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Aang-657">
        <img src="https://avatars.githubusercontent.com/u/188796947?s=64&v=4" width="80" alt="Gilang"/><br>
        <sub><b>241524044<br> Gilang Maulana</b></sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/Dyooooou">
        <img src="https://avatars.githubusercontent.com/u/188276434?s=64&v=4" width="80" alt="Julian"/><br>
        <sub><b>241524049<br> Julian Dio Saputra</b></sub>
      </a>
    </td>
  </tr>
</table>
