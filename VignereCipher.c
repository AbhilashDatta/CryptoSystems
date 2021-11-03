#include<stdio.h>

char* Encrypt(char* plaintext, char* keyword, int m){
    int i = 0;
    
    if(keyword[0]>='A' && keyword[0]<='Z'){
        for(int i=0;i<m;i++){
            keyword[i] = keyword[i]-'A'+'a';
        }
    }

    for(char* c=plaintext; *c!='\0';c++){
        if(*c==' ') continue;

        int adder = *(keyword+i%m)-'a';
        int temp = (*c-'a'+adder)%26;
        *c = temp+'A';
        i++;
    }

    return plaintext;
}

char* Decrypt(char* ciphertext, char* keyword, int m){
    int i=0;

    if(keyword[0]>='A' && keyword[0]<='Z'){
        for(int i=0;i<m;i++){
            keyword[i] = keyword[i]-'A'+'a';
        }
    }

    for(char* c=ciphertext; *c!='\0'; c++){
        if(*c==' ') continue;

        int sub = *(keyword+i%m)-'a';
        int temp = *c-'A'-sub;
        while(temp<0){
            temp += 26;
        }

        temp = temp%26;
        *c = temp+'a';
        i++;
    }

    return ciphertext;
}

int main(){
    char plaintext[1000];
    printf("Enter Plain text: ");
    scanf("%[^\n]s", plaintext);

    int m;
    printf("Enter the value of m: ");
    scanf("%d",&m);

    char keyword[m];
    printf("Enter the keyword: ");
    scanf("%s", keyword);

    printf("\nEncrypting Plain Text...\n");
    char* ciphertext = Encrypt(plaintext, keyword, m);
    printf("Cipher text: %s\n", ciphertext);

    printf("\nDecrypting Cipher Text...\n");
    char* real_message = Decrypt(ciphertext, keyword, m);
    printf("Real message: %s\n", real_message);

    return 0;
}