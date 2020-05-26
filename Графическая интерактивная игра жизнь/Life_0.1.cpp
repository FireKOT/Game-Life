#include <TXLib.h>

using namespace std;

class Life{
private:
    int x=0, y=0;
    vector < vector <int> > cells;

    bool clic=0;
    int RectX0=-1, RectY0=-1, RectX=-1, RectY=-1;

public:
    Life();
    void GetCells(int s, int h);
    void GiveCells();
    int check(int x0, int y0);
    void God();
    void Print();
    ~Life();
};

class Menu{
private:
    int x, y, factor;
    bool clic=0;
    int buttons[1];
    int cords[1][2];
    COLORREF Color[1][2];

public:
    Menu();
    void GetInfo(int x0, int y0, int factor0);
    int GiveInfo(int n);
    void ChengeButtons();
    void PrintButtons();
    ~Menu();
};



int main(){
    int x=100, y=100, factor=10, time=0;
    //cin >> x >> y;
    txCreateWindow(x*factor+12*factor, y*factor);
    txBegin();

    Life life;
    life.GetCells(x, y);

    Menu menu;
    menu.GetInfo(x, y, factor);

    while(!GetAsyncKeyState(VK_ESCAPE)){
        life.GiveCells();
        menu.ChengeButtons();
        life.Print();
        menu.PrintButtons();
        if(menu.GiveInfo(0)==0) life.God();

        txSleep(0);
    }

    txEnd();
    return 0;
}



Life::Life(){

}

void Life::GetCells(int s, int h){
    x=s, y=h;
    cells.resize(x, vector <int> (y, 0));

    cells[1][0]=1;
    cells[2][1]=1;
    cells[0][2]=1;
    cells[1][2]=1;
    cells[2][2]=1;
}

void Life::GiveCells(){
    RectX=txMouseX(), RectY=txMouseY();
    if(RectX%10!=0) RectX+=10;
    if(RectY%10!=0) RectY+=10;

    if(RectX0>1000) RectX0=1000;
    if(RectY0>1000) RectY0=1000;
    if(RectX>1000) RectX=1000;
    if(RectY>1000) RectY=1000;

    if(txMouseButtons()==1 && clic==0){
        clic=1;
        RectX0=txMouseX();
        RectY0=txMouseY();
    }
    else if(clic==1 && txMouseButtons()==0){
        clic=0;

        if(RectX0>RectX) swap(RectX, RectX0);
        if(RectY0>RectY) swap(RectY, RectY0);
        for(int i=RectX0/10; i<RectX/10; i++)
            for(int j=RectY0/10; j<RectY/10; j++)
                cells[i][j]=1;
    }
}

int Life::check(int x0, int y0){
    int tmp=0;
    for(int i=x0-1; i<x0+2; i++)
        for(int j=y0-1; j<y0+2; j++)
            if(cells[(x+i)%x][(y+j)%y]!=0) tmp++;

    if((tmp==3 && cells[x0][y0]==0) || ((tmp==3 || tmp==4) && cells[x0][y0]==1)) return 1;
    else return 0;
}

void Life::God(){
    int buf[x][y];
    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            buf[i][j]=cells[i][j];

    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            buf[i][j]=check(i, j);

    for(int i=0; i<x; i++)
        for(int j=0; j<y; j++)
            cells[i][j]=buf[i][j];
}

void Life::Print(){
    txSetColor(RGB(0, 0, 0));

    for(int i=0; i<x; i++){
        for(int j=0; j<y; j++){
            if(cells[i][j]==1) txSetFillColor(RGB(0, 255, 0));
            else txSetFillColor(RGB(150, 0, 150));

            txRectangle(i*10, j*10, i*10+10, j*10+10);
        }
    }

    if(clic==1){
        txSetColor(RGB(0, 255, 0));
        txLine(RectX0/10*10, RectY0/10*10, RectX0/10*10, RectY/10*10);
        txLine(RectX0/10*10, RectY0/10*10, RectX/10*10, RectY0/10*10);
        txLine(RectX/10*10, RectY0/10*10, RectX/10*10, RectY/10*10);
        txLine(RectX/10*10, RectY/10*10, RectX0/10*10, RectY/10*10);
    }
}

Life::~Life(){

}



Menu::Menu(){
    Color[0][0]=RGB(128, 0, 128);
    Color[0][1]=RGB(0, 255, 0);

    for(int i=0; i<1; i++)
        buttons[i]=0;
}

void Menu::GetInfo(int x0, int y0, int factor0){
    x=x0*factor0, y=y0*factor0, factor=factor0;

    for(int i=0; i<1; i++){
        cords[i][0]=x+factor;
        cords[i][1]=i*10*factor+factor;
    }
}

int Menu::GiveInfo(int n){
    return buttons[n];
}

void Menu::ChengeButtons(){
    if(clic==1 && txMouseButtons()==0 && !GetAsyncKeyState(VK_SPACE)) clic=0;

    for(int i=0; i<1; i++){
        if((txMouseX()>=cords[i][0] && txMouseX()<=cords[i][0]+10*factor && txMouseY()>=cords[i][1] && txMouseY()<=cords[i][1]+10*factor && txMouseButtons()==1)
           || GetAsyncKeyState(VK_SPACE) && clic==0){
            clic=1;
            buttons[i]++;
            buttons[i]%=2;
        }
    }
}

void Menu::PrintButtons(){
    txSetFillColor(RGB(0, 0, 0));
    txSetColor(RGB(0, 0, 0));
    txRectangle(x, 0, x+12*factor, y);

    for(int i=0; i<1; i++){
        txSetFillColor(Color[i][buttons[i]]);
        txSetColor(RGB(0, 0, 0));

        txRectangle(cords[i][0], cords[i][1], cords[i][0]+10*factor, cords[i][1]+10*factor);
    }
}

Menu::~Menu(){

}
