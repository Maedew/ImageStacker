//Assignment 2: Image Stacker	Due: 10/8/2018
//Program processes 10 images to create a final, noise-free output image file (.ppm)
//Jessica Ng

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROWS = 1000;
const int MAX_COLS = 1000;
const int z = 3;

void ReadMatrixFile(ifstream & file, int matA[][MAX_COLS][z], int nRows, int nCols);
void AddMatrices(int matA[][MAX_COLS][z], int matB[][MAX_COLS][z], int nRows, int nCols);

int main()
{
	string fileName, outFile, folder;
	ifstream imageFile;
	ofstream outputImage;

	cout << "Enter image folder name : ";
	cin >> folder;

	int matA[MAX_ROWS][MAX_COLS][z] = { 0 }; //input
	int matB[MAX_ROWS][MAX_COLS][z] = { 0 }; //output

	char num = '1';
	for (int i = 0; i < 10; i++) //going through files
	{
		if (num <= '9')		//files 001 to 009
		{
			fileName = folder + "/" + folder + "_00";
			fileName += num;
			fileName += ".ppm";
		}
		else		//file 010
		{
			fileName = folder + "/" + folder + "_010.ppm";
		}

		imageFile.open(fileName);	//opening file

		//check file--------------------------------------------------------------------
		if (!imageFile)
		{
			cout << "Failed to open file." << endl;
			return 0;
		}

		cout << fileName << endl;

		string magicNumber;
		int row, col, mcv;	//mcv= maximum color value

		imageFile >> magicNumber;
		imageFile >> row >> col >> mcv;

		if (row > 1000 || col > 1000)
		{
			cout << "Image contains more than 1000 pixels in either width or height.";
			imageFile.close();
			return 0;
		}

		//getting values-------------------------------------------------------------------
		ReadMatrixFile(imageFile, matA, row, col);	//obtaining values

		AddMatrices(matA, matB, row, col);	//adding values to matB

		imageFile.close();
		num++;		//next file number
	} //end of going through files


	imageFile.open(fileName);
	string magicNumber;
	int row, col, mcv;
	imageFile >> magicNumber >> row >> col >> mcv;	//reobtain data to put in output file

	//getting the average of the values
	for (int z = 0; z < 3; z++)
	{
		for (int r = 0; r < row; r++)
		{
			for (int c = 0; c < col; c++)
			{
				matB[r][c][z] = matB[r][c][z] / 10;
			}
		}
	}
	imageFile.close();

	//create output file--------------------------------------------------------------------
	string outFileName;
	outFileName = folder + "_good.ppm";

	cout << "Creating output file : " << outFileName << endl;

	outputImage.open(outFileName);
	outputImage << magicNumber << endl;			//ppm header
	outputImage << row << " " << col << endl;
	outputImage << mcv << endl;

	int test = 0;

	for (int z = 0; z < 3; z++)
	{
		for (int r = 0; r < row; r++) //put in values from matrix
		{
			for (int c = 0; c < col; c++)
			{
				outputImage << matB[r][c][z] << " ";
			}
		}
	}

	outputImage.close();

	return 0;
}

void ReadMatrixFile(ifstream & file, int matA[][MAX_COLS][z], int nRows, int nCols)
{
	//obtains values and puts into matA
	for (int z = 0; z < 3; z++)
	{
		for (int r = 0; r < nRows; r++)
		{
			for (int c = 0; c < nCols; c++)
			{
				file >> matA[r][c][z];
			}
		}
	}
}

void AddMatrices(int matA[][MAX_COLS][z], int matB[][MAX_COLS][z], int nRows, int nCols)
{
	//takes values from matA and adds it to matB
	//matB stores added values which will later be divided by 10 to get average
	for (int z = 0; z < 3; z++)
	{
		for (int r = 0; r < nRows; r++)
		{
			for (int c = 0; c < nCols; c++)
			{
				matB[r][c][z] += matA[r][c][z];
			}
		}
	}
}