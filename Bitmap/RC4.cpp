#include "RC4.h"
#define T_ELEMENT_MAX   (256)
#define S_ELEMENT_MAX   (T_ELEMENT_MAX)

extern unsigned char S_vector[256];
extern unsigned char T_vector[256];

void S_vector_init()
{
    for (unsigned short i = 0; i < T_ELEMENT_MAX; i++)
    {
        S_vector[i] = i;
    }
}

void T_vector_init(unsigned char key_arr[], unsigned long keylen)
{
    unsigned long temp_keylen = keylen;
    int temp = 0;
    for (unsigned short i = 0; i < T_ELEMENT_MAX; i++)
    {
        T_vector[i] = key_arr[temp];
        temp++;
        if (temp >= temp_keylen)
        {
            temp = 0;
        }
    }
}

void arr_swap(unsigned char* s, unsigned int i, unsigned int j)
{
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void KSA_Algorithm(unsigned char* key, unsigned long key_length)
{
    unsigned int j = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        j = (j + S_vector[i] + key[i]) % 256;
        arr_swap(S_vector, i, j);
    }
    j = 0;
}

void PRGA_Algorithm(unsigned char* keyStream)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int t;
    for (unsigned int r = 0; r < 1920 * 1080; r++)
    {
        i = (i + 1) % 256;
        j = (j + S_vector[i]) % 256;
        arr_swap(S_vector, i, j);
        t = (S_vector[i] + S_vector[j]) % 256;
        keyStream[r] = S_vector[t];
    }

}
