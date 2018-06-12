#include"imageMatrix.h"
imageMatrix::imageMatrix(char*filename){
	if (!bmpLoad(filename))
		cout << "error" << endl;
}
imageMatrix::imageMatrix(int h, int w){
	//cout << h << w << endl;
	height = h;
	width = w;
	rowsize = (w + 3) / 4 * 4;
	//cout << rowsize << endl;
	YUV_Vec.resize(h);
	RGB_Vec.resize(h);
	for (int i = 0; i < h; i++)
	{
		YUV_Vec[i].resize(rowsize);
		RGB_Vec[i].resize(rowsize);
	}
}
void imageMatrix::countPSNR(imageMatrix&after){
	double temp=0;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < rowsize; j++){
			temp += (RGB_Vec[i][j].Y - after.RGB_Vec[i][j].Y)*(RGB_Vec[i][j].Y - after.RGB_Vec[i][j].Y);
			temp += (RGB_Vec[i][j].U - after.RGB_Vec[i][j].U)*(RGB_Vec[i][j].U - after.RGB_Vec[i][j].U);
			temp += (RGB_Vec[i][j].V - after.RGB_Vec[i][j].V)*(RGB_Vec[i][j].V - after.RGB_Vec[i][j].V);
		}
	}
	cout << "PSNR:" << 10 * log((255 * 255) / (temp / (height*rowsize * 3))) << endl;
}
void imageMatrix::getY_value(int base_x,int base_y,double**output){
	for (int i = 0; i <16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x-i<0||base_y+j>rowsize-1)
				*((double*)output + 16 * i + j) = 0;
			else
				*((double*)output + 16 * i + j) = YUV_Vec[base_x-i][base_y+j].Y;
			//cout << int(*((double*)output + 16 * i + j)) << " ";
		}
		//cout << endl;
	}
	//cout << "********************************************" << endl;
}
void imageMatrix::getU_value(int base_x, int base_y, double**output){
	for (int i = 0; i <16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x - 2 * i < 0 || base_y + 2 * j>rowsize-1){
				*((double*)output + 16 * i + j) = 0;
				
			}
			else
				*((double*)output + 16 * i + j) = YUV_Vec[base_x - 2 * i][base_y + 2*j].U;
			
				//cout << int(*((double*)output + 16 * i + j))<<" ";
		}
		//cout << endl;
	}
	//cout << "_______________________________________" << endl;
}
void imageMatrix::getV_value(int base_x, int base_y, double**output){
	for (int i = 0; i <16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x - 2 * i -1< 0 || base_y + 2 * j>rowsize - 1){
				*((double*)output + 16 * i + j) = 0;
			}
			else
				*((double*)output + 16 * i + j) = YUV_Vec[base_x - 2*i-1][base_y + 2*j].V;
			//cout << int(*((double*)output + 16 * i + j)) << " ";
		}
		//cout << endl;
	}
}
void imageMatrix::setY_value(int base_x, int base_y, double**output){
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x-i>0&&base_y+j<rowsize-1)
				YUV_Vec[base_x - i][base_y + j].Y = *((double*)output + i * 16 + j);
	//		cout << int(YUV_Vec[base_x - i][base_y + j].Y )<< " ";
		}
	//	cout << endl;
	}
