#include"GraphColor.h"
int main() {
	time_t st = clock();
	string fn = "./instance/DSJC500.5.col";
	string ofn = "color.txt";
	Solver solver = Solver();
	cout << "���ļ�" << endl;
	solver.read_file(fn);
	cout << "���ɳ�ʼ��" << endl;
	solver.minestfs = 1;
	while (solver.minestfs > 0)
	{
		solver.iter = solver.currcf = 0;
		solver.M = solver.tabuTable = vector<vector<int>>(solver.v + 1, vector<int>(solver.cn, 0));
		solver.initiate_sol();
		cout << solver.minestfs << "		" << solver.currcf << endl;
		cout << "��������" << endl;
		solver.tabu_search();
	}

	solver.write_file(ofn);
	time_t et = clock();
	cout << "����ʱ��: " << (double)(et - st) / CLOCKS_PER_SEC << "S" << endl;
	std::system("pause");
	return 0;
}