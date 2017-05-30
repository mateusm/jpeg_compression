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
using namespace std;


void predicao(unsigned int img[][512], unsigned int img_pred[][512]){
    
    for(int i = 0; i <512; i++){
        for(int j  = 0; j < 512; j++){
            if(j == 0){
                img_pred[i][j] = img[i][j];
            }else{
                img_pred[i][j] = img[i][0];
            }
        }
    }
}

void residuo(unsigned int img[][512], unsigned int img_pred[][512], unsigned int img_residuo[][512]){
    
    for(int i = 0; i <512; i++){
        for(int j  = 0; j < 512; j++){
            img_residuo[i][j] = img[i][j] - img_pred[i][j];
        }
    }
}



int main(int argc, const char * argv[]) {
    
    char fileName[80] = "/Users/mateusmesturini/Downloads/lena.raw"; //512x512 image
    ifstream fin(fileName);
    unsigned char ch;
    unsigned int image[512][512];
    unsigned int image_pred[512][512];
    unsigned int image_residuo[512][512];

    int i = 0,j = 0;
    
    
    while (fin >> ch){ //le imagem e coloca numa matriz de unsigned int
        j++;
        if(j == 512){j=0; i++;}
        image[i][j] = (unsigned int)ch;
    }
    fin.close();
    
    
    predicao(image,image_pred);
    residuo(image, image_pred, image_residuo);
    
    ofstream fout("/Users/mateusmesturini/Downloads/lena_residuo.raw");
    ofstream fpred("/Users/mateusmesturini/Downloads/lena_predicao.raw");
    for(int i = 0; i <512; i++){
        for(int j  = 0; j < 512; j++){
            fout << (unsigned char)image_residuo[i][j];
            fpred << (unsigned char)image_pred[i][j];
        }
    }
    
    
    
    

    return 0;
}

