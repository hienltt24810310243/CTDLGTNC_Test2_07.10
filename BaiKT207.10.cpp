#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct NgaySinh {
    int ngay;
    int thang;
    int nam;
};

struct NhanVien {
    int maNV;
    string hoTen;
    NgaySinh ngaySinh;
    double luong;
};

void nhapDanhSach(NhanVien a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "\n--- Nhan vien thu " << i + 1 << " ---\n";
        cout << "Ma nhan vien: ";
        cin >> a[i].maNV;
        cin.ignore();
        cout << "Ho ten: ";
        getline(cin, a[i].hoTen);
        cout << "Ngay sinh (ngay thang nam): ";
        cin >> a[i].ngaySinh.ngay >> a[i].ngaySinh.thang >> a[i].ngaySinh.nam;
        cout << "Luong (trieu dong): ";
        cin >> a[i].luong;
    }
}

void xuatTieuDe() {
    cout << left << setw(10) << "Ma NV"
         << setw(25) << "Ho ten"
         << setw(15) << "Ngay sinh"
         << setw(15) << "Luong (trieu)" << endl;
    cout << string(65, '-') << endl;
}

void xuatMotNhanVien(const NhanVien &nv) {
    cout << left << setw(10) << nv.maNV
         << setw(25) << nv.hoTen;

    int doDai = 2 + 4;
    if (nv.ngaySinh.ngay >= 10) doDai += 2; else doDai += 1;
    if (nv.ngaySinh.thang >= 10) doDai += 2; else doDai += 1;

    cout << nv.ngaySinh.ngay << "/" << nv.ngaySinh.thang << "/" << nv.ngaySinh.nam;
    for (int i = doDai; i < 15; i++) cout << " ";

    cout << fixed << setprecision(2) << nv.luong << endl;
}

void xuatDanhSach(NhanVien a[], int n) {
    xuatTieuDe();
    for (int i = 0; i < n; i++) {
        xuatMotNhanVien(a[i]);
    }
}

void bubbleSort(NhanVien a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].luong > a[j + 1].luong) {
                NhanVien tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

int timKiemNhiPhan(NhanVien a[], int left, int right, double x) {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (a[mid].luong == x) return mid;
    if (a[mid].luong > x) return timKiemNhiPhan(a, left, mid - 1, x);
    return timKiemNhiPhan(a, mid + 1, right, x);
}

void timNhanVienTheoLuong(NhanVien a[], int n, double x) {
    int pos = timKiemNhiPhan(a, 0, n - 1, x);
    if (pos == -1) {
        cout << "Khong tim thay nhan vien nao co luong = " << x << endl;
        return;
    }
    int l = pos, r = pos;
    while (l - 1 >= 0 && a[l - 1].luong == x) l--;
    while (r + 1 < n && a[r + 1].luong == x) r++;

    cout << "Cac nhan vien co luong = " << x << " trieu:\n";
    xuatTieuDe();
    for (int i = l; i <= r; i++) {
        xuatMotNhanVien(a[i]);
    }
}

int main() {
    int n;
    do {
        cout << "Nhap so luong nhan vien n: ";
        cin >> n;
    } while (n <= 0 || n > 1000);

    NhanVien a[1000];

    nhapDanhSach(a, n);
    cout << "\n===== DANH SACH NHAN VIEN VUA NHAP =====\n";
    xuatDanhSach(a, n);

    bubbleSort(a, n);
    cout << "\n===== DANH SACH SAU KHI SAP XEP TANG DAN THEO LUONG =====\n";
    xuatDanhSach(a, n);

    double x;
    cout << "\nNhap luong X can tim (trieu dong): ";
    cin >> x;
    cout << endl;
    timNhanVienTheoLuong(a, n, x);

    return 0;
}
