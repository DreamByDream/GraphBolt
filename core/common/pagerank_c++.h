/*
Function: c++实现PageRank算法
Author: ystraw
Time: 2020-7-20 13:58
*/
#include<iostream>
#include<fstream>
#include<cmath>
#include <cstring>
using namespace std;
#define MAX 10000
int A[MAX][MAX];   // 关系矩阵
float M[MAX][MAX]; // 权重矩阵
float newPR[MAX];  // 存储pr 
float oldPR[MAX];
float d = 0.85;      // 初始化参数
float threshold = 1e-4; // 迭代终止阈值

void getM(int n){
	// 计算初始权重矩阵 
	for(int i = 0; i < n; i++){
		int s = 0; // 统计出度 
		for(int j = 0; j < n; j++){
			s += A[j][i]; // 每列求和 
		}
		if(s == 0){  // 处理Dead Ends: 没有出度 
			for(int j = 0; j < n; j++){
				M[j][i] = 1.0 / n;
			}	
		}
		else{
			float fm = s;
			for(int j = 0; j < n; j++){
				M[j][i] = A[j][i] / fm;
			}	
		}
	}
//	for(int i = 0 ; i < n; i++){
//		for(int j = 0; j < n; j++){
//			cout << M[i][j] << " ";
//		}
//		cout << endl;
//	}
}

void getBaseLev(int n){
	//计算完全随机转移矩阵: bl = (1-d)/n*1
	for(int i = 0; i < n; i++){
		newPR[i] = 1.0/n;
	}
//	for(int i = 0; i < n; i++){
//		cout << newPR[i] << endl;
//	} 
}

void getPR(float *a, float *b, int n){
	// d * M @ oldPR + BL
	for(int i = 0; i < n; i++){
		a[i] = 0;
		for(int j = 0; j < n; j++){
			a[i] += M[i][j] * b[j];
		}
		a[i] = a[i] * d + 1.0/n * (1-d);
	}
//	for(int i = 0; i < n; i++){
//		cout << a[i] << " ";
//	} 
//	cout << endl;
} 

float* computePR(int n, char* outpath){ 
	
	//	cout << n << endl;
	// 通过邻接矩阵计算状态转移矩阵M:
    getM(n);
	// 得到完全随机转移矩阵
    getBaseLev(n);
    // 记录迭代次数
	int cnt = 0;
	while(1){
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
		if(wc < threshold){
			break;
		}
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
