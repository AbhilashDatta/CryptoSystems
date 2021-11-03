#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int* generate_random_key(int n){

    int* r = malloc(n * sizeof(int));
    for(int i=0;i<n;++i){
        r[i]=i+1;
    }

    for (int i = n-1; i >= 0; --i){
        srand(time(0));
        int j = rand() % (i+1);

        int temp = r[i];
        r[i] = r[j];
        r[j] = temp;
    }
    
    return r;

}

char* Encrypt(char* plaintext, char* key, int m){
    int i=0;
   
    while(plaintext[i]!='\0') i++;

    int len = i;
    
    int temp_len = len;
    while(temp_len%m!=0) temp_len++;

    char str[temp_len+1];

    // x stand for buffer padding
    for(int i=0;i<temp_len;i++){
        str[i] = 'x';
    }
    str[temp_len] = '\0';

    i = 0;

    for(char* c=plaintext; *c!='\0'; c++){
        str[(i/m)*m+key[i%m]-'1'] = *c-'a'+'A';
        i++;
    }

    strcpy(plaintext, str);

    return plaintext;
}

char* Decrypt(char ciphertext[], char* key, int m){
    int i=0;
    
    while(ciphertext[i]!='\0') i++;
    
    int len = i;
    char plaintext[len+1];
    
    for(int i=0;i<len;i++){
        plaintext[i] = 'x';
    }

    char pi_inverse[m];

    for(int i=0;i<m;i++){
        pi_inverse[key[i]-'1'] = i+'1';
    }
    
    i = 0;

    for(char* c=ciphertext; *c!='\0'; c++){
        if(*c=='x'){
            plaintext[(i/m)*m+pi_inverse[i%m]-'1'] = '\0';
        }
        else{
            plaintext[(i/m)*m+pi_inverse[i%m]-'1'] = *c-'A'+'a';
        }
        i++;
    }
    
    strcpy(ciphertext, plaintext);
    ciphertext[len] = '\0';
    return ciphertext;
}

int main(){
    int m;
    printf("Enter the value of m: ");
    scanf("%d",&m);

    printf("Generating random key: ");
    int *key = generate_random_key(m);
    for(int i=0;i<m;i++){
        printf("%d", key[i]);
    } 
    printf("\n");

    char plaintext[1000];
    char keyword[m];
    getchar();
    printf("\nEnter Plain text: ");
    scanf("%s", plaintext);
    printf("Enter key: ");
    scanf("%s", keyword);
    
    printf("\nEncrypting Plain Text...\n");
    char* ciphertext = Encrypt(plaintext, keyword, m);
    printf("Cipher text: %s\n", ciphertext);
    
    printf("\nDecrypting Cipher Text...\n");
    char* real_message = Decrypt(ciphertext, keyword, m);
    printf("Real message: %s\n", real_message);
    
    return 0;
}
