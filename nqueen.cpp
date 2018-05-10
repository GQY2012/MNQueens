#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <queue>
#include <Windows.h>

using namespace std;

int N, M;

boolean queen(int*,int);
boolean conflictCheck(int*,int,int);

int main() {
	const char *pathInput = "C:/Users/95850/Desktop/Mine/��ҵ/�˹����ܻ���/PB15111650_������_ʵ��һ/N�ʺ�/input.txt";
	freopen(pathInput, "r", stdin);//�ض�����������ָ���ļ�
	scanf("%d %d", &N, &M);
	freopen("CON", "r", stdin);//�ض�����������windows����̨
	int *chess = new int[N];	//chess[i]��ʾ��i�лʺ��λ��
	if (queen(chess, 0)) {
		for (int i = 0;i < N;i++)
			cout << chess[i] << endl;
	}

	system("pause");
	return 0;
}

boolean conflictCheck(int *chess,int row,int col) {
	for (int i = 0;i < row;i++) {
		if (chess[i] == col || abs(row - i) == abs(col - chess[i]))
			return false;
	}
	return true;
}

boolean queen(int*chess,int row) {
	if (row == N) {
		return true;
	}
	else {
		for (int j = 0;j < N;j++) {
			if (conflictCheck(chess, row, j)) {
				chess[row] = j;
			//	cout << row << " " << j << endl;
				if (queen(chess, row + 1))
					return true;
			}
		}
	}
	return false;
}

