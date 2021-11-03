#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int* generate_random_permutation(int n, int seed){
    
    int* r = malloc(n * sizeof(int));
    for(int i=0;i<n;++i){
        r[i]=i;
    }

    for (int i = n-1; i >= 0; --i){
        srand(seed);
        int j = rand() % (i+1);

        int temp = r[i];
        r[i] = r[j];
        r[j] = temp;
    }
    return r;

}

int* generate_pi_s(int l, int seed){
    int x = 1<<l;
    return generate_random_permutation(x, seed);
}

int* generate_pi_s_inverse(int* pi_s, int l){
    int x = 1<<l;
    int* pi_s_inverse = (int*)malloc(sizeof(int)*x);
    for(int i=0;i<x;i++){
        pi_s_inverse[pi_s[i]] = i;
    }
    return pi_s_inverse;
}

int* generate_pi_p(int lm, int seed){
    return generate_random_permutation(lm, seed);
}

int* generate_pi_p_inverse(int* pi_p, int lm){
    int* pi_p_inverse = (int*)malloc(sizeof(int)*lm);
    for(int i=0;i<lm;i++){
        pi_p_inverse[pi_p[i]] = i;
    }
    return pi_p_inverse;
}

void generate_round_keys(char*** keyset, char* key, int r, int l, int m){
    int start = 0;
    *keyset = (char**)malloc((r+1)*sizeof(char*));

    for(int i=0;i<=r;i++){
        (*keyset)[i] = (char*)malloc(l*m*sizeof(char));
        for(int j=start;j<start+l*m;j++){
            (*keyset)[i][j-start] = key[j%(l*m)];
        }
        start+=l;
    }
}

char* Encrypt(char plaintext[], char** keyset, int* pi_s, int* pi_p, int l, int m, int r){

    char u[l*m+1], v[l*m+1], *k, Y[l*m+1];
    
    for(int i=0;i<r-1;i++){
        k = keyset[i];
        // printf("k: %s\n",k);

        for(int j=0;j<l*m;j++){
            u[j] = (plaintext[j]-'0')^(k[j]-'0')+'0';
        }
        
        // printf("u: %s\n",u);
        // printf("%ld\n",strlen(u));

        for(int j=0;j<l*m;j+=l){
            char b[l+1];
            for(int i=j;i<j+l;i++) b[i-j] = u[i];
            // printf("%s\n",b);
            int x = 0;
            for(int i=0;i<l;i++){
                x += (b[l-i-1]-'0')*(1<<i);
            }
            // printf("%d\n",x);
            x = pi_s[x];
            int i=l-1;
            // printf("%d\n",x);

            for(int i=0;i<l;i++){
                b[i] = '0';
            }

            while(x>0){
                b[i--] = x%2+'0';
                x /= 2;
            }
            b[l] = '\0';
            // printf("%s\n",b);
            for(int i=j;i<j+l;i++) v[i] = b[i-j]; 
            v[l*m] = '\0';
        }
        // printf("v: %s\n",v);

        for(int j=0;j<l*m;j++){
            plaintext[j] = v[pi_p[j]];
        }
        // printf("w: %s\n",plaintext);
    }

    k = keyset[r-1];
    // printf("k: %s\n",k);
    for(int j=0;j<l*m;j++){
        u[j] = (plaintext[j]-'0')^(k[j]-'0')+'0';
    }
    // printf("u: %s\n",u);
    for(int j=0;j<l*m;j+=l){
        char b[l+1];
        for(int i=j;i<j+l;i++) b[i-j] = u[i];
        
        int x = 0;
        for(int i=0;i<l;i++){
            x += (b[l-1-i]-'0')*(1<<i);
        }
        
        x = pi_s[x];
        int i=l-1;
        
        for(int i=0;i<l;i++) b[i] = '0';

        while(x>0){
            b[i--] = x%2+'0';
            x /= 2;
        }
        b[l] = '\0';

        for(int i=j;i<j+l;i++) v[i] = b[i-j]; 
        v[l*m] = '\0';
    }
    // printf("v: %s\n",v);

    k = keyset[r];
    // printf("k: %s\n",k);

    for(int j=0;j<l*m;j++){
        Y[j] = (v[j]-'0')^(k[j]-'0')+'0';
    }
    Y[l*m] = '\0';
    // printf("Y: %s\n",Y);

    strcpy(plaintext,Y);
    return plaintext;
}