//	cout << "-------------------" << endl;
}
void imageMatrix::setU_value(int base_x, int base_y, double**output){
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x - 2 * i>-1 && base_y + 2 * j < rowsize){
				YUV_Vec[base_x - 2 * i][base_y + 2 * j].U = *((double*)output + i * 16 + j);
				if (base_x - 2 * i - 1>-1)
				{
					YUV_Vec[base_x - 2 * i - 1][base_y + 2 * j].U = *((double*)output + i * 16 + j);
					if (base_y - 2 * +1 < rowsize)
						YUV_Vec[base_x - 2 * i - 1][base_y + 2 * j + 1].U = *((double*)output + i * 16 + j);
				}
				if (base_y + 2 * j + 1 < rowsize)
					YUV_Vec[base_x - 2 * i][base_y + 2 * j + 1].U = *((double*)output + i * 16 + j);
			}
		}
	}
}
void imageMatrix::setV_value(int base_x, int base_y, double**output){

	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			if (base_x - 2 * i-1>-1 && base_y + 2 * j < rowsize){
				YUV_Vec[base_x - 2 * i - 1][base_y + 2 * j].V = *((double*)output + i * 16 + j);
				YUV_Vec[base_x - 2 * i][base_y + 2 * j].V = *((double*)output + i * 16 + j);	
				if (base_y - 2 * +1 < rowsize)
				{
					YUV_Vec[base_x - 2 * i - 1][base_y + 2 * j + 1].V = *((double*)output + i * 16 + j);
					YUV_Vec[base_x - 2 * i][base_y + 2 * j + 1].V = *((double*)output + i * 16 + j);
				}
				
			}
		}
	}
}
bool imageMatrix::bmpSave(char*filename){
	BITMAPFILEHEADER h = {
		0x4d42,
		54L + rowsize*height,
		0,
		0,
		54
	};
	BITMAPINFOHEADER hInfo = {
		sizeof(BITMAPINFOHEADER),
		width,
		height,
		1,
		24,
		0,
		rowsize*height,
		0,
		0,
		0,
		0
	};
	ofstream f;
	f.open(filename, ios::binary);
	f.write((char*)&h, sizeof(h));
	f.write((char*)&hInfo, sizeof(hInfo));
	
	cout << "save file: " << filename << "...." << endl;
	for (int y = 0; y != YUV_Vec.size(); ++y) {
		for (int x = 0; x != YUV_Vec[0].size(); ++x) {

			/*	R = Y + (1.4075 * (V - 128)); 
				G = Y - (0.3455 * (U - 128) - (0.7169 * (V - 128));
				B = Y + (1.7790 * (U - 128);
			*/
			char chB =YUV_Vec[y][x].Y + (2.03 * (YUV_Vec[y][x].U))-1;
			char chG = YUV_Vec[y][x].Y - 0.39 * (YUV_Vec[y][x].U ) - (0.58 * (YUV_Vec[y][x].V ))-1;
			char chR =  YUV_Vec[y][x].Y + (1.14 * (YUV_Vec[y][x].V))-1;
			RGB_Vec[y][x].Y = chR;
			RGB_Vec[y][x].U = chG;
			RGB_Vec[y][x].V = chB;
			f.put(chB).put(chG).put(chR);
		}
	}
	f.close();
	
	return 1;
}
bool imageMatrix::bmpLoad(char *filename){

	BITMAPFILEHEADER h;
	BITMAPINFOHEADER hInfo;
	ifstream f;
	f.open(filename, ios::binary);
	f.seekg(0, f.end);
	cout << "圖檔大小: " << f.tellg() << "bytes\n";
	f.seekg(0, f.beg);
	f.read((char*)&h, sizeof(h));
	f.read((char*)&hInfo, sizeof(hInfo));
	if (h.bfType != 0x4d42			//BM
		|| hInfo.biClrUsed != 0		//沒調色盤
		|| hInfo.biCompression != 0	//沒壓縮
		|| hInfo.biBitCount != 24	//24色素
		|| hInfo.biPlanes != 1		//一個平面
		)
	{
		cout << "error" << endl;
		return false;
	}
	width = hInfo.biWidth;
	height = hInfo.biHeight;
	cout << "reading from file " << filename << "...\n";
	rowsize = (width + 3) / 4 * 4;
	//resize YUV
	YUV_Vec.resize(height);
	RGB_Vec.resize(height);
	for (int i = 0; i < height; i++)
	{
		YUV_Vec[i].resize(rowsize);
		RGB_Vec[i].resize(rowsize);
	}
	//get RGB from bmp file
	for (int y = 0; y !=YUV_Vec.size(); ++y) {
		for (int x = 0; x != YUV_Vec[0].size(); ++x) {
			/*
			Y = R * .299 + G * .587 + B * .114;
			U = R * -.169 + G * -.332 + B * .500 + 128.;
			V = R * .500 + G * -.419 + B * -.0813 + 128.;
			*/
			char chR, chG, chB;
			f.get(chB).get(chG).get(chR);
			RGB_Vec[y][x].Y = chR;
			RGB_Vec[y][x].U = chG;
			RGB_Vec[y][x].V = chB;
			YUV_Vec[y][x].Y = (double)(0.299*chR + 0.587*chG + 0.114* chB);
			YUV_Vec[y][x].U = (double)(-0.147*chR - 0.289*chG + 0.436*chB);
			YUV_Vec[y][x].V = (double)(0.615*chR - 0.515*chG - 0.1*chB);
		}
	}
	
	/*for (int i = height - 1; i >= 0; i--){
		for (int j = 0; j < rowsize; j++){
			cout << setw(3) << int(YUV_Vec[i][j].Y) << " ";
		}
		cout << endl;
	}*/

	f.close();
	
	return true;
}