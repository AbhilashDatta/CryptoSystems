/*
Abhilash Datta
19CS30001
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int key_shift_sizes[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
 
int key_permutation[] = {
                         57, 49, 41, 33, 25, 17, 9,
                         1, 58, 50, 42, 34, 26, 18,
                         10, 2, 59, 51, 43, 35, 27,
                         19, 11, 3, 60, 52, 44, 36,
                         63, 55, 47, 39, 31, 23, 15,
                         7, 62, 54, 46, 38, 30, 22,
                         14, 6, 61, 53, 45, 37, 29,
                         21, 13, 5, 28, 20, 12, 4 };
 
int message_permutation[] = { 
                             58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17,  9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };
 
int sub_key_permutation[] = {
                             14, 17, 11, 24, 1, 5,
                             3, 28, 15, 6, 21, 10,
                             23, 19, 12,  4, 26, 8,
                             16, 7, 27, 20, 13, 2,
                             41, 52, 31, 37, 47, 55,
                             30, 40, 51, 45, 33, 48,
                             44, 49, 39, 56, 34, 53,
                             46, 42, 50, 36, 29, 32 };
 
int expansion[] =  {
                  32, 1, 2, 3, 4, 5,
                  4, 5, 6, 7, 8, 9,
                  8, 9, 10, 11, 12, 13,
                  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
                  20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29,
                  28, 29, 30, 31, 32, 1 };
 
int array_a1[] = {
                  14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };
 
int array_a2[] = {
                  15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };
 
int array_a3[] = {
                  10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };
 
int array_a4[] = { 
                  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
                  13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
                  10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                  3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 };
 
int array_a5[] = { 
                  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
                  14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                  4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
                  11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 };
 
int array_a6[] = {
                  12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                  10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                  4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 };
 
int array_a7[] = { 
                  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
                  13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
                  1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
                  6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 };
 
int array_a8[] = {
                  13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                  1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                  7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                  2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 };

int temp1[] = {
                  15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };

int temp2[] = {
                  12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                  10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                  9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                  4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 };
 
int intermediate_permutation[] = {
                                  16,  7, 20, 21,
                                  29, 12, 28, 17,
                                  1, 15, 23, 26,
                                  5, 18, 31, 10,
                                  2,  8, 24, 14,
                                  32, 27,  3,  9,
                                  19, 13, 30,  6,
                                  22, 11,  4, 25 };

int mid_permutation[] = {
                            16,  7, 20, 21,
                            29, 12, 28, 17,
                            1, 15, 23, 26,
                            5, 18, 31, 10,
                            2,  8, 24, 14,
                            32, 27,  3,  9,
                            19, 13, 30,  6,
                            22, 11,  4, 25 };
 
int final_permutation[] = {
                         40,  8, 48, 16, 56, 24, 64, 32,
                         39,  7, 47, 15, 55, 23, 63, 31,
                         38,  6, 46, 14, 54, 22, 62, 30,
                         37,  5, 45, 13, 53, 21, 61, 29,
                         36,  4, 44, 12, 52, 20, 60, 28,
                         35,  3, 43, 11, 51, 19, 59, 27,
                         34,  2, 42, 10, 50, 18, 58, 26,
                         33,  1, 41,  9, 49, 17, 57, 25 };

int end_permutation[] = {
                         40,  8, 48, 16, 56, 24, 64, 32,
                         39,  7, 47, 15, 55, 23, 63, 31,
                         38,  6, 46, 14, 54, 22, 62, 30,
                         37,  5, 45, 13, 53, 21, 61, 29,
                         36,  4, 44, 12, 52, 20, 60, 28,
                         35,  3, 43, 11, 51, 19, 59, 27,
                         34,  2, 42, 10, 50, 18, 58, 26,
                         33,  1, 41,  9, 49, 17, 57, 25 };

int *ApplyPermutation(int* orig, int permutation[], int l){
    int *final = (int *)malloc(sizeof(int) * l);
    for(int i=0;i<l;i++){
        final[i] = orig[permutation[i]-1];
    }
    return final;
}

int *Fiestel(int *message, int *key){
    int* nmessage = ApplyPermutation(message, expansion, 48);
    int* fout = (int*)malloc(sizeof(int)*48);
    for(int i=0;i<48;i++) fout[i] = nmessage[i] ^ key[i];
       
    int row_num;
    int col_num;
    int fin_val;
    int j = 0;

    int p = 0;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a1[row_num*16 + col_num];

    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }

    p = 6;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a2[row_num*16 + col_num];
    
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }    

    p = 12;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a3[row_num*16 + col_num];
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    } 

    p = 18;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a4[row_num*16 + col_num];
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }

    p = 24;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a5[row_num*16 + col_num];
    
    for(int k=0;k<4;k++) nmessage[j++] = (fin_val>>k)&1;
    
    p = 30;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a6[row_num*16 + col_num];
    
    for(int k=0;k<4;k++) nmessage[j++] = (fin_val>>k)&1;
    

    p = 36;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a7[row_num*16 + col_num];
    
    for(int k=0;k<4;k++) nmessage[j++] = (fin_val>>k)&1;
    
    p = 42;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a8[row_num*16 + col_num];
    
    for(int k=0;k<4;k++) nmessage[j++] = (fin_val>>k)&1;
    
    nmessage = ApplyPermutation(nmessage, intermediate_permutation, 32);

    return nmessage;
}

int *OneRoundFiestelEncryption(int* message, int* key){
    int L0[32];
    int R0[32];
    for(int i=0;i<32;i++){
        L0[i] = message[i];
    }
    for(int i=32;i<64;i++){
        R0[i-32] = message[i];
    }

    int *L1 = (int *)malloc(sizeof(int) * 32);
    int* R1 = (int *)malloc(sizeof(int) * 32);
    int *temp = Fiestel(R0, key);
    for(int i=0;i<32;i++){
        L1[i] = R0[i];
        R1[i] = temp[i] ^ L0[i];
    }

    int* final = (int *)malloc(sizeof(int) * 64);
    for(int i=0;i<32;i++){
        final[i] = L1[i];
    }
    for(int i=32;i<64;i++){
        final[i] = R1[i-32];
    }
    return final;
}

int* OneRoundFiestelDecryption(int* message, int* key){
    int L0[32];
    int R0[32];

    for(int i=0;i<32;i++){
        L0[i] = message[i];
    }
    for(int i=32;i<64;i++){
        R0[i-32] = message[i];
    }

    int *L1 = (int *)malloc(sizeof(int) * 32);
    int* R1 = (int *)malloc(sizeof(int) * 32);
    int *temp = Fiestel(L0, key);
    for(int i=0;i<32;i++){
        R1[i] = L0[i];
        L1[i] = temp[i] ^ R0[i];
    }

    int* final = (int *)malloc(sizeof(int) * 64);
    for(int i=0;i<32;i++){
        final[i] = L1[i];
    }
    for(int i=32;i<64;i++){
        final[i] = R1[i-32];
    }
    return final;
}

#define XT(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
#define mul(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * XT(x)) ^ ((y>>2 & 1) * XT(XT(x))) ^ ((y>>3 & 1) * XT(XT(XT(x)))) ^ ((y>>4 & 1) * XT(XT(XT(XT(x))))))

int SubByte(int x){
    int SBOX[256] =   
    {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 
    };
    return SBOX[x];
}

int SubByteInverse(int x)
{
    int inSBOX[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
    return inSBOX[x];
}

void SubBytes(int m[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=SubByte(m[i][j]);
        }
    }
}

void SubBytesInverse(int m[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=SubByteInverse(m[i][j]);
        }
    }
}

void LeftShift(int t[]){
    unsigned char k = t[0];
    t[0] = t[1]; t[1] = t[2]; t[2] = t[3];
    t[3] = k;
}

void RightShift(int t[]){
    int k=t[3];
    t[3]=t[2]; t[2]=t[1]; t[1]=t[0]; 
    t[0]=k;
}

void ShiftRows(int m[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<i;j++){
            LeftShift(m[i]);
        }
    }
}

void ShiftRowsInverse(int m[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<i;j++){
            RightShift(m[i]);
        }
    }
}

void MixColumns(int m[4][4]){
    unsigned char temp[4][4];
    for(int i=0;i<4;i++){
        unsigned char a = m[0][i],b = m[1][i], c = m[2][i], d = m[3][i];
        temp[0][i] = mul(a,0x02)^mul(b,0x03)^mul(c,0x01)^mul(d,0x01);
        temp[1][i] = mul(a,0x01)^mul(b,0x02)^mul(c,0x03)^mul(d,0x01);
        temp[2][i] = mul(a,0x01)^mul(b,0x01)^mul(c,0x02)^mul(d,0x03);
        temp[3][i] = mul(a,0x03)^mul(b,0x01)^mul(c,0x01)^mul(d,0x02);
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=temp[i][j];
        }
    }
}

void MixColumnsInverse(int m[4][4]){
    unsigned char temp[4][4];
    for(int i=0;i<4;i++){
        unsigned char a=m[0][i], b=m[1][i], c=m[2][i], d=m[3][i];
        temp[0][i] = mul(a,0x0e)^mul(b,0x0b)^mul(c,0x0d)^mul(d,0x09);
        temp[1][i] = mul(a,0x09)^mul(b,0x0e)^mul(c,0x0b)^mul(d,0x0d);
        temp[2][i] = mul(a,0x0d)^mul(b,0x09)^mul(c,0x0e)^mul(d,0x0b);
        temp[3][i] = mul(a,0x0b)^mul(b,0x0d)^mul(c,0x09)^mul(d,0x0e);
    }
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            m[i][j]=temp[i][j];
        }
    }
}

void AddRoundKey(int m[4][4],int key[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            unsigned char a=key[i][j]^m[i][j];
            m[i][j]=a;
        }
    }
}

void OneRoundAESEncryption(int m[4][4],int roundKey[4][4]){
    SubBytes(m);
    ShiftRows(m);
    MixColumns(m);
    AddRoundKey(m,roundKey);
}

void OneRoundAESDecryption(int m[4][4],int roundKey[4][4]){
    AddRoundKey(m,roundKey);
    MixColumnsInverse(m);
    ShiftRowsInverse(m);
    SubBytesInverse(m);
}

int* convToArray(int matrix[4][4]){
    int *r = (int*)malloc(128*sizeof(int));
    int k = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            int x = matrix[i][j];
            int l = 8;
            while(l--){
                r[k++] = x%2;
                x = x/2;
            }
            l=8;
            for(int m=0;m<l/2;m++){
                int temp = r[k-m-1];
                r[k-m-1] = r[k+m-8];
                r[k+m-8] = temp;
            }
        }
    }    
    return r;
}

int** convToMatrix(int* r){
    int** m = (int**)malloc(4*sizeof(int));
    int k=0;
    for(int i=0;i<4;i++){
        m[i] = (int*)malloc(4*sizeof(int));
        for(int j=0;j<4;j++){
            int n = 0;
            int l = 8;
            while(l--){
                n += r[k++]<<(l);
            }
            m[i][j] = n;
        }
    }
    return m;
}

void Encrypt(int matrix[4][4],int roundKey[4][4]){
    for(int i=0;i<5;i++){
        OneRoundAESEncryption(matrix, roundKey);
    }

    int* full_m = convToArray(matrix);
    int* full_k = convToArray(roundKey);
    
    for(int i=0;i<6;i++){
        int h1[64];
        int h2[64];
        int k1[64];
        int k2[64];

        for(int j=0;j<64;j++){
            h1[j] = full_m[j];
            h2[j] = full_m[64+j];
        }
        for(int j=0;j<48;j++){
            k1[j] = full_k[j];
            k2[j] = full_k[48+j];
        }
        int *cipher1 = OneRoundFiestelEncryption(h1,k1);
        int *cipher2 = OneRoundFiestelEncryption(h2,k2);

        for(int j=0;j<64;j++){
            full_m[j] = cipher1[j];
        }
        for(int j=0;j<64;j++){
            full_m[j+64] = cipher2[j];
        }
    }

    int** m = convToMatrix(full_m);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            matrix[i][j] = m[i][j];
    }

    for(int i=0;i<5;i++){
        OneRoundAESEncryption(matrix, roundKey);
    }    
}

void Decrypt(int matrix[4][4],int roundKey[4][4]){
    for(int i=0;i<5;i++){
        OneRoundAESDecryption(matrix, roundKey);
    }

    int* full_m = convToArray(matrix);
    int* full_k = convToArray(roundKey);
    
    for(int i=0;i<6;i++){
        int h1[64] ,h2[64], k1[64], k2[64];
        for(int j=0;j<64;j++){
            h1[j] = full_m[j];
            h2[j] = full_m[64+j];
        }
        for(int j=0;j<48;j++){
            k1[j] = full_k[j];
            k2[j] = full_k[48+j];
        }
        int *cipher1 = OneRoundFiestelDecryption(h1,k1);
        int *cipher2 = OneRoundFiestelDecryption(h2,k2);
        
        for(int j=0;j<64;j++){
            full_m[j] = cipher1[j];
        }

        for(int j=0;j<64;j++){
            full_m[j+64] = cipher2[j];
        }

    }

    int** m = convToMatrix(full_m);

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            matrix[i][j] = m[i][j];
    }

    for(int i=0;i<5;i++){
        OneRoundAESDecryption(matrix, roundKey);
    }    
}

int main(){
 
    int response;
    printf("\n\tCustomized Block Cipher\n\n==================MENU==================\n\n");
    printf("Press (1) for Encryption  \nPress (2) for Decryption\n");
    printf("Response: ");
    scanf("%d",&response);

    if(response==1){
        int matrix[4][4];
        int key[4][4];
        printf("\nEnter the plaintext in matrix form:\n");
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("\nEnter the round key in matrix form:\n");

        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                scanf("%d", &key[i][j]);
            }
        }

        Encrypt(matrix,key);

        printf("\nCipher Text:\n");
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }

    else{
        int matrix[4][4];
        int key[4][4];
        printf("\nEnter the ciphertext in matrix form:\n");
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("\nEnter the round key in matrix form:\n");
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                scanf("%d", &key[i][j]);
            }
        }
        
        Decrypt(matrix,key);

        printf("\nPlain Text:\n");
        
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
}