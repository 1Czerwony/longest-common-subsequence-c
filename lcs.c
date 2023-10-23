#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

void inicializar_vetores(char x[], char y[], int tam_x, int tam_y, FILE *saida) {
    printf("X = ");
    fprintf(saida, "X = ");
    for(int i = 0; i < tam_x; i++) {
        x[i] = 'A' + (rand() % 26);
        printf("%c", x[i]);
        fprintf(saida, "%c", x[i]);
    }
    printf("\nY = ");
    fprintf(saida, "\nY = ");
    for(int i = 0; i < tam_y; i++) {
        y[i] = 'A' + (rand() % 26);
        printf("%c", y[i]);
        fprintf(saida, "%c", y[i]);
    }
}

int max(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

int lcs(char x[], char y[], int m, int n) {
    int c[m+1][n+1];
    for(int i = 0; i <= m; i++)
        c[i][0] = 0;
    for(int j = 0; j <= n; j++)
        c[0][j] = 0;

    for(int i = 0; i <= m; i++)
        for(int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                c[i][j] = 0;
            else if (x[i-1] == y[j-1])
                c[i][j] = c[i-1][j-1] + 1;    
            else
                c[i][j] = max(c[i-1][j], c[i][j-1]);
        }
    return c[m][n];
}

int main() {
    srand(time(NULL));

    FILE *saida = fopen("saida.txt", "w");

    for(int i = 20; i < 140; i+=20) {
        int tam_x = rand() % i;
        int tam_y = rand() % i;

        char x[tam_x];
        char y[tam_y];

        printf("\n");
        fprintf(saida, "\n");
        inicializar_vetores(x, y, tam_x, tam_y, saida);
        printf("\nm = %d, n = %d\n", tam_x, tam_y);
        fprintf(saida, "\nm = %d, n = %d\n", tam_x, tam_y);
        printf("lcs = %d\n", lcs(x, y, tam_x, tam_y));
        fprintf(saida, "lcs = %d\n", lcs(x, y, tam_x, tam_y));
        printf("\n---------------------------------------------\n");
        fprintf(saida, "\n---------------------------------------------\n");
    }

    assert(lcs("ABCB", "BDCAB", 4, 5) == 3);
    assert(lcs("ABCBDAB", "BDCABA", 7, 6) == 4);

    return 0;
}