#include"GraphColor.h"
#include<sstream>


Solver::Solver()
{	
	cn = 48;
	iter = v = e  = currcf = 0;
	minestfs = non_cf = tabu_cf = 10000;
}

void Solver::read_file(string &fn)
{
	ifstream infile(fn, ios::in);
	string line;
	int f, t;
	stringstream ss;
	if (!infile) { //文件不存在
		cerr << "open file error." << endl;
		exit(1); //退出程序
	}
	while (getline(infile, line)) {//逐行读取文件
		if (line[0] == 'c') continue;
		else if (line[0] == 'p') {
			ss.clear();
			ss << line;
			ss >> line >> line >> v >>e;
			obj = sol = vector<int>(v + 1,0);
			adjTable =  vector<set<int>>(v + 1);
			M = tabuTable = vector<vector<int>>(v+1,vector<int>(cn,0));
		}
		else if (line[0] == 'e') {
			ss.clear();
			ss<<line;
			ss >> line >> f >> t;
			adjTable[f].insert(t);
			adjTable[t].insert(f);
		}
	}
	infile.close();

	cout <<"节点数：	"<< v << "	边数：	" << e << endl;
}

void Solver::write_file(string &fn) 
{//将最优解写到文件里，文件名为参数fn
	ofstream outfile(fn,ios::out);
	vector<vector<int>> vi(cn);
	for (int i = 1; i < v + 1; ++i) {
		vi[obj[i]].push_back(i);
	}

	for (int i = 0; i < cn; i++) {
		outfile << "颜色" << i <<":		";
		for (int j = 0; j < vi[i].size(); j++) {
			outfile  << vi[i][j] << "	";
		}
		cout <<'\n';
	}
	outfile.close();
}

bool Solver::initiate_sol() 
{
	srand(clock());
	srand(clock()+currcf+rand()%100); //初始化随机数种子
	//给每个结点随机上色
	for (int i = 1; i < v + 1; ++i) {
		sol[i] = rand() % cn;
	}
	/*for (int i = 1; i < v + 1; ++i) { //查看生成的随机解
		cout<< sol[i]<<"	";
	}
	cout << endl;*/
	minestfs = update_M();
	return true;
}

int Solver::update_M() 
{
	for (int i = 1; i < v + 1; ++i)
	{
		for (const auto nno : adjTable[i])
		{
			++M[i][sol[nno]];
			if (sol[i] == sol[nno])
			{
				++currcf;
			}
		}
	}
	return currcf /= 2;
}

void Solver::find_pair(my_pair<int, int> &ans)
{
	int cdiff = 0;
	non_cf = tabu_cf = INT_MAX;
	for (int i = 1; i < v + 1; ++i) 
	{ //遍历顶点，查找所有有冲突的顶点，并找出局部最优转换的顶点
		if (M[i][sol[i]] > 0)
		{ //当前结点有冲突边
			for (int c = 0; c < cn; ++c)
			{ //遍历所有可能的颜色
				if (c != sol[i])
				{
					cdiff = M[i][c] - M[i][sol[i]];
					ans.first = i;
					ans.second = c;
					if (iter >= tabuTable[i][c])
					{//非禁忌移动
						if (cdiff == non_cf)
						{
							non_tabu_pair.push_back(ans);
						}
						else if (cdiff < non_cf) 
						{
							non_cf = cdiff;
							non_tabu_pair.clear();
							non_tabu_pair.push_back(ans);
						}
					}else
					{//禁忌移动
						if (cdiff == tabu_cf)
						{
							tabu_pair.push_back(ans);
						}else if (cdiff < tabu_cf)
						{
							tabu_cf = cdiff;
							tabu_pair.clear();
							tabu_pair.push_back(ans);
						}

					}

				}
			}

		}

	}
	/*找到要更新的节点-颜色对*/
	if (tabu_pair.size() > 0 && tabu_cf < non_cf && tabu_cf + currcf < minestfs /*|| non_tabu_pair.size() == 0*/)
	{ //使用禁忌移动
		non_cf = tabu_cf;
		srand(clock()+ tabu_pair.size());
		ans = tabu_pair[rand() % tabu_pair.size()];
	}else
	{
		srand(clock()+ non_tabu_pair.size());
		ans = non_tabu_pair[rand() % non_tabu_pair.size()];
	}
}

void Solver::update(my_pair<int, int> &ans)
{
	srand(clock()+currcf+iter);
	tabuTable[ans.first][sol[ans.first]] = iter + currcf + rand()%10+1; //更新禁忌表值
	//tabuTable[ans.first][ans.second] = iter + currcf + rand()%10 ; //更新禁忌表值
	 /*更新邻接颜色表*/
	for (const int x : adjTable[ans.first]) {
		++M[x][ans.second];
		--M[x][sol[ans.first]];
	}
	sol[ans.first] = ans.second;
	currcf += non_cf;
	if (minestfs > currcf) 
	{
		minestfs = currcf;
		obj = sol;
	}
}
void Solver::tabu_search() 
{
	time_t st = clock();
	time_t  et = clock();
	while(currcf > 0 && ((et-st)/CLOCKS_PER_SEC)<200)
	{
		non_tabu_pair.clear();
		tabu_pair.clear();
		my_pair<int, int> ans;
		find_pair(ans);
		update(ans);
		iter++;
		et = clock();
	}
	cal_conflict();
}

void Solver::cal_conflict()
{
	int cf = 0;
	for (int i=1;i<v+1;++i) 
	{
		cf += M[i][sol[i]];
	}
	cout << "当前冲突：	" << cf/2 << endl;
}

