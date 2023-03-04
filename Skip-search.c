#include <stdio.h>
#include <string.h>


int skip_search(char* str, char* substr, int* num_comparacoes)
{
    int n = strlen(str);
    int m = strlen(substr);
    int skip[8];


    // Preencher a tabela de saltos com os valores apropriados
    for (int i = 0; i < m; i++)
        skip[substr[i]] = m - i - 1;


    // Realizar a busca
    int i = m + 1;
    int comparacoes = 0;
   
    while (i < n)
    {
        int j = m - 1;
        while (j >= 0 && str[i] == substr[j])
        {
            i--;
            j--;
            comparacoes++;
        }
        if (j == -1) {
            // Encontrou a substring
            *num_comparacoes = comparacoes;
            return i + 1;
           
        } else {
            i += skip[str[i]];
            comparacoes++;
        }
    }
    // Substring nao encontrada
    *num_comparacoes = comparacoes;
    return -1;
}


int main()
{
    char str[] = "GCATCGCAGAGAGTATACAGTACG";
    char substr[] = "GCAGAGAG";


    int num_comparacoes;
    int posicao = skip_search(str, substr, &num_comparacoes);
   
    if (posicao == -1)
        printf("A substring nao foi encontrada\n");
       
    else
    {
        printf("A substring foi encontrada na posicao %d\n", posicao);
        printf("Numero de comparacoes: %d\n", num_comparacoes);
    }
    return 0;
}
