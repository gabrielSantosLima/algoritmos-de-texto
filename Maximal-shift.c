#include <stdio.h>
#include <string.h>

// Calcular o array de deslocamento de caracteres inválidos para o padrão
void preprocess_bad_char(char *pattern, int m, int *bad_char) 
{
    for (int i = 0; i < m; i++) 
        bad_char[(int) pattern[i]] = i;
}


void maximal_shift(char *text, int n, char *pattern, int m, int *bad_char, int *result) 
{
    int i, j, shift, bad_char_index;
    int comparisons = 0;
    i = 0;
    
    while (i < n) 
    {
        j = m - 1;
        while (j >= 0 && text[i+j] == pattern[j]) 
        {
            j--;
            comparisons++;
        }

        if (j == -1) 
        {
            result[0] = i;
            result[1] = comparisons;
            return;

        } else 
        {
            bad_char_index = (int) text[i+j];
            shift = j - bad_char[bad_char_index];
            
            if (shift <= 0) 
            {
                shift = 1;
            }
            i += shift;
            comparisons++;
        }
    }
    result[0] = -1;
    result[1] = comparisons;
}


// Procura o padrão no texto usando o algoritmo de deslocamento máximo
void search(char *text, int n, char *pattern, int m) 
{
    int result[2];
    int bad_char[8];
    
    preprocess_bad_char(pattern, m, bad_char);
    maximal_shift(text, n, pattern, m, bad_char, result);
    
    if (result[0] == -1) 
        printf("O padrao nao foi encontrado no texto\n");
    else 
        printf("O padrao foi encontrado na posicao %d no texto\n", result[0]);

    printf("Numero de comparacoes: %d\n", result[1]);
}


int main() 
{
    char text[] = "GCATCGCAGAGAGTATACAGTACG";
    char pattern[] = "GCAGAGAG";
    int n = strlen(text);
    int m = strlen(pattern);
    search(text, n, pattern, m);
    return 0;
}
