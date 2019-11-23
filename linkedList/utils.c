#include <stdio.h>

#include "utils.h"

// Implementações das funções.
void limpaBuffer() {
    int c;
    do {
        c = getchar();
    } while((c != '\n') && (c != EOF));
}

void lerString(char* string) {

    char temp;
    
    int i = 0;
    scanf("%c", &temp);
    
    while (temp != '\n') {
        
        // Concatenando o caractere armazenado em temp.
        string[i] = temp;
        i++;
        
        // Lendo nova palavra.
        scanf("%c", &temp);
    }
    
    // O último caractere da string é um zero sempre!!!
    string[i] = 0;
}
