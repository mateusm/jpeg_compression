#include <iostream>
#include <fstream>
#include <string>
#include "../include/cod_pred.hpp"
#include "../include/dec_pred.hpp"
#include "../include/jo_jpeg.h"

using namespace std;

#ifdef __linux__

string imagem_pred = "./output/lena_pred.raw";
string imagem_residuo = "./output/lena_residuo.raw";
string imagem_entrada = "./lena.raw";
const char *imagem_saida_jpeg = "./lena_jpeg.jpeg";

#elif __APPLE__

string imagem_pred = "./output/lena_pred.raw";
string imagem_residuo = "./output/lena_residuo.raw";
string imagem_entrada = "./lena.raw";
const char *imagem_saida_jpeg = "./lena_jpeg.raw";

#endif

// em relação a primeira coluna
void predicao(char img[][512], char img_pred[][512])
{

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			if (j == 0)
			{
				img_pred[i][j] = img[i][j];
			}
			else
			{
				img_pred[i][j] = img[i][0];
			}
		}
	}
}

void gerar_residuo(char img[][512], char img_pred[][512], char img_residuo[][512])
{

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			img_residuo[i][j] = img_pred[i][j] - img[i][j];
		}
	}

	// salva resíduo em JPEG
	bool status = jo_write_jpg(imagem_saida_jpeg, img_residuo, 512, 512, 1, 90);
	if (status)
		cout << "Codificação JPEG ok."
			 << " Imagem " << imagem_saida_jpeg << " salva." << endl;
	else
		cout << "Codificação JPEG falhou." << endl;
}

void cod_pred(char image[512][512])
{
	char image_pred[512][512];
	char image_residuo[512][512];

	predicao(image, image_pred);
	gerar_residuo(image, image_pred, image_residuo);

	ofstream fout(imagem_residuo, ios::binary);
	ofstream fpred(imagem_pred);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			fout << image_residuo[i][j];
			fpred << image_pred[i][j];
		}
	}
	fout.close();
	fpred.close();

	cout << endl
		 << "Predição finalizada." << endl;
	cout << imagem_pred << " e " << imagem_residuo << " salvas." << endl
		 << endl;
}

int main(int argc, const char *argv[])
{

	char image[512][512];
	char image_residuo[512][512];

	abre_imagem(imagem_entrada, image);

	// faz predição, gera imagem resíduo e as salva em arquivos
	cod_pred(image);

	// faz decodificação da imagem e a salva
	dec_pred();

	return 0;
}
