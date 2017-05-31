#include <fstream>
#include <string>
#include <iostream>
#include "../include/dec_pred.hpp"

using namespace std;

void abre_imagem(string path, unsigned int matriz[512][512])
{
	unsigned char ch;
	unsigned i = 0, j = 0;

	ifstream fin(path);
	if (!fin.is_open())
	{
		cout << "Arquivo " << path << " para decodificação preditiva não encontrado!";
		cout << "Arquivo .raw (512x512) deve estar em ./output/" << endl;
		exit(5);
	}

	while (fin >> ch)
	{
		j++;
		if (j == 512)
		{
			j = 0;
			i++;
		}
		matriz[i][j] = (unsigned int)ch;
	}
	fin.close();
}

void dec_pred()
{
	string imagem_residuo = "./output/lena_residuo.raw";
	string imagem_pred = "./output/lena_pred.raw";
	string imagem_dec = "./output/lena_dec.raw";

	unsigned int image[512][512];
	unsigned int image_pred[512][512];
	unsigned int image_residuo[512][512];

	abre_imagem(imagem_residuo, image_residuo);

	abre_imagem(imagem_pred, image_pred);

	// DECODIFICÃO DA PREDIÇÃO
	for (unsigned i = 0; i < 512; ++i)
	{
		for (unsigned j = 0; j < 512; ++j)
		{
			image[i][j] = image_residuo[i][j] + image_pred[i][j];
		}
	}

	ofstream fout(imagem_dec);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			fout << (unsigned char)image[i][j];
		}
	}
	fout.close();
}