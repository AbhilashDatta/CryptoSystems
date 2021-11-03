#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(char* x, char* y){
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

char* generate_random_key(char* key){
    for (int i = 25; i >= 0; --i){
        //generate a random number [0, n-1]
        srand(time(0));
        int j = rand() % (i+1);

        //swap the last element with element at random index
        swap(&key[i], &key[j]);
    }

    return key;
}

char* Encrypt(char* plaintext, char* key){
    int hash[26];

    for(int i=0;i<26;i++){
        hash[i] = key[i]-'a';
    }

    for(char* c=plaintext;*c!='\0';c++){
        if(*c==' ') continue;
        *c = 'A'+hash[*c-'a'];
    }

    return plaintext;
}

char* Decrypt(char* ciphertext, char* key){
    int hash[26];

    for(int i=0;i<26;i++){
        hash[key[i]-'a'] = i;
    }

    for(char* c=ciphertext;*c!='\0';c++){
        if(*c==' ') continue;
        *c = 'a'+hash[*c-'A'];
    }

    return ciphertext;
}

int main(){
    char inp[] = "abcdefghijklmnopqrstuvwxyz";
    printf("Generating random key: ");
    printf("%s\n", generate_random_key(inp));

    char plaintext[1000];
    char key[26];
    printf("\nEnter Plain text: ");
    scanf("%[^\n]s", plaintext);
    printf("Enter key: ");
    scanf("%s",key);

    printf("\nEncrypting Plain Text...\n");
    char* ciphertext = Encrypt(plaintext,key);
    printf("Cipher text: %s\n", ciphertext);

    printf("\nDecrypting Cipher Text...\n");
    char* real_message = Decrypt(ciphertext, key);
    printf("Real message: %s\n", real_message);
    
    return 0;
}