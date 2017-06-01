#include <fstream>
#include <string>
#include <iostream>
#include "../include/dec_pred.hpp"

using namespace std;

#ifdef __linux__

string imagem_predi = "./output/lena_pred.raw";
string imagem_dec = "./output/lena_dec.raw";

#elif __APPLE__

string imagem_predi = "./output/lena_pred.raw";
string imagem_dec = "./output/lena_dec.raw";

#endif

void printMatrix(char matrix[512][512])
{
	cout << endl;
	for (unsigned i = 0; i < 10; ++i)
	{
		for (unsigned j = 0; j < 16; ++j)
		{
			cout << (int)matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void abre_imagem(string path, char matriz[512][512])
{
	char ch;
	unsigned i = 0, j = 0;

	ifstream fin(path);
	if (!fin.is_open())
	{
		cout << "Arquivo " << path << " para decodificação preditiva não encontrado!" << endl;
		cout << "Arquivo .raw (512x512) deve estar em ./output/" << endl;
		exit(5);
	}

	while (fin >> ch)
	{
		if (j == 512)
		{
			j = 0;
			i++;
		}
		matriz[i][j] = (char)ch;
		j++;
	}
	fin.close();
}

void dec_pred()
{

	char image[512][512];
	char image_pred[512][512];
	char image_residuo[512][512];

	abre_imagem(imagem_predi, image_pred);

	// DECODIFICÃO DA PREDIÇÃO
	for (unsigned i = 0; i < 512; i++)
	{
		for (unsigned j = 0; j < 512; j++)
		{
			image[i][j] = (char)image_residuo[i][j] + image_pred[i][j];
		}
	}

	ofstream fout(imagem_dec);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			fout << (char)image[i][j];
		}
	}
	fout.close();

	cout << endl
		 << "Decodificação da predição finalizada." << endl;
	cout << imagem_dec << " salva." << endl
		 << endl;
}