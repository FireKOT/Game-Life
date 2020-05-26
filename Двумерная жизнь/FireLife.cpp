#include "TXLib.h"

int Think(int kat);
void Print(int kat);

int main()
{
    int x, y, kot, tok, life, fake;
    FILE *file;
    file = fopen("gopa.txt","r");
    if(file == NULL) printf("Error!");
    fscanf(file, "%d %d", &x, &y);
    int mas[x][y];
    int KOT[x][y];
    for(int num = 0; num < x; num++)
        for(int lib = 0; lib < y; lib++)
            fscanf(file, "%d", &mas[num][lib]);
    fclose(file);

    for(int num = 0; num < 101; num++)
    {
        for(int num = 0; num < x; num++)
            for(int lib = 0; lib < y; lib++)
            {
                life = 0;
                for(kot = num-1; kot < num+2; kot++)
                    for(tok = lib-1; tok < lib+2; tok++)
                        if(mas[(x+kot)%x][(y+tok)%y] == 1) life++;

                if(mas[num][lib] == 1) life--;
                if(life != 2) KOT[num][lib] = Think(life);
                    else KOT[num][lib] = mas[num][lib];
            }

        for(int num = 0; num < x; num++)
        {
            for(int lib = 0; lib < y; lib++)
            {
                if(mas[num][lib] == 1) printf("#");
                    else printf(" ");
                mas[num][lib] = KOT[num][lib];
            }
            printf("\n");
        }
        Sleep(70);
        system("cls");
    }
    FILE *fi;
    fi = fopen("rio.txt", "w");
    if(file == NULL) printf("Error!");
    for(int num = 0; num < x; num++)
    {
        for(int lib = 0; lib < y; lib++)
            fprintf(fi, "%d", mas[num][lib]);
        printf("\n");
    }
    fclose(fi);

    return 0;
}

int Think(int kat)
{
    int what;
    if(kat < 2 || kat > 3) what = 0;
    else what = 1;
    return what;
}
