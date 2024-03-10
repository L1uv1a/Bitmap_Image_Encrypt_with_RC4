#include <iostream>
#include <stdio.h>
using namespace std;

#define T_ELEMENT_MAX   (256)
#define S_ELEMENT_MAX   (T_ELEMENT_MAX)

unsigned char S_vector[256];
unsigned char T_vector[256];

void S_vector_init();
void T_vector_init(unsigned char key_arr[], unsigned long keylen);
void arr_swap(unsigned char *s, unsigned int i, unsigned int j);
void KSA_Algorithm(unsigned char *key, unsigned long key_length);
void PRGA_Algorithm(unsigned char *keyStream, string PT);

int main()
{
    unsigned long keylen;
    unsigned long key_input;
    string PlainText;
    string CipherText;
    printf("Please Enter Key Length: ");
    scanf("%lu" ,&keylen);
    printf("Please Enter Key: ");
    scanf("%lu" ,&key_input);
    printf("Please Plain Text: ");
    cin>>PlainText;
    CipherText = PlainText;
    unsigned char* key_arr = new unsigned char(keylen);
    unsigned char* keyStream = new unsigned char(PlainText.length());
    for (unsigned long i = 1; i<=keylen; i++)
    {
        key_arr[keylen - i] = key_input % ( 10 );
        key_input = key_input/( 10 );
    }
    S_vector_init();
    T_vector_init(key_arr, keylen);
    KSA_Algorithm(T_vector, keylen);
    PRGA_Algorithm(keyStream, PlainText);
    for (int i = 0; i<PlainText.length(); i++)
    {
        CipherText[i] = PlainText[i] ^ keyStream[i];
    }
    cout<<"Encrypt: "<<CipherText<<endl;

    for (int i = 0; i<PlainText.length(); i++)
    {
        CipherText[i] = CipherText[i] ^ keyStream[i];
    }
    cout<<"Decrypt: "<<CipherText;

    return 0;
}

void S_vector_init()
{
    for (unsigned short i = 0; i<T_ELEMENT_MAX; i++)
    {
        S_vector[i] = i;
    }
}

void T_vector_init(unsigned char key_arr[], unsigned long keylen)
{
	unsigned long temp_keylen = keylen;
    int temp = 0;
    for (unsigned short i = 0; i<T_ELEMENT_MAX; i++)
    {
        T_vector[i] = key_arr[temp];
        temp++;
        if(temp >= temp_keylen)
        {
            temp = 0;
        }
    }
}

void arr_swap(unsigned char *s, unsigned int i, unsigned int j) 
{
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void KSA_Algorithm(unsigned char *key, unsigned long key_length)
{
    unsigned int j = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        j = ( j + S_vector[i] + key[i] ) % 256;
        arr_swap(S_vector, i, j);
    }
    j = 0;
}


void PRGA_Algorithm(unsigned char *keyStream, string PT)
{
    int i = 0;
    int j = 0;
    for (int r = 0; r < PT.length(); r++)
    {
        i = ( i+1 ) % 256;
        j = ( j + S_vector[i] ) % 256;
        arr_swap(S_vector, i, j);
        int t = ( S_vector[i] + S_vector[j] ) % 256;
        keyStream[r] = S_vector[t];
    }

}