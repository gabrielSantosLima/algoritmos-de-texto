#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASIZE 256
#define XSIZE 100
#define TEXTSIZE 100
#define true 1
#define false 0

typedef int bool;

typedef struct patternScanOrder
{
    int loc;
    char c;
} pattern;

int freq[ASIZE];

int MAX(int n1, int n2)
{
    if (n1 > n2)
        return n1;
    return n2;
}

void preQsBc(char *x, int m, int qsBc[])
{
    int i;

    for (i = 0; i < ASIZE; ++i)
        qsBc[i] = m + 1;
    for (i = 0; i < m; ++i)
        qsBc[x[i]] = m - i;
}

/* Construct an ordered pattern from a string. */
void orderPattern(char *x, int m, int (*pcmp)(),
                  pattern *pat)
{
    int i;

    for (i = 0; i <= m; ++i)
    {
        pat[i].loc = i;
        pat[i].c = x[i];
    }
    qsort(pat, m, sizeof(pattern), pcmp);
}

/* Optimal Mismatch pattern comparison function. */
int optimalPcmp(pattern *pat1, pattern *pat2)
{
    float fx;

    fx = freq[pat1->c] - freq[pat2->c];
    return (fx ? (fx > 0 ? 1 : -1) : (pat2->loc - pat1->loc));
}

/* Find the next leftward matching shift for
   the first ploc pattern elements after a
   current shift or lshift. */
int matchShift(char *x, int m, int ploc,
               int lshift, pattern *pat)
{
    int i, j;

    for (; lshift < m; ++lshift)
    {
        i = ploc;
        while (--i >= 0)
        {
            if ((j = (pat[i].loc - lshift)) < 0)
                continue;
            if (pat[i].c != x[j])
                break;
        }
        if (i < 0)
            break;
    }
    return (lshift);
}

/* Constructs the good-suffix shift table
   from an ordered string. */
void preAdaptedGs(char *x, int m, int adaptedGs[],
                  pattern *pat)
{
    int lshift, i, ploc;

    adaptedGs[0] = lshift = 1;
    for (ploc = 1; ploc <= m; ++ploc)
    {
        lshift = matchShift(x, m, ploc, lshift, pat);
        adaptedGs[ploc] = lshift;
    }
    for (ploc = 0; ploc <= m; ++ploc)
    {
        lshift = adaptedGs[ploc];
        while (lshift < m)
        {
            i = pat[ploc].loc - lshift;
            if (i < 0 || pat[ploc].c != x[i])
                break;
            ++lshift;
            lshift = matchShift(x, m, ploc, lshift, pat);
        }
        adaptedGs[ploc] = lshift;
    }
}

/* Optimal Mismatch string matching algorithm. */
void OM(char *x, int m, char *y, int n, int *output)
{
    int i, j, adaptedGs[XSIZE], qsBc[ASIZE];
    pattern pat[XSIZE];

    // Prepare outuput array of positions
    int currentIndex = 0;
    for (int index = 0; index < XSIZE; index++)
        output[index] = -1;

    /* Preprocessing */
    orderPattern(x, m, optimalPcmp, pat);
    preQsBc(x, m, qsBc);
    preAdaptedGs(x, m, adaptedGs, pat);

    /* Searching */
    j = 0;
    while (j <= n - m)
    {
        i = 0;
        while (i < m && pat[i].c == y[j + pat[i].loc])
            ++i;
        if (i >= m)
        {
            output[currentIndex] = j;
            currentIndex++;
        }
        j += MAX(adaptedGs[i], qsBc[y[j + m]]);
    }
}

typedef struct pet
{
    char especie[TEXTSIZE];
    char nome[TEXTSIZE];
    char raca[TEXTSIZE];
} pet;

bool e_cachorro(pet npet)
{
    int out[XSIZE];
    OM("cachorro", 8, npet.especie, strlen(npet.especie), out);
    if (out[0] == -1)
        return false;
    return out[0] == 0 && strlen(npet.especie) == 8;
}

bool tem_nome_composto(pet npet)
{
    int out[XSIZE];
    OM(" ", 1, npet.nome, strlen(npet.nome), out);
    if (out[0] == -1)
        return false;
    return true;
}

bool comeca_com_caracter(pet npet)
{
    char raca = npet.raca[0];
    if (npet.nome[0] == raca)
        return true;
    int out[XSIZE];
    int aux = -1;
    int currentIndex = 0;
    OM(" ", 1, npet.nome, strlen(npet.nome), out);
    aux = out[currentIndex];
    while (aux != -1)
    {
        char c = npet.nome[aux + 1];
        if (c == raca)
            return true;
        currentIndex++;
        aux = out[currentIndex];
    }
    return false;
}

int main()
{
    int n = 0;
    int out = 0;
    scanf("%d", &n);
    fflush(stdin);
    for (int index = 0; index < n; index++)
    {
        pet npet;
        scanf("%[^\n]%*c", npet.especie);
        scanf("%[^\n]%*c", npet.raca);
        scanf("%[^\n]%*c", npet.nome);
        fflush(stdin);
        if (e_cachorro(npet) && tem_nome_composto(npet) && comeca_com_caracter(npet))
            out++;
        char ch;
        scanf("%c", &ch);
    }
    printf("%d\n", out);
    return 0;
}