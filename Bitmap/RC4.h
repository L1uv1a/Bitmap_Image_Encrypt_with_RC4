#pragma once
#include <iostream>
#include <stdio.h>
#include "Image.h"



void S_vector_init();
void T_vector_init(unsigned char key_arr[], unsigned long keylen);
void arr_swap(unsigned char* s, unsigned int i, unsigned int j);
void KSA_Algorithm(unsigned char* key, unsigned long key_length);
void PRGA_Algorithm(unsigned char* keyStream);