char* Decrypt(char* ciphertext, char** keyset, int* pi_s_inverse, int* pi_p_inverse, int l, int m, int r){
    char u[l*m+1], v[l*m+1], w[l*m+1], *k, *Y;

    Y = ciphertext;
    k = keyset[r];

    for(int j=0;j<l*m;j++){
        v[j] = (Y[j]-'0')^(k[j]-'0')+'0';
    }
    v[l*m] = '\0';

    for(int j=0;j<l*m;j+=l){
        char b[l+1];
        for(int i=j;i<j+l;i++) b[i-j] = v[i];
        
        int x = 0;
        for(int i=0;i<l;i++){
            x += (b[l-i-1]-'0')*(1<<i);
        }
        
        x = pi_s_inverse[x];
        int i=l-1;
        
        for(int i=0;i<l;i++) b[i] = '0';

        while(x>0){
            b[i--] = x%2+'0';
            x /= 2;
        }
        b[l] = '\0';

        for(int i=j;i<j+l;i++) u[i] = b[i-j]; 
        u[l*m] = '\0';
    }

    k = keyset[r-1];
    for(int j=0;j<l*m;j++){
        w[j] = (u[j]-'0')^(k[j]-'0')+'0';
    }
    w[l*m] = '\0';

    for(int i=r-2;i>=0;i--){
        
        for(int j=0;j<l*m;j++){
            v[j] = w[pi_p_inverse[j]];
        }

        for(int j=0;j<l*m;j+=l){
            char b[l+1];
            for(int i=j;i<j+l;i++) b[i-j] = v[i];
           
            int x = 0;
            for(int i=0;i<l;i++){
                x += (b[l-i-1]-'0')*(1<<i);
            }
          
            x = pi_s_inverse[x];
            int i=l-1;
            
            for(int i=0;i<l;i++) b[i] = '0';

            while(x>0){
                b[i--] = x%2+'0';
                x /= 2;
            }
            b[l] = '\0';

            for(int i=j;i<j+l;i++) u[i] = b[i-j]; 
            u[l*m] = '\0';
        }

        k = keyset[i];
        
        for(int j=0;j<l*m;j++){
            w[j] = (u[j]-'0')^(k[j]-'0')+'0';
        }
        w[l*m] = '\0';      
    }

    strcpy(ciphertext, w);
    return ciphertext;

}

int main(){
    int l,m,r;
    printf("Enter the value of l: ");
    scanf("%d",&l);
    printf("Enter the value of m: ");
    scanf("%d",&m);
    printf("Enter the value of r: ");
    scanf("%d",&r);
    getchar();

    char plaintext[l*m];
    char key[32];

    printf("\nEnter Plain text (=l*m bits): ");
    scanf("%[^\n]s", plaintext);
    printf("Enter key (>=l*m bits): ");
    scanf("%s",key);

    int* pi_s = generate_pi_s(l, 1);
    int* pi_p = generate_pi_p(l*m, 2 );

    char** keyset; 
    generate_round_keys(&keyset,key,r,l,m);

    printf("\nEncrypting Plain Text...\n");
    char* ciphertext = Encrypt(plaintext, keyset, pi_s, pi_p, l, m, r); 
    printf("Cipher text: %s\n", ciphertext);
      
    int* pi_s_inverse = generate_pi_s_inverse(pi_s, l);
    int* pi_p_inverse = generate_pi_p_inverse(pi_p, l*m);

    printf("\nDecrypting Cipher Text...\n");
    char* real_message = Decrypt(ciphertext, keyset, pi_s_inverse, pi_p_inverse, l, m, r);
    printf("Real message: %s\n", real_message);
    return 0;

}