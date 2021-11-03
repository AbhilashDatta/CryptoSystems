#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to generate the 5x5 key square
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
	int i, j, k, flag = 0, *dicty;

	// a 26 character hashmap
	// to store count of the alphabet
	dicty = (int*)calloc(26, sizeof(int));
	for (i = 0; i < ks; i++) {
		if (key[i] != 'j')
			dicty[key[i] - 97] = 2;
	}

	dicty['j' - 97] = 1;

	i = 0;
	j = 0;

	for (k = 0; k < ks; k++) {
		if (dicty[key[k] - 97] == 2) {
			dicty[key[k] - 97] -= 1;
			keyT[i][j] = key[k];
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}

	for (k = 0; k < 26; k++) {
		if (dicty[k] == 0) {
			keyT[i][j] = (char)(k + 97);
			j++;
			if (j == 5) {
				i++;
				j = 0;
			}
		}
	}
}

void search(char keyT[5][5], char a, char b, int arr[]){
	int i, j;

	if (a == 'j')
		a = 'i';
	else if (b == 'j')
		b = 'i';

	for (i = 0; i < 5; i++) {

		for (j = 0; j < 5; j++) {

			if (keyT[i][j] == a) {
				arr[0] = i;
				arr[1] = j;
			}
			else if (keyT[i][j] == b) {
				arr[2] = i;
				arr[3] = j;
			}
		}
	}
}

// Function to make the plain text length to be even
int prepare(char str[], int ptrs)
{
	if (ptrs % 2 != 0) {
		str[ptrs++] = 'x';
		str[ptrs] = '\0';
	}
	return ptrs;
}

char* Encrypt(char str[], char key[]){
    char ps, ks, keyT[5][5];
	ks = strlen(key);
	ps = strlen(str);

	ps = prepare(str, ps);
	generateKeyTable(key, ks, keyT);

	int i, a[4];

	for (i = 0; i < ps; i += 2) {

		search(keyT, str[i], str[i + 1], a);

		if (a[0] == a[2]) {
			str[i] = keyT[a[0]][(a[1] + 1)%5];
			str[i + 1] = keyT[a[0]][(a[3] + 1)%5];
		}
		else if (a[1] == a[3]) {
			str[i] = keyT[(a[0] + 1)%5][a[1]];
			str[i + 1] = keyT[(a[2] + 1)%5][a[1]];
		}
		else {
			str[i] = keyT[a[0]][a[3]];
			str[i + 1] = keyT[a[2]][a[1]];
		}
	}

    return str;
}

char* Decrypt(char str[], char key[]){
    char ps, ks, keyT[5][5];
	ks = strlen(key);
	ps = strlen(str);

	ps = prepare(str, ps);
	generateKeyTable(key, ks, keyT);

    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][(a[1] - 1)%5];
            str[i + 1] = keyT[a[0]][(a[3] - 1)%5];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[(a[0] - 1)%5][a[1]];
            str[i + 1] = keyT[(a[2] - 1)%5][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
    int len = strlen(str);
    while(str[--len]=='x') str[len] = '\0';
    
    return str;
}

int main(){
    char plaintext[1000];
    char key[25];

    printf("Enter Plain text: ");
    scanf("%[^\n]s", plaintext);
    printf("Enter key: ");
    scanf("%s",key);

    printf("\nEncrypting...\n");
    char* ciphertext = Encrypt(plaintext,key);
    printf("Cipher text: %s\n", ciphertext);

    printf("\nDecrypting...\n");
    char* real_message = Decrypt(ciphertext, key);
    printf("Real message: %s\n", real_message);

    return 0;
}
