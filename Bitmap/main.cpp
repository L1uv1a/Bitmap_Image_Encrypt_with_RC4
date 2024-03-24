#include <iostream>
#include <stdio.h>
#include "Image.h"
#include "RC4.h"
#include "AES.h"

#define T_ELEMENT_MAX   (256)
#define S_ELEMENT_MAX   (T_ELEMENT_MAX)

unsigned char S_vector[256];
unsigned char S_vector_R[256];
unsigned char S_vector_G[256];
unsigned char S_vector_B[256];
unsigned char T_vector[256];
unsigned char keyStream[1920 * 1080];


int main()
{
	const int width = 1920;
	const int height = 1080;

	Image image(width, height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			image.SetColor (Color ((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
		}
	}
    std::cout << "Creating Test Image\n";
	image.Export("Image.bmp");

	Image PlainImage(0, 0);

    std::cout << "Import Firefly\n";
    PlainImage.Import("Firefly1.bmp");

	std::cout << PlainImage.m_colors[0].R * 255.0f << "\n";

    unsigned char keylen;
    unsigned char key_input;
    printf("Please Enter Key Length: ");
    std::cin >> keylen;
    //scanf("%lu", &keylen);
    printf("Please Enter Key: ");
    std::cin >> key_input;
    //scanf("%lu", &key_input);
    unsigned char* key_arr = new unsigned char(keylen);
    //unsigned char* keyStream_Green = new unsigned char(PlainImage.m_height * PlainImage.m_width);
    //unsigned char* keyStream_Blue = new unsigned char(PlainImage.m_height * PlainImage.m_width);
    for (unsigned long i = 1; i <= keylen; i++)
    {
        key_arr[keylen - i] = key_input % (10);
        key_input = key_input / (10);
    }

    S_vector_init();
    T_vector_init(key_arr, keylen);
    KSA_Algorithm(T_vector, keylen);
    PRGA_Algorithm(keyStream);
    /*
    for (unsigned long i = 0; i < PlainImage.m_height * PlainImage.m_width; i++)
    {
        keyStream_Green[i] = keyStream_Red[i];
        keyStream_Blue[i] = keyStream_Red[i];
    }
    */

    
    Image CipherImage(PlainImage.m_width, PlainImage.m_height);
    for (unsigned long i = 0; i < PlainImage.m_height * PlainImage.m_width; i++)
    {
        CipherImage.m_colors[i].R = (unsigned char)(PlainImage.m_colors[i].R * 255.0f) ^ keyStream[i];
        CipherImage.m_colors[i].G = (unsigned char)(PlainImage.m_colors[i].G * 255.0f) ^ keyStream[i];
        CipherImage.m_colors[i].B = (unsigned char)(PlainImage.m_colors[i].B * 255.0f) ^ keyStream[i];
        CipherImage.m_colors[i].R /= 255.0f;
        CipherImage.m_colors[i].G /= 255.0f;
        CipherImage.m_colors[i].B /= 255.0f;
    }
    //printf("%f\n", (CipherImage.m_colors[0].R));
    //printf("%d\n", (unsigned char)(PlainImage.m_colors[0].R * 255.0f));

    std::cout << "Creating Cipher_Firefly1 Image\n";
    CipherImage.Export("Cipher_Firefly1.bmp");



    Image CopyImage(PlainImage.m_width, PlainImage.m_height);
    for (unsigned long i = 0; i < PlainImage.m_height * PlainImage.m_width; i++)
    {
        CopyImage.m_colors[i].R = (unsigned char)(CipherImage.m_colors[i].R * 255.0f) ^ keyStream[i];
        CopyImage.m_colors[i].G = (unsigned char)(CipherImage.m_colors[i].G * 255.0f) ^ keyStream[i];
        CopyImage.m_colors[i].B = (unsigned char)(CipherImage.m_colors[i].B * 255.0f) ^ keyStream[i];
        CopyImage.m_colors[i].R /= 255.0f;
        CopyImage.m_colors[i].G /= 255.0f;
        CopyImage.m_colors[i].B /= 255.0f;
    }
    
    std::cout << "Creating Copy_Firefly1 Image\n";
    CopyImage.Export("Copy_Firefly1.bmp");
}