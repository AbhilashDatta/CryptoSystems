#include<stdio.h>
#include<stdlib.h>

int* Convert_char_to_binary(char* message, int length){
    int fin_length = length * 4;
    int* binary_message = (int*)malloc(sizeof(int) * fin_length);
    int i = 0, j = 0;
    while(i<length){
        for(int k=0;k<4;k++){
            binary_message[j] = (message[i]>>k) & 1;
            j++;
        }
        i++;
    }
    return binary_message;
}

char* Convert_binary_to_char(int* message, int length){
    int fin_length = length/4;
    char* fin_message = (char*)malloc(sizeof(char) * fin_length);
    int i=0,j=0;
    while(i<fin_length){
        int temp = 0;
        for(int k=0;k<4;k++){
            temp |= (1<<k) * message[j];
            j++;
        }
        fin_message[i] = (char)temp;
        i++;
    }
    return fin_message;
}

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
 
int intermediate_permutation[] = {
                                  16,  7, 20, 21,
                                  29, 12, 28, 17,
                                  1, 15, 23, 26,
                                  5, 18, 31, 10,
                                  2,  8, 24, 14,
                                  32, 27,  3,  9,
                                  19, 13, 30,  6,
                                  22, 11,  4, 25 };
 
int end_permutation[] = {
                         40,  8, 48, 16, 56, 24, 64, 32,
                         39,  7, 47, 15, 55, 23, 63, 31,
                         38,  6, 46, 14, 54, 22, 62, 30,
                         37,  5, 45, 13, 53, 21, 61, 29,
                         36,  4, 44, 12, 52, 20, 60, 28,
                         35,  3, 43, 11, 51, 19, 59, 27,
                         34,  2, 42, 10, 50, 18, 58, 26,
                         33,  1, 41,  9, 49, 17, 57, 25 };

int *applyPerm(int* original, int permuatation[], int l1){
    int *final = (int *)malloc(sizeof(int) * l1);
    for(int i=0;i<l1;i++){
        final[i] = original[permuatation[i]-1];
    }
    return final;
}

int *fiestel(int *message, int *key){
    int* nmessage = applyPerm(message, expansion, 48);
    int* fout = (int*)malloc(sizeof(int)*48);
    for(int i=0;i<48;i++){
        fout[i] = nmessage[i] ^ key[i];
    }
    
    int row_num, col_num, fin_val, j = 0;

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
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }  


    p = 30;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a6[row_num*16 + col_num];
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }

    p = 36;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a7[row_num*16 + col_num];
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    }  

    p = 42;
    row_num = fout[p+0]*2 + fout[p+5];
    col_num = fout[p+1]*8 + fout[p+2]*4 + fout[p+3]*2 + fout[p+4];
    fin_val = array_a8[row_num*16 + col_num];
    for(int k=0;k<4;k++){
        nmessage[j] = (fin_val>>k)&1;
        j++;
    } 

    nmessage = applyPerm(nmessage, intermediate_permutation, 32);

    return nmessage;
}

int *roundF(int* message, int* key){
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
    int *temp = fiestel(R0, key);
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

int* revRound(int* message, int* key){
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
    int *temp = fiestel(L0, key);
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

int* CyclicLS(int *key, int val){
    int* nkey = (int*) malloc(sizeof(key) * 56);
    int j = 0;
    for(int i=val;i<28;i++){
        nkey[j++] = key[i];
    }
    for(int i=0;i<val;i++){
        nkey[j++] = key[i];
    }
    return nkey;
}

int* keyScheduling(int* key, int roundNumber){
    int *nkey = applyPerm(key, key_permutation, 56);
    int* L = (int*)malloc(sizeof(int) * 28);
    int* R = (int*)malloc(sizeof(int) * 28);
    for(int i=0;i<28;i++){
        L[i] = nkey[i];
    }
    for(int i=28;i<56;i++){
        R[i-28] = nkey[i];
    }
    for(int i=0;i<=roundNumber;i++){
        L = CyclicLS(L, key_shift_sizes[i]);
        R = CyclicLS(R, key_shift_sizes[i]);
    }
    for(int i=0;i<28;i++){
        nkey[i] = L[i];
    }
    for(int i=0;i<28;i++){
        nkey[i+28] = R[i];
    }
    nkey = applyPerm(nkey, sub_key_permutation, 48);
    return nkey;
}

int *encrypt(int *message, int *key){
    message = applyPerm(message, message_permutation, 64);
    for(int i=0;i<16;i++){
        int* ki = keyScheduling(key, i);
        message = roundF(message, ki);
    }
    message = applyPerm(message, end_permutation, 64);
    return message;
}

int *decrypt(int* message, int *key){
    message = applyPerm(message, message_permutation, 64);
    for(int i=15;i>=0;i--){
        int* ki = keyScheduling(key, i);
        message = revRound(message, ki);
    }
    message = applyPerm(message, end_permutation, 64);
    return message;
}

int main(){
    printf("Enter length of message (length <= 16 && enter message without spaces) :- ");
    int length;
    scanf("%d", &length);
    printf("Enter message (Without spaces) :- ");
    char message[16];
    scanf("%s", message);
    for(int i=length;i<16;i++){
        message[i] = '#';
    }
    long long int k;
    printf("Enter key (64-bit integer) - ");
    scanf("%lld", &k);
    int* key = (int*) malloc(sizeof(int) * 64);
    int j = 0;
    for(int i=0;i<64;i++){
        key[j++] = (k>>i) & 1;
    }
    printf("Original message: ");
    
    int* binMessage = Convert_char_to_binary(message, 16);
    for(int i=0;i<64;i++){
        printf("%d", binMessage[i]);
    }
    printf("\n");
    
    int* encryptedMessage = encrypt(binMessage, key);
    printf("Encrypted message: ");
    for(int i=0;i<64;i++){
        printf("%d",encryptedMessage[i]);
    }
    printf("\n");
    int* decryptedMessage = decrypt(encryptedMessage, key);
    printf("Final message: ");
    for(int i=0;i<64;i++){
        printf("%d", decryptedMessage[i]);
    }
    printf("\n");
    return 0;
}