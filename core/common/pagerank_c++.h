/*
Function: c++ʵ��PageRank�㷨
Author: ystraw
Time: 2020-7-20 13:58
*/
#include<iostream>
#include<fstream>
#include<cmath>
#include <cstring>
using namespace std;
#define MAX 10000
int A[MAX][MAX];   // ��ϵ����
float M[MAX][MAX]; // Ȩ�ؾ���
float newPR[MAX];  // �洢pr 
float oldPR[MAX];
float d = 0.85;      // ��ʼ������
float threshold = 1e-4; // ������ֹ��ֵ

void getM(int n){
	// �����ʼȨ�ؾ��� 
	for(int i = 0; i < n; i++){
		int s = 0; // ͳ�Ƴ��� 
		for(int j = 0; j < n; j++){
			s += A[j][i]; // ÿ����� 
		}
		if(s == 0){  // ����Dead Ends: û�г��� 
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
	//������ȫ���ת�ƾ���: bl = (1-d)/n*1
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
	// ͨ���ڽӾ������״̬ת�ƾ���M:
    getM(n);
	// �õ���ȫ���ת�ƾ���
    getBaseLev(n);
    // ��¼��������
	int cnt = 0;
	while(1){
		cnt++;
		if(cnt % 2 == 1){
			getPR(oldPR, newPR, n); // newPR��������oldPR 
		}
		else{
			getPR(newPR, oldPR, n); 
		}
		// ����Ƿ������
		float wc = 0;
		for(int i = 0; i < n; i++){
			wc += abs(oldPR[i] - newPR[i]);
		} 
//		cout << cnt << ": " << wc << " " << threshold << endl; 
		if(wc < threshold){
			break;
		}
	} 
	// �����д�� 
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
	// ���������
	if(cnt % 2 == 1){
		return oldPR;
	}
	else{
		return newPR;
	}
}
