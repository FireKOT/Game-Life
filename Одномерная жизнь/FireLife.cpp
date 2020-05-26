#include "TXLib.h"

int Fink(int n0, int n1, int n2);

int main()
{
    int num;
    scanf("%d", &num);
    int turn1[num];
    int turn2[num];

    for(int n  = 0; n < num-1; n++)
    {
        turn1[n] = rand() % 2;
        if(turn1[n] == 0) printf(" ");
            else printf("*");
    }
    printf("\n");
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        for(int n = 0; n < num; n++)
        {
            if(n-1 < 0) turn1[n-1] = turn1[0];
            turn2[n] = Fink(turn1[(num+n-1)%num], turn1[n], turn1[(n+1)%num]);
        }
        for(int n = 0; n < num; n++)
        {
            turn1[n] = turn2[n];
            if(turn2[n] == 0) printf(" ");
                else printf("*");
        }
        printf("\n");
        Sleep(50);
    }
    return 0;
}

int Fink(int n0, int n1, int n2)
{
    if((n0+n2 == 1) || ((n0+n2) && n1 == 0)) n1 = 1;
    else n1 = 0;
    return n1;
}
