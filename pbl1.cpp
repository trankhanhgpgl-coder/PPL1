/* phân công 
 *
 * Ngô Nguyễn Nhựt Anh-106240311
 * nhiệm vụ
 * - docFile()      : đọc dữ liệu từ file
 * - ghiFile()      : Ghi dữ liệu ra file
 * - themSach()     : Thêm sách mới
 * - suaSach()      : Sửa thông tin sách
 * - xoaSach()      : Xóa sách
 * - sapXepTheoMa() : Sắp xếp theo mã sách
 * - Trần Xuân Khánh-106230201
 * - hienThiDS()       : Hiển thị danh sách sách
 * - timTheoTacGia()   : Tìm sách theo tên tác giả
 * - timTheoMaHoacTen(): Tìm sách theo mã hoặc tên sách
 * - locTheoNXB()      : Lọc sách theo nhà xuất bản
 * - kiemTraTinhTrang(): Kiểm tra tình trạng sách
 *
 * Cả 2 cùng làm
 * ----------------------------------------------------------------
 * - struct Sach
 * - Cac menu (menuChinh, menuThongTin, menuQuanLy, menuTienIch)
 * - ham timSach() (dung chung)

 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;
struct Sach {
    string maSach;
    string tenSach;
    string tacGia;
    string nhaXuatBan;
    int namXuatBan;
    int lanTaiBan;
    int soTrang;
    double gia;
    int soLuong;
};
Sach ds[1000];
int n = 0;
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Hàm tìm sách theo mã
int timSach(string ma) {
    for(int i = 0; i < n; i++) {
        if(ds[i].maSach == ma)
            return i;
    }
    return -1;
}

// Hàm hiển thị 1 dòng sách
void inSach(Sach s) {
    cout << left << setw(12) << s.maSach
         << setw(28) << s.tenSach
         << setw(18) << s.tacGia
         << setw(18) << s.nhaXuatBan
         << setw(8) << s.namXuatBan
         << setw(8) << s.lanTaiBan
         << setw(8) << s.soTrang
         << setw(10) << s.gia
         << setw(6) << s.soLuong << endl;
}

// ==================== FILE ====================
void docFile() {
    ifstream fileIn("thuvien.txt");
    if(!fileIn.is_open()) {
        cout << "Khong tim thay file thuvien.txt, khoi tao danh sach moi.\n";
        return;
    }
    
    n = 0;
    string line;
    while(getline(fileIn, line) && n < 1000) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1+1);
        size_t pos3 = line.find('|', pos2+1);
        size_t pos4 = line.find('|', pos3+1);
        size_t pos5 = line.find('|', pos4+1);
        size_t pos6 = line.find('|', pos5+1);
        size_t pos7 = line.find('|', pos6+1);
        size_t pos8 = line.find('|', pos7+1);
        
        if(pos8 != string::npos) {
            ds[n].maSach = line.substr(0, pos1);
            ds[n].tenSach = line.substr(pos1+1, pos2-pos1-1);
            ds[n].tacGia = line.substr(pos2+1, pos3-pos2-1);
            ds[n].nhaXuatBan = line.substr(pos3+1, pos4-pos3-1);
            ds[n].namXuatBan = stoi(line.substr(pos4+1, pos5-pos4-1));
            ds[n].lanTaiBan = stoi(line.substr(pos5+1, pos6-pos5-1));
            ds[n].soTrang = stoi(line.substr(pos6+1, pos7-pos6-1));
            ds[n].gia = stod(line.substr(pos7+1, pos8-pos7-1));
            ds[n].soLuong = stoi(line.substr(pos8+1));
            n++;
        }
    }
    fileIn.close();
    cout << "Da doc " << n << " sach tu file.\n";
}

void ghiFile() {
    ofstream fileOut("thuvien.txt");
    if(!fileOut.is_open()) {
        cout << "Loi mo file de ghi!\n";
        return;
    }
    
    for(int i = 0; i < n; i++) {
        fileOut << ds[i].maSach << "|"
                << ds[i].tenSach << "|"
                << ds[i].tacGia << "|"
                << ds[i].nhaXuatBan << "|"
                << ds[i].namXuatBan << "|"
                << ds[i].lanTaiBan << "|"
                << ds[i].soTrang << "|"
                << ds[i].gia << "|"
                << ds[i].soLuong << endl;
    }
    fileOut.close();
}

// ==================== CHUC NANG ====================
void hienThiDS() {
    clearScreen();
    if(n == 0) {
        cout << "Danh sach rong!\n";
        cout << "\nNhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "\n=====================================================================================================\n";
    cout << "                                       DANH SACH SACH TRONG THU VIEN\n";
    cout << "=======================================================================================================\n";
    cout << left << setw(12) << "Ma sach"
         << setw(28) << "Ten sach"
         << setw(18) << "Tac gia"
         << setw(18) << "NXB"
         << setw(8) << "Nam"
         << setw(8) << "Tai ban"
         << setw(8) << "Trang"
         << setw(10) << "Gia"
         << setw(6) << "SL" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        inSach(ds[i]);
    }
    cout << "----------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

void themSach() {
    clearScreen();
    if(n >= 1000) {
        cout << "Danh sach day!\n";
        return;
    }
    
    Sach s;
    cout << "\n--- THEM SACH MOI ---\n";
    cout << "Ma sach: ";
    getline(cin, s.maSach);
    
    if(timSach(s.maSach) != -1) {
        cout << "Ma sach da ton tai!\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.ignore();
        cin.get();
        return;
    }
    
    cout << "Ten sach: "; getline(cin, s.tenSach);
    cout << "Tac gia: "; getline(cin, s.tacGia);
    cout << "Nha xuat ban: "; getline(cin, s.nhaXuatBan);
    cout << "Nam xuat ban: "; cin >> s.namXuatBan;
    cout << "Lan tai ban: "; cin >> s.lanTaiBan;
    cout << "So trang: "; cin >> s.soTrang;
    cout << "Gia: "; cin >> s.gia;
    cout << "So luong: "; cin >> s.soLuong;
    cin.ignore();
    
    ds[n] = s;
    n++;
    ghiFile();
    
    cout << "\nThem sach thanh cong!\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

void suaSach() {
    clearScreen();
    string ma;
    cout << "\n--- SUA THONG TIN SACH ---\n";
    cout << "Nhap ma sach can sua: ";
    getline(cin, ma);
    
    int idx = timSach(ma);
    if(idx == -1) {
        cout << "Khong tim thay sach!\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return;
    }
    
    cout << "\nNhap thong tin moi (bo trong neu khong doi):\n";
    cout << "Ten sach (" << ds[idx].tenSach << "): ";
    string temp; getline(cin, temp);
    if(temp != "") ds[idx].tenSach = temp;
    
    cout << "Tac gia (" << ds[idx].tacGia << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].tacGia = temp;
    
    cout << "Nha xuat ban (" << ds[idx].nhaXuatBan << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].nhaXuatBan = temp;
    
    cout << "Nam xuat ban (" << ds[idx].namXuatBan << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].namXuatBan = stoi(temp);
    
    cout << "Lan tai ban (" << ds[idx].lanTaiBan << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].lanTaiBan = stoi(temp);
    
    cout << "So trang (" << ds[idx].soTrang << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].soTrang = stoi(temp);
    
    cout << "Gia (" << ds[idx].gia << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].gia = stod(temp);
    
    cout << "So luong (" << ds[idx].soLuong << "): ";
    getline(cin, temp);
    if(temp != "") ds[idx].soLuong = stoi(temp);
    
    ghiFile();
    cout << "\nSua thong tin thanh cong!\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

void xoaSach() {
    clearScreen();
    string ma;
    cout << "\n--- XOA SACH ---\n";
    cout << "Nhap ma sach can xoa: ";
    getline(cin, ma);
    
    int idx = timSach(ma);
    if(idx == -1) {
        cout << "Khong tim thay sach!\n";
        cout << "Nhan Enter de tiep tuc...";
        cin.get();
        return;
    }
    
    for(int i = idx; i < n-1; i++) {
        ds[i] = ds[i+1];
    }
    n--;
    ghiFile();
    
    cout << "\nXoa sach thanh cong!\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

void sapXepTheoMa() {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(ds[i].maSach > ds[j].maSach) {
                Sach temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
    ghiFile();
    cout << "\nDa sap xep danh sach theo ma sach!\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
    hienThiDS();
}

void timTheoTacGia() {
    clearScreen();
    string tg;
    cout << "\n--- TIM SACH THEO TAC GIA ---\n";
    cout << "Nhap ten tac gia: ";
    getline(cin, tg);
    
    bool timThay = false;
    cout << "\nKet qua tim kiem:\n";
    cout << left << setw(12) << "Ma sach" << setw(30) << "Ten sach" << setw(20) << "Tac gia" << endl;
    cout << "--------------------------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        if(ds[i].tacGia == tg) {
            cout << left << setw(12) << ds[i].maSach
                 << setw(30) << ds[i].tenSach
                 << setw(20) << ds[i].tacGia << endl;
            timThay = true;
        }
    }
    
    if(!timThay) {
        cout << "Khong tim thay sach cua tac gia " << tg << endl;
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void timTheoMaHoacTen() {
    clearScreen();
    string kw;
    cout << "\n--- TIM SACH THEO MA HOAC TEN ---\n";
    cout << "Nhap ma sach hoac ten sach: ";
    getline(cin, kw);
    
    bool timThay = false;
    cout << "\nKet qua tim kiem:\n";
    cout << left << setw(12) << "Ma sach" << setw(35) << "Ten sach" << setw(15) << "So luong" << endl;
    cout << "--------------------------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        string tenSach = ds[i].tenSach;
        for(int j = 0; j < tenSach.length(); j++) tenSach[j] = tolower(tenSach[j]);
        string kwLower = kw;
        for(int j = 0; j < kwLower.length(); j++) kwLower[j] = tolower(kwLower[j]);
        
        if(ds[i].maSach == kw || tenSach.find(kwLower) != string::npos) {
            cout << left << setw(12) << ds[i].maSach
                 << setw(35) << ds[i].tenSach
                 << setw(15) << ds[i].soLuong << endl;
            timThay = true;
        }
    }
    
    if(!timThay) {
        cout << "Khong tim thay sach nao!\n";
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void locTheoNXB() {
    clearScreen();
    string nxb;
    cout << "\n--- LOC SACH THEO NHA XUAT BAN ---\n";
    cout << "Nhap ten nha xuat ban: ";
    getline(cin, nxb);
    
    bool timThay = false;
    cout << "\nSach cua nha xuat ban " << nxb << ":\n";
    cout << left << setw(12) << "Ma sach" << setw(35) << "Ten sach" << setw(18) << "Tac gia" << endl;
    cout << "--------------------------------------------------------------\n";
    
    for(int i = 0; i < n; i++) {
        if(ds[i].nhaXuatBan == nxb) {
            cout << left << setw(12) << ds[i].maSach
                 << setw(35) << ds[i].tenSach
                 << setw(18) << ds[i].tacGia << endl;
            timThay = true;
        }
    }
    
    if(!timThay) {
        cout << "Khong co sach cua nha xuat ban nay!\n";
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

void kiemTraTinhTrang() {
    clearScreen();
    string ma;
    cout << "\n--- KIEM TRA TINH TRANG SACH ---\n";
    cout << "Nhap ma sach: ";
    getline(cin, ma);
    
    int idx = timSach(ma);
    if(idx == -1) {
        cout << "Khong tim thay sach!\n";
    } else {
        cout << "\n========== THONG TIN SACH ==========\n";
        cout << "Ma sach: " << ds[idx].maSach << endl;
        cout << "Ten sach: " << ds[idx].tenSach << endl;
        cout << "So luong con: " << ds[idx].soLuong << endl;
        cout << "Tinh trang: ";
        if(ds[idx].soLuong == 0) {
            cout << "DA DUOC MUON HET!\n";
        } else {
            cout << "CON " << ds[idx].soLuong << " CUON\n";
        }
        cout << "====================================\n";
    }
    
    cout << "\nNhan Enter de tiep tuc...";
    cin.get();
}

// ==================== MENU ====================
void menuThongTin() {
    int chon;
    do {
        clearScreen();
        cout << "\n====================================\n";
        cout << "         THONG TIN SACH\n";
        cout << "====================================\n";
        cout << "   1. Hien thi danh sach sach\n";
        cout << "   0. Quay lai\n";
        cout << "====================================\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();
        
        if(chon == 1) hienThiDS();
        else if(chon != 0) cout << "Chon sai!\n";
    } while(chon != 0);
}

void menuQuanLy() {
    int chon;
    do {
        clearScreen();
        cout << "\n====================================\n";
        cout << "         QUAN LY TRANG THAI\n";
        cout << "====================================\n";
        cout << "   1. Cap nhat thong tin sach\n";
        cout << "   2. Them sach moi\n";
        cout << "   3. Xoa sach\n";
        cout << "   4. Sap xep theo ma sach\n";
        cout << "   0. Quay lai\n";
        cout << "====================================\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();
        
        switch(chon) {
            case 1: suaSach(); break;
            case 2: themSach(); break;
            case 3: xoaSach(); break;
            case 4: sapXepTheoMa(); break;
            case 0: break;
            default: cout << "Chon sai!\n";
        }
    } while(chon != 0);
}

void menuTienIch() {
    int chon;
    do {
        clearScreen();
        cout << "\n====================================\n";
        cout << "           TIEN ICH\n";
        cout << "====================================\n";
        cout << "   1. Tim sach theo tac gia\n";
        cout << "   2. Tim sach theo ma/ten sach\n";
        cout << "   3. Loc sach theo nha xuat ban\n";
        cout << "   4. Kiem tra tinh trang sach\n";
        cout << "   0. Quay lai\n";
        cout << "====================================\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();
        
        switch(chon) {
            case 1: timTheoTacGia(); break;
            case 2: timTheoMaHoacTen(); break;
            case 3: locTheoNXB(); break;
            case 4: kiemTraTinhTrang(); break;
            case 0: break;
            default: cout << "Chon sai!\n";
        }
    } while(chon != 0);
}

void menuChinh() {
    int chon;
    do {
        clearScreen();
        cout << "\n============================================\n";
        cout << "     CHUONG TRINH QUAN LY THU VIEN\n";
        cout << "============================================\n";
        cout << "   1. Menu thong tin sach\n";
        cout << "   2. Menu quan ly trang thai\n";
        cout << "   3. Menu tien ich\n";
        cout << "   0. Thoat\n";
        cout << "============================================\n";
        cout << "Chon: ";
        cin >> chon;
        cin.ignore();
        
        switch(chon) {
            case 1: menuThongTin(); break;
            case 2: menuQuanLy(); break;
            case 3: menuTienIch(); break;
            case 0: 
                cout << "\nCam on ban da su dung chuong trinh!\n";
                break;
            default: cout << "Chon sai!\n";
        }
    } while(chon != 0);
}

int main() {
    docFile();
    menuChinh();
    ghiFile();
    return 0;
}