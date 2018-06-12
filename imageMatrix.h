#ifndef IMAGEMATRIX_H
#define IMAGEMATRIX_H
#include<fstream>
#include<iostream>
#include<Windows.h>
#include<vector>
#include<iomanip>
//#define BYTE unsigned char
using namespace std;
struct YUV{
	double Y;
	double U;
	double V;
};
class imageMatrix
{
public:
	imageMatrix(char*);
	imageMatrix(int, int);
	bool bmpLoad(char*);
	bool bmpSave(char*);
	void countPSNR(imageMatrix&);
	void getY_value(int, int, double**);
	void getU_value(int, int, double**);
	void getV_value(int, int, double**);
	void setY_value(int, int, double**);
	void setU_value(int, int, double**);
	void setV_value(int, int, double**);
	int getHeight(){
		return height;
	}
	int getWidth(){
		return width;
	}
	int getRowsize(){
		return rowsize;
	}
	void print(){
		
		for (int i = 16; i >=0 ; i--){
			for (int j = 0; j < 20; j++){
				cout << int(YUV_Vec[i][j].Y) << " ";
				
			}
			cout << endl;
		}

	}
	//bool Save(char*);

private:
	int height;
	int width;
	int rowsize;
	vector<vector<YUV>> YUV_Vec;
	vector<vector<YUV>>RGB_Vec;
};
#endif