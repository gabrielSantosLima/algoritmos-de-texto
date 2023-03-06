#include <stdio.h>
#include <string.h>


int max(int x, int y){
    if(x > y){
        return x;
    }else{
        return y;
    }
}

int min(int x, int y){
    if(x > y){
        return y;
    }else{
        return x;
    }
}


/* Compute the next maximal suffix. */
void nextMaximalSuffix(char *z, int m, int *i, int *j, int *k, int *p) {

    char a, b;

    // Compara os caracteres nas posições (ip + k) e (jp + k)
    while (*j + *k < m) {
        a = z[*i + *k];
        b = z[*j + *k];

        // Se os caracteres forem iguais...
        if (a == b) 
        {

            // Se os valores de p e k forem iguais...
            if (*k == *p) { 
                (*j) += *p; 
                *k = 1; // k volta ao valor original
            }
            else
                ++(*k); 
        }
        else
        {
            // Se a for maior que b...
            if (a > b) {
                (*j) += *k;
                *k = 1;
                *p = *j - *i;
            }
            else {
                *i = *j;
                ++(*j);
                *k = *p = 1;
            }
        }
    }
}

/* String matching on ordered alphabets algorithm. */
void SMOA(char *x, int m, char *y, int n) {

    /*
        x: Array de caracteres com o padrão
        y: Array de caracteres com o texto 
        m: Tamanho do array x
        n: Tamanho do array y
    */

    int i, ip, j, jp, k, p;

    ip = -1;
    i = j = jp = 0;
    k = p = 1;

    /*
        i: Indica a posição analisada em x
        j: Indica a posição analisada em y
        ip e jp: Variáveis auxiliares para  indicar o maior sufixo comum entre x e a substring atual de y.
        k e p: Variáveis auxiliares para encontrar o sufixo máximo.
    */

    // Repete enquanto a string padrão couber na string texto
    while (j <= n - m) {

        /* Itera por x*/
        while (
            i + j < n && // Enquanto a soma dos indices for menor que o tamanho da string texto
            i < m &&  // Enquanto não chegar ao último caractere de x
            x[i] == y[i + j] // Enquanto houver match entre as strings.
        ) ++i;

        // Encontra o primeiro caractere coincidente
        if (i == 0) {
            ++j;
            ip = -1;
            jp = 0;
            k = p = 1;
        }
        else {
            // Coincidiu até último caractere de x? 
            // Printa a posição inicial do match na string y.
            if (i >= m) printf("Match at index %d\n", j); 


            // Algoritmo que passa pelo máximo de caracteres possíveis sem pular um possível match
            nextMaximalSuffix(y + j, i + 1, &ip, &jp, &k, &p);


            // Se tiver um sufixo máximo menor no sufixo atual
            if (ip < 0 || (ip < p && memcmp(y + j, y + j + p, ip + 1) == 0)) {
                j += p;
                i -= p;
                if (i < 0) i = 0; // Corrige para a posição inicial de x pois não pode ser menor que zero
                
                // se a distância for maior que p, subtrai-se p de j
                if (jp - ip > p) {
                    jp -= p;
                }
                // se for menor, reseta os valores auxiliares.
                else 
                {
                    ip = -1;
                    jp = 0;
                    k = p = 1;
                }
            }
            // Se não tive um sufixo máximo menor no sufixo atual
            else {
                // Reseta os valores auxiliares e incrementa j pela seguinte formula com os 
                j += (max(ip + 1, min(i - ip - 1, jp + 1)) + 1);
                i = jp = 0;
                ip = -1;
                k = p = 1;
            }

        }
    }
}

int main() {
    char text[] = "ABBBCCCC";
    char pattern[] = "BBC";

    SMOA(pattern, strlen(pattern), text, strlen(text));

    return 0;
}



