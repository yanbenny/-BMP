#include"imageMatrix.h"
const double PI = 3.1415926;
const static int Color_Quantization_Table[16][16] =
{
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	2, 3, 3, 3, 2, 4, 5, 6, 7, 3, 3, 4, 2, 5, 4, 6,
	/*17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,
	17, 18, 18, 19, 20, 24, 25, 26, 27, 28, 29, 40, 42, 44, 43, 99,*/
};
const static int Luminance_Quantization_Table[16][16] = {
	8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 30,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 30, 28,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 32, 35, 29,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 32, 35, 32, 28,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 40, 42, 40, 35,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 42, 44, 40, 35, 31,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 35, 44, 44, 50, 53, 52, 45,
	1, 1, 1, 1, 1, 1, 1, 1, 31, 34, 44, 55, 53, 52, 45, 39,
	1, 1, 1, 1, 1, 1, 1, 31, 34, 40, 41, 47, 52, 45, 52, 50,
	1, 1, 1, 1, 1, 1, 30, 32, 36, 41, 47, 52, 54, 57, 50, 46,
	1, 1, 1, 1, 1, 36, 32, 36, 44, 47, 52, 57, 60, 57, 55, 47,
	1, 1, 1, 1, 36, 39, 42, 44, 48, 52, 57, 61, 60, 60, 55, 51,
	1, 1, 1, 39, 42, 47, 48, 46, 49, 57, 56, 55, 52, 61, 54, 51,
	1, 1, 42, 46, 47, 48, 48, 49, 53, 56, 53, 50, 51, 52, 51, 50,
	1, 45, 46, 47, 48, 48, 49, 57, 56, 56, 50, 52, 52, 51, 51, 50,
	
};
void Zig_Zag(int col,int row,double **inputdata,vector<int>&Zout)
{
	int i = 0, j = 0, up = 1;
	bool turned = false;
	int d[2][2] = { { 1, -1 }, { -1, 1 } };
	int corner[2][4] = { { 1, 0, 0, 1 }, { 0, 1, 1, 0 } };
	while (i < col && j < row) {
		
		Zout.push_back(*((double*)inputdata + i*col + j));

		if (i == 0 || j == 0 || i == col - 1 || j == row - 1) {
			if (!turned) {
				int k = 2 * (up * (j / (row- 1)) | (1 - up) * (i / (col - 1)));
				i += corner[up][k];
				j += corner[up][k + 1];
				turned = true;
				up = 1 - up;
				continue;
			}
			else
				turned = false;
		}
		i += d[up][0];
		j += d[up][1];

	}
	int ZeroCount = 0;
	for (int i = 255; i >= 0; i--){
		if (Zout[i] == 0)
		{
			ZeroCount = ZeroCount + 1;
			Zout.pop_back();
			if (i == 0)
			{
				Zout.push_back('EOF');
				Zout.push_back(ZeroCount);
				//全為0
			}
		}
		else
		{
			Zout.push_back('EOF');
			Zout.push_back(ZeroCount);
			//有一個不為0
			break;
		}
	}
	
	

}
void InverseV(int index, int type,vector<int>& a,double **output){
	for (int i = 0; i < type; i++){
		for (int j = 0; j < type; j++){
			*((double*)output + i * type + j) = a[index+i * type+ j];
		}
	}
}
void push(vector<int>& a,double **input){
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			a.push_back((int)(*((double*)input + i * 16 + j)));
		}
	}
}
void ReadAnotherFile(char* filename, vector<int>& a, vector<int>& b, vector<int>& c){



}
void SaveAnotherFile(char* filename, vector<int>& a, vector<int>& b, vector<int>& c)
{
	ofstream f;
	f.open(filename, ios::binary);
	for (unsigned int i = 0; i < a.size(); i++)
	{
		f.put((char)a[i]);
	}
	for (unsigned int i = 0; i < b.size(); i++){
		f.put((char)b[i]);
	}
	for (unsigned int i = 0; i < c.size(); i++){
		f.put((char)c[i]);
	}
	f.close();
	
}
void DCT(double ** input, double ** output, int row, int col,int type)
{	
	//cout << "Test in DCT" << endl;
	double ALPHA, BETA;
	int u = 0;
	int v = 0;
	int i = 0;
	int j = 0;

	for (u = 0; u < row; u++)
	{
		for (v = 0; v < col; v++)
		{
			if (u == 0)
			{
				ALPHA = sqrt(1.0 / row);
			}
			else
			{
				ALPHA = sqrt(2.0 / row);
			}

			if (v == 0)
			{
				BETA = sqrt(1.0 / col);
			}
			else
			{
				BETA = sqrt(2.0 / col);
			}

			double tmp = 0.0;
			for (i = 0; i < row; i++)
			{
				for (j = 0; j < col; j++)
				{
					tmp += *((double*)input + col*i + j) * cos((2 * i + 1)*u*PI / (2.0 * row)) * cos((2 * j + 1)*v*PI / (2.0 * col));
				}
			}
			
			if (type == 0)
				*((double*)output + col*u + v) = int(ALPHA * BETA * tmp / (1*Luminance_Quantization_Table[u][v])+0.5);
			else if (type == 1)
				*((double*)output + col*u + v) = int(ALPHA * BETA * tmp / (1*Color_Quantization_Table[u][v]) + 0.5);

		}
	}

	//cout << "The result of DCT:" << endl;
	/*
	for (int m = 0; m < row; m++)
	{
		for (int n = 0; n < col; n++)
		{
			cout << setw(2) << *((double*)output + col*m + n) << "  ";
		}
		cout << endl;
	}
	*/
}
// Inverse DCT
void IDCT(double ** input, double ** output, int row, int col,int type)
{
	//cout << "Test in IDCT" << endl;
	double ALPHA, BETA;
	int u = 0;
	int v = 0;
	int i = 0;
	int j = 0;
	if (type == 0){
		for (int k = 0; k < 16; k++){
			for (int l = 0; l < 16; l++){
				*((double*)input + col*k + l) = int(1*Luminance_Quantization_Table[k][l] * *((double*)input + col*k + l)+0.5);
			}
		}
	}
	else if (type == 1){
		for (int k = 0; k < 16; k++){
			for (int l = 0; l < 16; l++){
				*((double*)input + col*k + l) = int(1*Color_Quantization_Table[k][l] * *((double*)input + col*k + l)+0.5);
			}
		}
	}
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			double tmp = 0.0;
			for (u = 0; u < row; u++)
			{
				for (v = 0; v < col; v++)
				{
					if (u == 0)
					{
						ALPHA = sqrt(1.0 / row);
					}
					else
					{
						ALPHA = sqrt(2.0 / row);
					}
					if (v == 0)
					{
						BETA = sqrt(1.0 / col);
					}
					else
					{
						BETA = sqrt(2.0 / col);
					}
					tmp += ALPHA * BETA * *((double*)input + col*u + v)* cos((2 * i + 1)*u*PI / (2.0 * row)) * cos((2 * j + 1)*v*PI / (2.0 * col));
				}
			}
			*((double*)output + col*i + j) = tmp;
		}
	}

	/*cout << "The result of IDCT:" << endl;
	for (int m = 0; m < row; m++)
	{
		for (int n = 0; n < col; n++)
		{
			cout << setw(2) << int(*((double*)output + col*m + n) + 0.5) << " ";
		}
		cout << endl;
	}*/
}
int main(){
	imageMatrix a("dog.bmp");
	imageMatrix b(a.getHeight(), a.getWidth());
	vector<int>Y;
	vector<int>Y_Zig;
	vector<int>U;
	vector<int>U_Zig;
	vector<int>V;
	vector<int>V_Zig;
	double outputdata[16][16];
	double inputdata[16][16];



	int n,m;
	if (a.getHeight() % 16 == 0)
		n = a.getHeight() / 16;
	else
		n = a.getHeight() / 16 + 1;
	if (a.getRowsize() % 16 == 0)
		m = a.getRowsize() / 16;
	else
		m = a.getRowsize() / 16 + 1;
	//cout << n << " " << m << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			a.getY_value(a.getHeight()-1-(16*i), 0+(16*j), (double**)inputdata);
			DCT((double**)inputdata, (double**)outputdata, 16, 16,0);
			Zig_Zag(16, 16, (double**)outputdata,Y_Zig);
			push(Y, (double**)outputdata);
		}
	}
	
	if (a.getHeight() % 32 == 0)
		n = a.getHeight()/32;
	else
		n = a.getHeight()/32 + 1;
	if (a.getRowsize() % 32 == 0)
		m = a.getRowsize()/32;
	else
		m = a.getRowsize()/32 + 1;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			//cout << a.getHeight() - 1 - (32 * i) << " " << 0 + (32 * j) << endl;
			a.getU_value(a.getHeight() - 1 - (32 * i), 0 + (32*j), (double**)inputdata);
			DCT((double**)inputdata, (double**)outputdata, 16, 16,1);
			Zig_Zag(16, 16, (double**)outputdata, U_Zig);
			push(U, (double**)outputdata);
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			a.getV_value(a.getHeight() - 1 - (32 * i), 0 + (32*j), (double**)inputdata);
			DCT((double**)inputdata, (double**)outputdata, 16, 16,1);
			Zig_Zag(16, 16, (double**)outputdata, V_Zig);
			push(V, (double**)outputdata);
		}
	}
	
	//a.print();

	cout << "Y: " << Y.size() << endl;;
	cout << "U: " << U.size() << endl;
	cout << "V: " << V.size() << endl;
	cout << "Y_ZIG: " << Y_Zig.size() << endl;
	cout << "U_ZIG: " << U_Zig.size() << endl;
	cout << "V_ZIG: " << V_Zig.size() << endl;
	SaveAnotherFile("test.txt", Y_Zig, U_Zig, V_Zig);

	int index = 0;
	int base_x = b.getHeight() - 1;
	int base_y = 0;
	
	for (int i = 0; i < Y.size() / (16 * 16); i++){
		InverseV(index, 16, Y, (double**)inputdata);
		
		IDCT((double**)inputdata, (double**)outputdata, 16, 16, 0);
		/*for (int i = 0; i<16; i++){
			for (int j = 0; j < 16; j++){
				cout << int(outputdata[i][j]) << " ";
			}
			cout << endl;
		}*/
		b.setY_value(base_x, base_y, (double**)outputdata);
		index += (16 * 16);
		//cout << base_x << " " << base_y << endl;
		base_y += 16;
		if (base_y>(b.getRowsize() - 1)){
			base_x -= 16;
			base_y = 0;
		}
	}
	index = 0;
	base_x = b.getHeight() - 1;
	base_y = 0;
	for (int i = 0; i < U.size() / (16 * 16); i++){
		InverseV(index, 16, U, (double**)inputdata);
		IDCT((double**)inputdata, (double**)outputdata, 16, 16,1);
		b.setU_value(base_x, base_y, (double**)outputdata);


		InverseV(index, 16, V, (double**)inputdata);
		IDCT((double**)inputdata, (double**)outputdata, 16, 16, 1);
		//cout << outputdata[1][1] << endl;
		b.setV_value(base_x, base_y, (double**)outputdata);
		index += (16 * 16);
		
		//cout << base_x << " " << base_y << endl;
		base_y += 32;
		if (base_y>(b.getRowsize() - 1)){
			base_x -= 32;
			base_y = 0;
		}
	}
	
	b.bmpSave("dog_4.bmp"); 
	a.countPSNR(b);



	system("pause");
}