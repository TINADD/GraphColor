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
	int  cn; //��ɫ��
	int  v;//������
	int  e;//����
	int iter;//��������
	int minestfs,currcf;//Ŀǰ��С�ĳ�ͻ��,��ǰ��ĳ�ͻ��
	vector<int> obj;//��С�ĳ�ͻ����Ӧ��Ŀ���
	vector<int> sol;//��ǰ��
	vector<vector<int>> M; //�ڽ���ɫ��
	vector<vector<int>> tabuTable;//���ɱ�
	vector<set<int>> adjTable;//adjTable[i] = ���i���ھӽ�㼯��

	int non_cf;
	int tabu_cf;
	vector<my_pair<int, int>> non_tabu_pair;//�ǽ��ɵ���ѽ�����
	vector<my_pair<int, int>> tabu_pair;//���ɵ���ѽ�����

	Solver();
	void read_file(string &fn);
	void write_file(string &fn);
	bool initiate_sol(); //��ʼ��sol
	int update_M();
	void find_pair(my_pair<int,int> &ans); //�ҵ�Ҫ������ɫ�Ľڵ��Լ�Ҫ��ɵ���ɫ
	void update(my_pair<int, int> &ans);
	void tabu_search();
	void cal_conflict();
	friend int main();
};
#endif