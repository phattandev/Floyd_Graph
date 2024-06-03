#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

const int MAX = 20;

struct Node {
	int dinhKe;
	int trongSo;
	Node* link;
};

struct MaTranKe {
	int mtk[MAX][MAX];
	int soDinh;
};

struct DanhSachKe {
	Node* dsk[MAX];
	int soDinh;
};

bool docMaTranKe(const char* file, MaTranKe& mt) {
	FILE* f = fopen(file, "rt");
	if (f == NULL) return false;
	fscanf(f, "%d", &mt.soDinh);
	for (int i = 0; i < mt.soDinh; i++) {
		for (int j = 0; j < mt.soDinh; j++) {
			fscanf(f, "%d", &mt.mtk[i][j]);
		}
	}
	fclose(f);
	return true;
}

void xuatMaTranKe(MaTranKe mt) {
	for (int i = 0; i < mt.soDinh; i++)
	{
		cout << endl;
		for (int j = 0; j < mt.soDinh; j++) {
			cout << mt.mtk[i][j] << " ";
		}
	}
}

bool docDanhSach(const char* fileName, DanhSachKe& ds) {
	FILE* f = fopen(fileName, "rt");
	if (f == NULL)
		return false;

	for (int i = 0; i < MAX; i++)
	{
		ds.dsk[i] = NULL;
	}

	fscanf(f, "%d", &ds.soDinh);

	for (int i = 0; i < ds.soDinh; i++)
	{
		int soDinhKe;
		fscanf(f, "%d", &soDinhKe);
		for (int j = 0; j < soDinhKe; j++)
		{
			Node* p = new Node;
			fscanf(f, "%d%d", &p->dinhKe, &p->trongSo);
			p->link = NULL;
			if (ds.dsk[i] == NULL)
				ds.dsk[i] = p;
			else {
				Node* t = ds.dsk[i];
				while (t->link != NULL) {
					t = t->link;
				}
				t->link = p;
			}
		}
	}
	fclose(f);
	return true;
}

void xuatDanhSach(DanhSachKe ds) {
	for (int i = 0; i < ds.soDinh; i++)
	{
		cout << "\n(" << i << "): ";
		Node* p = ds.dsk[i];
		while (p != NULL) {
			cout << "(" << p->dinhKe << "," << p->trongSo << ")" << " ";
			p = p->link;
		}
	}
}



void Floyd(MaTranKe mt) {
	int khoangCach[MAX][MAX]; //Ma trận khoảng cách lưu duong di ngắn nhất giữa các cặp đỉnh
	int dinhTrungGian[MAX][MAX]; //Ma trận đỉnh lưu các đỉnh trung gian trên đường mà các cặp đỉnh phải đi qua để có đường đi ngắn nhất

	for (int i = 0; i < mt.soDinh; i++)
	{
		for (int j = 0; j < mt.soDinh; j++)
		{
			//Ma trận khoangCach được khởi tạo dựa trên ma trận đầu vào
			khoangCach[i][j] = mt.mtk[i][j];

			//Ma trận đỉnh trung gian khởi tạo với *phần tử trong ma trận là đỉnh hiện tại tương ứng* mà KO đụng đến đường chéo chính (phần từ đường chéo chính <0> sẽ là -1)
			//VD {
			//   {-1     0	  0	   0	0}   i = 0
			//	 { 1	-1    1    1    1}   i = 1
			//   { 2	 2   -1    2    2}   i = 2
			//   { 3	 3    3   -1    3}   i = 3
			//   { 4	 4    4    4   -1}   i = 4
			//
			if (mt.mtk[i][j] != 0 && i != j )
				dinhTrungGian[i][j] = i;
			else
				dinhTrungGian[i][j] = -1;
		}
	}

	//FLoy
	for (int k = 0; k < mt.soDinh; k++)
	{
		for (int i = 0; i < mt.soDinh; i++)
		{
			for (int j = 0; j < mt.soDinh; j++)
			{
				if (khoangCach[i][j] > khoangCach[i][k] + khoangCach[k][j]) {
					khoangCach[i][j] = khoangCach[i][k] + khoangCach[k][j];
					dinhTrungGian[i][j] = i;
				}
			}
		}
	}

	cout << "\n\nMa tran duong di ngan nhat: ";
	for (int i = 0; i < mt.soDinh; i++)
	{
		cout << endl;
		for (int j = 0; j < mt.soDinh; j++)
		{
			cout << khoangCach[i][j] << " ";
		}
	}

	cout << "\n\nMa tran dinh trung gian: ";
	for (int i = 0; i < mt.soDinh; i++)
	{
		cout << endl;
		for (int j = 0; j < mt.soDinh; j++)
		{
			cout << dinhTrungGian[i][j] << " ";
		}
	}
}

int main() {
	
	MaTranKe MTK_Co_Huong;
	if (docMaTranKe("MTK_Co_Huong.txt", MTK_Co_Huong)) {
		cout << "MA TRAN KE CO HUONG: ";
		xuatMaTranKe(MTK_Co_Huong);

		Floyd(MTK_Co_Huong);
	}


	cout << "\n\n";
	return 0;
}