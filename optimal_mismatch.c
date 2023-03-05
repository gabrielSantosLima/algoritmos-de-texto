#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LEN 1000
#define MAX_PATTERN_LEN 100

// Constrói a tabela de saltos a partir do padrão
void build_skip_table(char pattern[], int table[][MAX_PATTERN_LEN])
{
    int i, j, m = strlen(pattern);
    // memset(table, 0, sizeof(table));
    for (i = 0; i < m; i++)
        for (j = m - 1; j >= 0; j--)
            if (pattern[j] == pattern[i])
                table[pattern[i]][j] = i - j;
            else
                table[pattern[j]][j] = i - j;
    for (i = 0; i < m; i++)
        for (j = 0; j < MAX_PATTERN_LEN; j++)
            if (table[i][j] == 0)
                table[i][j] = m - j - 1;
    for (i = 0; i < m; i++)
        for (j = m - 2; j >= 0; j--)
            if (table[pattern[j]][j] > m - j - 1)
                table[pattern[j]][j] = m - j - 1;
}

// Busca todas as ocorrências do padrão no texto utilizando a tabela de saltos
void search(char text[], char pattern[], int table[][MAX_PATTERN_LEN])
{
    int i, j, m = strlen(pattern), n = strlen(text);
    i = m - 1;
    while (i < n)
    {
        j = m - 1;
        while (j >= 0 && pattern[j] == text[i - m + 1 + j])
            j--;
        if (j < 0)
        {

            printf("Padrão encontrado na posição %d\n", i - m + 1);
            i++;
        }
        else
        {
            i += table[text[i]][j];
        }
    }
}

// Função principal
int main()
{
    char text[MAX_TEXT_LEN], pattern[MAX_PATTERN_LEN];
    int table[MAX_PATTERN_LEN][MAX_PATTERN_LEN];
    printf("Digite o texto: ");
    fgets(text, MAX_TEXT_LEN, stdin);
    printf("Digite o padrão: ");
    fgets(pattern, MAX_PATTERN_LEN, stdin);
    pattern[strcspn(pattern, "\n")] = 0; // Remove o caractere de quebra de linha do padrão
    build_skip_table(pattern, table);
    search(text, pattern, table);
    return 0;
}
