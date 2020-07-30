/*
Function: c++实现PageRank算法, 邻接链表 
Author: ystraw
Time: 2020-7-22 13:58
*/

#include <iostream>
#include <vector>
#include <cstring>
#include<fstream>
#include<cmath>
using namespace std;
#define MAX 1000000

vector <int> in_ver[MAX]; // 存储各点入度的点 
int out_num[MAX]; // 存储各点出度数量 
float newPR[MAX]; // 存储pr 
float oldPR[MAX];
float d = 0.80;         // 初始化参数
float threshold = 1e-4; // 迭代终止阈值

void getPR(float *a, float *b, int n){
	for(int i = 0; i < n; i++){
		a[i] = 0;
		int len = in_ver[i].size();
		for(int j = 0; j < len; j++){
			a[i] += b[in_ver[i][j]] / out_num[in_ver[i][j]]; // 累加：该点入度点的pr值除以该点的出度 
		}
		//a[i] = a[i] * d + (1 - d) / n;
		a[i] = a[i] * d + 1 - d; 
	}
}

float* computePR(int n, char* outpath){ 
	// 处理没有出度的点
	for(int i = 0; i < n; i++){
		if(out_num[i] == 0){ // 如果没有出度，则将其指向另外的所有点 
			out_num[i] = n;
			for(int j = 0; j < n; j++){
				in_ver[j].push_back(i);
			}
		}
		//newPR[i] = 1.0/n;
		newPR[i] = 1.0; // 初始化1
	}  
    // 记录迭代次数
	int cnt = 0;
	while(cnt < 200){
		cnt++;
		if(cnt % 2 == 1){
			getPR(oldPR, newPR, n); // newPR迭代存入oldPR 
		}
		else{
			getPR(newPR, oldPR, n); 
		}
		// 检测是否结束：
		float wc = 0;
		for(int i = 0; i < n; i++){
			wc += abs(oldPR[i] - newPR[i]);
		} 
//		cout << cnt << ": " << wc << " " << threshold << endl; 
		//if(wc < threshold){ // 收敛判断
		//	break;
		//}
	} 
	// 将结果写入 
	if(*outpath != '\0'){
//		ofstream fout(".\\output.txt");
		cout << "outpath:" << outpath << endl;
		ofstream fout(outpath);
		if(cnt % 2 == 1){
			for(int i=0; i<n; i++)
				fout<< i << ' ' << oldPR[i] << endl;
		}
		else{
			for(int i=0; i<n; i++)
				fout << i << ' ' << newPR[i] << endl;
		}
	}
	// 将结果返回
	if(cnt % 2 == 1){
		return oldPR;
	}
	else{
		return newPR;
	}
}
