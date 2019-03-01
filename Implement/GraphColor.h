#pragma once
#ifndef GRAPH_COLOR_H
#define GRAPH_COLOR_H
#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<set>
using namespace std;
template<class T1,class T2>
using my_pair = pair<T1, T2>;
class Solver {
protected:
	int  cn; //颜色数
	int  v;//顶点数
	int  e;//边数
	int iter;//迭代步长
	int minestfs,currcf;//目前最小的冲突数,当前解的冲突数
	vector<int> obj;//最小的冲突数对应的目标解
	vector<int> sol;//当前解
	vector<vector<int>> M; //邻接颜色表
	vector<vector<int>> tabuTable;//禁忌表
	vector<set<int>> adjTable;//adjTable[i] = 结点i的邻居结点集合

	int non_cf;
	int tabu_cf;
	vector<my_pair<int, int>> non_tabu_pair;//非禁忌的最佳交换对
	vector<my_pair<int, int>> tabu_pair;//禁忌的最佳交换对

	Solver();
	void read_file(string &fn);
	void write_file(string &fn);
	bool initiate_sol(); //初始化sol
	int update_M();
	void find_pair(my_pair<int,int> &ans); //找到要更改颜色的节点以及要变成的颜色
	void update(my_pair<int, int> &ans);
	void tabu_search();
	void cal_conflict();
	friend int main();
};
#endif