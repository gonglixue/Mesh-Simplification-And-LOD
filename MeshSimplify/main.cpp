#include <iostream>
#include <time.h>
#include "Simplify.h"
#include "Config.h"
#include "solve.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4) {
		cout << "error input" << endl;
		return -1;
	}
	else {
		clock_t start = clock();
		Simplify* meshSimplify = new Simplify();
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
		meshSimplify->setRatio(atof(argv[3]));  // 简化率
		meshSimplify->input();  // 读入
		meshSimplify->start();  // 开始简化
		meshSimplify->output();  // 输出

		clock_t finish = clock();
		cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	}

	return 0;
}