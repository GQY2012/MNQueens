#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <vector>
#include <Windows.h>

using namespace std;

int N, M;
double temperature = 0.9;//初始温度
boolean acceptFlag;//标志坏状态是否被接受
LARGE_INTEGER nFreq;//cpu frequency  
LARGE_INTEGER t1;//begin
LARGE_INTEGER t2;//end


void init(int*);					//随机产生不再同一行及同一列的皇后位置
int evaluate(int*, vector<int>&);	//返回冲突的皇后个数
int doAction(int*, int, int, vector<int>&);//交换皇后位置
int next_state(int*, vector<int>&);		   //下一状态

int main() {
	const char *pathInput = "input.txt";
	freopen(pathInput, "r", stdin);//重定向输入流到指定文件
	scanf("%d %d", &N, &M);
	freopen("CON", "r", stdin);//重定向输入流到windows控制台
	int *status = new int[N];	//status[i]表示第i行皇后的位置
	int max_tries = N * N;		//最大尝试次数
	int max_steps = N * N;		//最大交换次数
	int tries = 0;

	QueryPerformanceFrequency(&nFreq);//获取cpu频率
	QueryPerformanceCounter(&t1);//算法开始时间
	while (tries < max_tries) {
		++tries;

		int steps = 0;
		int collision = 0;
		vector<int> collision_list;

		srand(time(NULL) + tries * collision);
		init(status);
		collision = evaluate(status, collision_list);

		while ((collision != M) && (steps < max_steps)) {
			collision = next_state(status, collision_list);
			steps++;
		}

		if (collision == M) {
			QueryPerformanceCounter(&t2);//算法结束时间
			cout << "尝试次数 " << tries << "交换次数 " << steps << endl;
			const char *pathInput = "output_simulated_annealing.txt";
			freopen(pathInput, "w", stdout);//重定向输入流到指定文件
			for (int i = 0; i<N; ++i) {
				cout << status[i] << endl;
			}
			printf("%f毫秒\n", (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart * 1000);
			freopen("CON", "w", stdout);//重定向输入流到windows控制台
			break;
		}
	}

	for (int i = 0; i<N; ++i) {
		cout << status[i] << endl;
	}
	printf("%f毫秒\n", (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart * 1000);
	system("pause");
	getchar();
	return 0;
}


void init(int* status) {
	for (int i = 0; i < N; i++) {
		status[i] = i;
	}
	/*随机交换*/
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++) {
		int r = rand();
		r = r % N;
		swap(status[r], status[N - r - 1]);
	}
}

int evaluate(int* status, vector<int>& collisionList) {
	collisionList.clear();
	int collision = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int offset = j - i;
			if (abs(status[i] - status[j]) == offset) {
				collisionList.push_back(j);
				collision++;
			}
		}
	}
	return collision;
}

int doAction(int *status, int row1, int row2, vector<int>& cl) {
	vector<int> new_cl;
	swap(status[row1], status[row2]);
	int new_collision = evaluate(status, new_cl);
	int old_collision = cl.size();
	if (abs(new_collision - M) > abs(old_collision - M)) {
		if (rand() % 2 < temperature) {
			acceptFlag = true;
			temperature *= 0.5;//退火
			cl = new_cl;
		}
		else{
			swap(status[row2], status[row1]);
		}
	}
	else {
		cl = new_cl;
	}
	return new_cl.size();
}

int next_state(int *status, vector<int>& cl) {
	int new_collision, old_collision = cl.size();
	int row1, row2;

	if (cl.size() == 1) {
		for (int i = 0;i < N;i++) {
			if (i != cl[0] && (doAction(status, cl[0], i, cl) == M)) {
				return M;
			}
		}
	}

	do {
		row1 = rand() % N;
		do {
			row2 = rand() % N;
		} while (row1 == row2);

		acceptFlag = false;
		new_collision = doAction(status, row1, row2, cl);
	} while (abs(new_collision - M) > abs(old_collision - M) || acceptFlag);

	return new_collision;
}