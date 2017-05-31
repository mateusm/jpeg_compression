//
//  main.cpp
//  Compressor
//
//  Created by Mateus Mesturini Meruvia on 5/29/17.
//  Copyright © 2017 Mateus Mesturini Meruvia. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "../include/cod_pred.hpp"
#include "../include/dec_pred.hpp"

using namespace std;

void predicao(unsigned int img[][512], unsigned int img_pred[][512])
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

void gerar_residuo(unsigned int img[][512], unsigned int img_pred[][512], unsigned int img_residuo[][512])
{

	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			img_residuo[i][j] = img_pred[i][j] - img[i][j];
		}
	}
}

void cod_pred(unsigned int image[512][512])
{

	string imagem_pred = "./output/lena_pred.raw";
	string imagem_residuo = "./output/lena_residuo.raw";

	unsigned int image_pred[512][512];
	unsigned int image_residuo[512][512];

	predicao(image, image_pred);
	gerar_residuo(image, image_pred, image_residuo);

	ofstream fout(imagem_residuo);
	ofstream fpred(imagem_pred);
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			fout << (unsigned char)image_residuo[i][j];
			fpred << (unsigned char)image_pred[i][j];
		}
	}

	fout.close();
	fpred.close();
	cout << imagem_pred << " e " << imagem_residuo << " salvas." << endl;

	return;
}

int main(int argc, const char *argv[])
{
	string imagem_entrada = "./lena.raw";

	char fileName[80] = "/Users/mateusmesturini/Downloads/lena.raw"; //512x512 image

	unsigned int image[512][512];

	abre_imagem(imagem_entrada, image);

	// faz predição, gera imagem resíduo e as salva em arquivos
	cod_pred(image);

	// faz decodificação da imagem e a salva
	dec_pred();

	return 0;
}
