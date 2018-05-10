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
	const char *pathInput = "C:/Users/95850/Desktop/Mine/作业/人工智能基础/PB15111650_郭秋洋_实验一/N皇后/input.txt";
	freopen(pathInput, "r", stdin);//重定向输入流到指定文件
	scanf("%d %d", &N, &M);
	freopen("CON", "r", stdin);//重定向输入流到windows控制台
	int *chess = new int[N];	//chess[i]表示第i行皇后的位置
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

