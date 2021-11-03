#include<stdio.h>

char* Encrypt(char* plaintext, int key){
    
    for(char *c = plaintext; *c!='\0'; c++){
        if(*c==' ') continue;

        char temp = *c-'a';
        temp = (temp+key)%26;
        *c = temp+'A';
    }

    return plaintext;
}

char* Decrypt(char* ciphertext, int key){

    for(char *c = ciphertext; *c!='\0'; c++){
        if(*c==' ') continue;

        char temp = *c-'A';
        while(temp-key<0) temp += 26;

        temp = (temp-key)%26;
        *c = temp+'a';
    }

    return ciphertext;
}

int main(){
    char plaintext[1000];
    int key;

    printf("Enter Plain text: ");
    scanf("%[^\n]s", plaintext);
    printf("Enter key: ");
    scanf("%d",&key);

    printf("\nEncrypting...\n");
    char* ciphertext = Encrypt(plaintext,key);
    printf("Cipher text: %s\n", ciphertext);

    printf("\nDecrypting...\n");
    char* real_message = Decrypt(ciphertext, key);
    printf("Real message: %s\n", real_message);

    return 0;
}