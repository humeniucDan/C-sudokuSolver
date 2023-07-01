#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sn = 0, s[9][9], w = 0;
double chk_t = 0, bt_t = 0;

void p_mat(int** g)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) printf("%i ", g[i][j]);
        puts("");
    }

}

void fpr_mat(FILE *f2, int g[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) fprintf(f2, "%i ", g[i][j]);
        fprintf(f2, "\n");
    }
    fprintf(f2, "\n");
}

void pr_mat(int g[9][9])
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) printf("%i ", g[i][j]);
        puts("");
    }
}

int** make_vm(int gr[9][9])
{
    int** vm = (int*)malloc(9 * sizeof(int*));
    for(int i = 0; i < 9; i++) vm[i] = malloc(9 * sizeof(int));

    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) vm[i][j] = (gr[i][j] == 0 ? 1 : 0);
    return vm;
}

int chk(int r, int c, int val, int gr[9][9])
{
    clock_t t;
    t = clock();

    int vof = (r / 3)*3, hof = (c / 3)*3;

    for(int i = 0; i < 9; i++) if(gr[r][i] == val || gr[i][c] == val) return 0;

    for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(gr[i+vof][j+hof] == val) return 0;

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    chk_t += time_taken;

    return 1;
}

void bt(int x, int y, int gr[9][9], int** vm, int *sol)
{
    if(*sol) return;
    if(y == 9)
    {
        sn++;
        *sol = 1;
        //puts("solved");
        for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) if(gr[i][j] != s[i][j]) w++;
        return;
    }
    if(vm[y][x] == 1)
    {
        for(int i = 1; i <= 9; i++)
        {
            gr[y][x] = 0;
            if(chk(y, x, i, gr))
            {
                gr[y][x] = i;
                bt((x+1)%9, y+(x+1)/9, gr, vm, sol);
            }
        }
        gr[y][x] = 0;
    }
    else bt((x+1)%9, y+(x+1)/9, gr, vm, sol);
}

//int bt(int x, int y, int gr[9][9], int** vm)
//{
//    if(y == 9)
//    {
//        sn++;
//        //puts("solved");
//        for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) if(gr[i][j] != s[i][j]) w++;
//        return 1;
//    }
//    if(!vm[y][x]) return bt((x+1)%9, y+(x+1)/9, gr, vm);
//    for(int i = 1; i <= 9; i++)
//    {
//        if(chk(y, x, i, gr))
//        {
//            gr[y][x] = i;
//            if(bt((x+1)%9, y+(x+1)/9, gr, vm)) return 1;
//        }
//        gr[y][x] = 0;
//    }
//}

void solve(int grid[9][9])
{
    int sol = 0;
    clock_t t;
    t = clock();
    int** vm = make_vm(grid);
    bt(0, 0, grid, vm, &sol);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    bt_t += time_taken;
}

void in(FILE* f, int g[9][9], int s[9][9])
{
    char b;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            fscanf(f, "%c", &b);
            g[i][j] = (b == '.' ? 0 : b - '0');
        }
    }
    fscanf(f, "%c", &b);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            fscanf(f, "%c", &b);
            s[i][j] = b - '0';
        }
    }
    fscanf(f, "%c", &b);
    fscanf(f, "%c", &b);
}

/// se poate optimiza alegand mai bine celulele de test (acelea cu cele mai putine "variante" libere)

int main()
{
    int g[9][9];

    FILE *f = fopen("sudoku_puzzles.txt", "r");
    FILE *f2 = fopen("sp.txt", "w+");
    if(!f) return -999;
    for(int i = 0; i < 200; i++)
    {
        in(f, g, s);
        //fpr_mat(f2, g);
        solve(g);
        //solveSudoku(g, 0, 0);
        //fpr_mat(f2, g);
    }
    printf("\n%i solved in %i wrongs with %g sec checking time and %g sec time spent backtraking", sn, w, chk_t, bt_t);
    return 0;
}
