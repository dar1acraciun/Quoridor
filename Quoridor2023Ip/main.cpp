#include <iostream>
#include <cmath>
#include <string.h>
#include <graphics.h>
#include <winbgim.h>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

int iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8,turn=1,type,nrGarduri1=10,nrGarduri2=10,computer=0,computertactic1=0,computertactic2=0;
const int size = 17; // dimensiunea matricei
char nume1[100],nume2[100],castigator[100];
typedef char tabel[100];
/*vector <string> tabel;

/*
Pentru plasarea pionului si al gardului vom folosi click stanga
Cand plasam un gard, matricea va avea 0 in loc de 2 in memorie
*/

struct gard {
    int distanta;
    int operatie;
}d1nou[5];

struct init{
    int x1,y1,x2,y2;//coordonatele coltului de sus si coltului de jos al dreptunghiului;
    int info;
}tabla[17][17];//implementare tabla;

struct butoane{
    int x1,x2,y1,y2;
}Button2vs2,Buttoncomp, ButonAcasa;

struct mutare {
    int distanta; //distanta minima
    int operatie; //difera in functie de mutare
};

void initalizare(); //initializeaza tabla cu 2 si 1, 1 pentru pion, 2 pentru gard ||Daria
void initPion(int x, int y, int r, int color); //initializeaza un pion || Andrei
void initTable(); //deseneaza tabla in functie de valorile din matrice || Daria+Andrei
void stergereMutariPioni(); //coloreaza patratele disponibile din jur cu negru || Daria
int move(int iNew, int jNew); //verifica daca spatiul e valid si muta pionul ||
void transfClick(int &x, int &y); //transforma inputul din pixeli in memorie si apeleaza functia move in interior || Daria
int mutariPion(int x,int y); //inverzeste spatiile disponibile din jurul pionului || Daria
int castig(); //returneaza daca jocul s-a terminat sau nu; 1 sau 0 || Daria+Andrei
void alternanta(int &turn); //realizeaza alternanta mutarilor player 1(cel de jos), player 2(cel de sus) || Daria+Andrei
void initGard(int stanga, int sus, int dreapta, int jos, int color); //coloreaza gardul ||
bool InMat(int i, int j); //verifica daca i si j sunt coordonate valide n matrice si returneaza 1 || Andrei
int validareGard(int iStart, int jStart, int target); //returneaza 1 daca se poate pune gard si daca pionul mai are un drum de la pozitia sa in partea opusa || Andrei
void miscareimposibila();//in momentul in care plasati un gard incorect se va afisa mesajul || Daria
int putGard(int x, int y); //retuneaza 1 daca pune gard si 0 in caz contrar || Andrei+Daria
void endgame(); //afiseaza ecranul cu game over || Daria
void randomFences(); //genereaza garduri random || Andrei
void randomMoves(); //genereaza mutari random || Andrei
void alternantacomp(); //jocul cu computer || Andrei
void menu(); //meniul aplicatiei || Daria
int distantaMinima(int iStart, int jStart, int target); //returneaza distanta minima de la pozitia actuala a pionului, la locul unde castiga || Andrei
void alternantacompTactic(); //joaca contra computer tactic || Andrei
void afisgard();//afiseaza numarul de garduri disponibile || Daria
void afisturn();//afiseaza randul jucatorilor || Daria
void computerpage();//pagina care afiseaza nivele computerului || Daria
void alternantacompTacticMedium(); //nivel mediu de joc || Andrei
void classament();//se afiseaza tabelul cu ultimele 7 meciuri || Daria
void fisier();//retine numele din fisier pentru functia classament || Daria
void loadingPage();//grafica si la pagina cu bara de loading || Daria
void namepage1(); //realizeaza pagina in care primul player isi pune numele || Daria
void namepage2(); //realizeaza pagina in care al doilea player isi pune numele || Daria
void rulespage1();//prima pagina de help || Daria
void rulespage2();//a doua pagina de help || Daria
void rulespage3();//a treia pagina de help || Daria
void rulespage4();//a patra pagina de help || Daria
void rulespage5();//a cincea pagina de help || Daria




int distantaMinima(int iStart, int jStart, int target) {
    //in variabila target va fi linia la care trebuie sa ajunga pionul si vom folosi functia pentru ambii pioni
    int matriceDistanta[size][size] = {};
    int vectorDirectieX[] = {0, 0, -2, 2};
    int vectorDirectieY[] = {-2, 2, 0, 0};

    int matriceLee[size][size];
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //daca e spatiu ocupat cu gard
            if(tabla[i][j].info == 0 || (i % 2 == 1 && j % 2 == 1)) {
                matriceLee[i][j] = 1;
            }else if(tabla[i][j].info == 2) {
                //spatiu de gard
                matriceLee[i][j] = -1;
            }else matriceLee[i][j] = 0;
        }
    }
    matriceDistanta[iStart][jStart] = 1;
    queue< pair <int, int> > coada;
    coada.push(make_pair(iStart, jStart));
    while (coada.empty() == false)
    {
        int x = coada.front().first;
        int y = coada.front().second;
        coada.pop();
        for(int d = 0; d <= 3; d ++) {
            int iNou = vectorDirectieX[d] + x;
            int jNou = vectorDirectieY[d] + y;
            if(InMat(iNou, jNou) && matriceLee[iNou][jNou] == 0 && matriceDistanta[iNou][jNou] == 0) {
                if(d == 0) {
                    //directie in stanga
                    if(matriceLee[iNou][jNou + 1] == -1) {
                        matriceDistanta[iNou][jNou] = matriceDistanta[x][y] + 1;
                        coada.push(make_pair(iNou, jNou));
                    }
                }else if(d == 1) {
                    //directie in dreapta
                    if(matriceLee[iNou][jNou - 1] == -1) {
                        matriceDistanta[iNou][jNou] = matriceDistanta[x][y] + 1;
                        coada.push(make_pair(iNou, jNou));
                    }
                }else if(d == 2) {
                    //directie in jos
                    if(matriceLee[iNou + 1][jNou] == -1) {
                        matriceDistanta[iNou][jNou] = matriceDistanta[x][y] + 1;
                        coada.push(make_pair(iNou, jNou));
                    }
                }else if(d == 3) {
                    if(matriceLee[iNou - 1][jNou] == -1) {
                        matriceDistanta[iNou][jNou] = matriceDistanta[x][y] + 1;
                        coada.push(make_pair(iNou, jNou));
                    }
                }
            }
        }
    }
    int min = 2147483647;
    for(int i = 0; i<size; i += 2) {
        if(matriceDistanta[target][i] < min && matriceDistanta[target][i] != 0)
            min = matriceDistanta[target][i];
    }
    return min;
}
bool InMat(int i, int j) {
    return i >= 0 && j >= 0 && i < size && j < size;
}
int validareGard(int iStart, int jStart, int target) {
    //in variabila target va fi linia la care trebuie sa ajunga pionul si vom folosi functia pentru ambii pioni
    int matriceDistanta[size][size] = {};
    int vectorDirectieX[] = {0, 0, -1, 1};
    int vectorDirectieY[] = {-1, 1, 0, 0};

    int matriceLee[size][size];
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //daca e spatiu ocupat cu gard
            if(tabla[i][j].info == 0 || (i % 2 == 1 && j % 2 == 1)) {
                matriceLee[i][j] = 1;
            }else matriceLee[i][j] = 0;
        }
    }
    matriceDistanta[iStart][jStart] = 1;
    queue< pair <int, int> > coada;
    coada.push(make_pair(iStart, jStart));
    while (coada.empty() == false)
    {
        int x = coada.front().first;
        int y = coada.front().second;
        coada.pop();
        for(int d = 0; d <= 3; d++) {
            int iNou = vectorDirectieX[d] + x;
            int jNou = vectorDirectieY[d] + y;
            if(InMat(iNou, jNou) && matriceLee[iNou][jNou] == 0 && matriceDistanta[iNou][jNou] == 0) {
                matriceDistanta[iNou][jNou] = matriceDistanta[x][y] + 1;
                coada.push(make_pair(iNou, jNou));
            }
        }

    }
    for(int j = 0; j < size; j+=2) {
        if(matriceDistanta[target][j] != 0 )
            return 1;
    }
    return 0;
}
void initializare()//initializeaza tabla cu 2 si 1, 1 pentru pion, 2 pentru gard
{
    int constanta=1;
    for(int i = 0;i<17;i++){
        if(i%2==0){
            constanta=1;
            for(int j = 0;j<17;j++){
                tabla[i][j].info=constanta;
                constanta=3-constanta;}
        }else{
            constanta=2;
            for(int j=0;j<17;j++){
                tabla[i][j].info=constanta;
            }
        }
    }
}
void initPion(int x, int y, int r, int color) {//se coloreaza pionii
    setfillstyle(SOLID_FILL, color);
    setcolor(color);
    circle(x, y, r);
    floodfill(x, y, color);
}
void loadingPage(){
    initwindow(600,500,"Loading",150,50);
	int x=230,y=210;
	int n=1;
	int page=0;
	while(n<=101)
	{
		setactivepage(page);
		setvisualpage(1-page);//pentru a opri glitchurile
     settextstyle(8,HORIZ_DIR,3);
	 outtextxy(x,y,"Loading...");
	 setcolor(WHITE);
	 rectangle(600/2-101,500/2-2,600/2+102,500/2+20+2);
	 stringstream s;
	 s<<n<<'%';//se afiseaza numerele (1,2,'....100)
	 char ch[5];
	 s>>ch;
	 outtextxy(280,280,ch);
	 for(int i=1;i<=n*2;i++)
	 {
	 	line(600/2-100+i,500/2,600/2-100+i,500/2+20);//se umple bara de loading
	 }
	 n++;
	page=1-page;
	delay(30);

	}
}
void initTable(){
    loadingPage();
    closegraph();
    initwindow(1200,800,"QUORIDOR");
    nrGarduri1=10,nrGarduri2=10;
    iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8;
    ButonAcasa.x1 = 800, ButonAcasa.x2 = 1000, ButonAcasa.y1 = 600, ButonAcasa.y2 = 650;
    //setfillstyle(SOLID_FILL, WHITE);
    setcolor(WHITE);
    rectangle(ButonAcasa.x1, ButonAcasa.y1, ButonAcasa.x2, ButonAcasa.y2);
   // floodfill(ButonAcasa.x1 + 1, ButonAcasa.y1 + 1, WHITE);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(0);
    setcolor(15);
    outtextxy(812,614,"BACK TO MENU");
    setcolor(WHITE);
    initializare();
    int cX,cY;
    cX=cY=100;
    int dp,dg;//lungimea patrat-pion,gard
    dp=61;
    dg=6;
    for(int i=0;i<17;i++){//se creaza tabla
        cX = 100;
        if( i % 2 == 0 ) {
            for(int j = 0; j < 17; j++) {
                if(tabla[i][j].info == 1) {
                    rectangle(cX, cY, cX+dp, cY + dp);
                    tabla[i][j].x1=cX;
                    tabla[i][j].y1=cY;
                    tabla[i][j].x2=cX+dp;
                    tabla[i][j].y2=cY+dp;
                    cX = cX + dp;
                }else if(tabla[i][j].info == 2) {
                    rectangle(cX, cY, cX + dg, cY + dp);
                    tabla[i][j].x1=cX;
                    tabla[i][j].y1=cY;
                    tabla[i][j].x2=cX+dg;
                    tabla[i][j].y2=cY+dp;
                    cX = cX + dg;
                }
            }
            cY+=dp;
        }else{
            for(int j = 0; j<17; j++) {
                if(tabla[i - 1][j].info == 2) {
                    rectangle(cX, cY, cX + dg, cY + dg);
                    tabla[i][j].x1=cX;
                    tabla[i][j].y1=cY;
                    tabla[i][j].x2=cX+dg;
                    tabla[i][j].y2=cY+dg;
                    cX = cX + dg;
                }else {
                    rectangle(cX, cY, cX + dp, cY + dg);
                    tabla[i][j].x1=cX;
                    tabla[i][j].y1=cY;
                    tabla[i][j].x2=cX+dp;
                    tabla[i][j].y2=cY+dg;
                    cX = cX + dp;
                 }
              }
            cY = cY + dg;
        }
    }

    initPion(tabla[16][8].x1+(tabla[16][8].x2-tabla[16][8].x1)/2,tabla[16][8].y1+(tabla[16][8].y2-tabla[16][8].y1)/2,15,GREEN);//pionul de sus
    initPion(tabla[0][8].x1+(tabla[0][8].x2-tabla[0][8].x1)/2,tabla[0][8].y1+(tabla[0][8].y2-tabla[0][8].y1)/2,15,RED); //pionul de jos*/
    tabla[16][8].info = 3; //loc ocupat pentru pionul 1
    tabla[0][8].info = 4; //loc ocupat pentru pionul 2
   setfillstyle(SOLID_FILL,14);
   setcolor(14);
   rectangle(350,20,355,80);
   floodfill(351,21,14);
   rectangle(360,75,420,80);
   floodfill(361,76,14);
   rectangle(350,717,355,777);
   floodfill(351,718,14);
   rectangle(360,772,420,777);
   floodfill(361,773,14);
   setcolor(15);
   setbkcolor(0);

}
void afisgard(){
    setfillstyle(SOLID_FILL,0);
    bar(381,41,410,70);
    bar(381,731,410,770);
    setcolor(15);
    setbkcolor(0);
    int text2=textwidth(nume2),text1=textwidth(nume1);
    if(text2-100>0)
     outtextxy(250-text2+100-5,40,nume2);
     else outtextxy(250,40,nume2);
     if(text1-100>0)
     outtextxy(250-text1+100-5,735,nume1);
     else   outtextxy(250,735,nume1);
     stringstream s,b;
     char gard1[4],gard2[4];
     s<<nrGarduri1;
     b<<nrGarduri2;
     s>>gard1;
     b>>gard2;
    outtextxy(380,40,gard2);
    outtextxy(380,730,gard1);
}
void stergereMutariPioni(){
    int i,j;
    if(turn==1)
        i=iOld1,j=jOld1;
    else
        i=iOld2,j=jOld2;

    if((i-2) >=0 && tabla[i-2][j].info == 1&&tabla[i-1][j].info==2){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i-2][j].x1,tabla[i-2][j].y1,tabla[i-2][j].x2,tabla[i-2][j].y2);
        floodfill(tabla[i-2][j].x1+1,tabla[i-2][j].y1+1,15);
    }
    else if((i-4) >=0 && tabla[i-2][j].info != 1){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i-4][j].x1,tabla[i-4][j].y1,tabla[i-4][j].x2,tabla[i-4][j].y2);
        floodfill(tabla[i-4][j].x1+1,tabla[i-4][j].y1+1,15);
    }

    if((j-2)>=0 && tabla[i][j-2].info == 1&&tabla[i][j-1].info==2){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i][j-2].x1,tabla[i][j-2].y1,tabla[i][j-2].x2,tabla[i][j-2].y2);
        floodfill(tabla[i][j-2].x1+1,tabla[i][j-2].y1+1,15);
    }
    else if((j-4)>=0 && tabla[i][j-2].info != 1&&tabla[i][j-3].info==2){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i][j-4].x1,tabla[i][j-4].y1,tabla[i][j-4].x2,tabla[i][j-4].y2);
        floodfill(tabla[i][j-4].x1+1,tabla[i][j-4].y1+1,15);
    }

    if((j+2) <=16 && tabla[i][j+2].info == 1&&tabla[i][j+1].info==2){
        setfillstyle(SOLID_FILL,0);
        setcolor(15);
        rectangle(tabla[i][j+2].x1,tabla[i][j+2].y1,tabla[i][j+2].x2,tabla[i][j+2].y2);
        floodfill(tabla[i][j+2].x1+1,tabla[i][j+2].y1+1,15);
    }
    else if((j+4) <=16 && tabla[i][j+2].info != 1&&tabla[i][j+3].info==2){
        setfillstyle(SOLID_FILL,0);
        setcolor(15);
        rectangle(tabla[i][j+4].x1,tabla[i][j+4].y1,tabla[i][j+4].x2,tabla[i][j+4].y2);
        floodfill(tabla[i][j+4].x1+1,tabla[i][j+4].y1+1,15);
    }
    if((i+2) <=16 && tabla[i+2][j].info == 1&&tabla[i+1][j].info==2){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i+2][j].x1,tabla[i+2][j].y1,tabla[i+2][j].x2,tabla[i+2][j].y2);
        floodfill(tabla[i+2][j].x1+1,tabla[i+2][j].y1+1,15);
    }
    else if((i+4) <=16 && tabla[i+2][j].info != 1&&tabla[i+3][j].info==2){
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[i+4][j].x1,tabla[i+4][j].y1,tabla[i+4][j].x2,tabla[i+4][j].y2);
        floodfill(tabla[i+4][j].x1+1,tabla[i+4][j].y1+1,15);

    }
    if(i-2>=0&&tabla[i-2][j].info!=1&&tabla[i-1][j].info==2&&tabla[i-3][j].info!=2)
                 {
                     if(tabla[i-2][j-1].info==2&&j-1>=0){
                      setfillstyle(SOLID_FILL, 0);
                      setcolor(15);
                     rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                      floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                     }
                     if(tabla[i-2][j+1].info==2&&j+1<=16){
                     setfillstyle(SOLID_FILL, 0);
                     setcolor(15);
                     rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                     floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                     }

                 }
                 if(i+2<=16&&tabla[i+2][j].info!=1&&tabla[i+3][j].info!=2&&tabla[i+1][j].info==2)
                 {
                     if(j+2<=16&&tabla[i+2][j+1].info==2){
                     setfillstyle(SOLID_FILL, 0);
                     setcolor(15);
                     rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                     floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                     if(j-1>=0&&tabla[i+1][j-1].info==2){
                     setfillstyle(SOLID_FILL, 0);
                     setcolor(15);
                     rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                     floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                     }
                 }
                 if(j+2<=16&&tabla[i][j+2].info!=1&&tabla[i][j+3].info!=2){
                     if(i+2<=16&&tabla[i+1][j+2].info==2){
                     setfillstyle(SOLID_FILL, 0);
                     setcolor(15);
                     rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                     floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);

                     }
                     if(i-2>=0&&tabla[i-1][j+2].info==2){
                     setfillstyle(SOLID_FILL, 0);
                     setcolor(15);
                     rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                     floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                     }
                 }
                 if(j-2>=0&&tabla[i][j-2].info!=1&&tabla[i][j-3].info!=2&&tabla[i][j-1].info==2){
                       if(i+2<=16&&tabla[i+1][j-1].info==2){
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);

                       }
                       if(i-2>=0&&tabla[i-1][j-2].info==2)
                       {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                       }
                    }
        if(j==2&&tabla[i][j-2].info!=1&&tabla[i][j-1].info==2)
                {
                    if(tabla[i-1][j-2].info==2)
                    {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                    }
                    if(tabla[i+1][j-2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                     }
                }
                if(j==14&&tabla[i][j+2].info!=1&&tabla[i][j+1].info==2)
                {
                    if(tabla[i-1][j+2].info==2)
                    {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                        floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                    }
                    if(tabla[i+1][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                        floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                }
                if(i==17&&tabla[i-2][j].info!=1&&tabla[i-2][j].info==2)
                {
                    if(tabla[i-2][j-1].info==2)
                    {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                    }
                    if(tabla[i-2][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                     }
                }
                if(i==14&&tabla[i+2][j].info!=1&&tabla[i+2][j].info==2)
                {
                    if(tabla[i+2][j-1].info==2)
                    {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                    }
                    if(tabla[i+2][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 0);
                        setcolor(15);
                        rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                        floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                }
}
void transfClick(int &x, int &y) {
    //in momentul in care dam click, coordonatele aferente sunt incadrate intr un spatiu de pion
    for(int i = 0; i < 17; i ++)
        for(int j = 0; j<17 ;j ++)
            if(tabla[i][j].x1<=x && tabla[i][j].x2>=x && tabla[i][j].y1<=y && tabla[i][j].y2 >= y){
                    x=i;
                    y=j;
                }
}
void initGard(int stanga, int sus, int dreapta, int jos) {
    setfillstyle(SOLID_FILL, 14);//se coloreaza gardul cu galben
    setcolor(14);
    rectangle(stanga, sus, dreapta, jos);
    floodfill(stanga + 1, sus + 1, 14);
}
void miscareimposibila()//in momentul in care plasati un gard incorect se va afisa mesajul
{  if(!(computer==1&&turn==2)){
    setbkcolor(0);
    setcolor(RED);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(800,300,"MISCARE IMPOSIBILA!");
    delay(1000);
    bar(800,300,1200,350);}
}
int putGard(int x, int y) {

    if((turn == 1 && nrGarduri1 != 0) || (turn == 2 && nrGarduri2 != 0)){
        transfClick(x,y);
        int linie;
        int nrGarduri;
        if(turn==1)
            linie=0,nrGarduri=nrGarduri1;
        else linie=16,nrGarduri=nrGarduri2;
        if(x%2 == 0 && y%2 )//verticala
        {

                if(tabla[x][y].info==2 && tabla[x+2][y].info==2 && tabla[x + 1][y].info == 2 && x+2<=16&&nrGarduri){
                    tabla[x][y].info=0;
                    tabla[x + 1][y].info = 0;
                    tabla[x+2][y].info=0;
                    if(validareGard(iOld1, jOld1, 0) == 1 && validareGard(iOld2, jOld2, 16) == 1) {
                        initGard(tabla[x][y].x1,tabla[x][y].y1,tabla[x][y].x2,tabla[x][y].y2);
                        initGard(tabla[x][y].x2-5,tabla[x][y].y2,tabla[x+2][y].x1+5,tabla[x+2][y].y1);
                        initGard(tabla[x+2][y].x1,tabla[x+2][y].y1,tabla[x+2][y].x2,tabla[x+2][y].y2);
                        if(turn==1)
                            nrGarduri1--;
                        else nrGarduri2--;
                    }else {
                        tabla[x][y].info = 2;
                        tabla[x + 1][y].info = 2;
                        tabla[x+2][y].info = 2;
                        miscareimposibila();
                        return 0;
                    }
                    return 1;

                }
        }
        else if(y%2==0)//orizontala
        {
            if(tabla[x][y].info == 2 && tabla[x][y + 2].info == 2 && tabla[x][y + 1].info == 2 && y + 2 <= 16&&nrGarduri){
                tabla[x][y].info = 0;
                tabla[x][y + 1].info = 0;
                tabla[x][y + 2].info = 0;
                if(validareGard(iOld1, jOld1, 0) == 1 && validareGard(iOld2, jOld2, 16) == 1) {
                    initGard(tabla[x][y].x1,tabla[x][y].y1,tabla[x][y].x2,tabla[x][y].y2);
                    initGard(tabla[x][y].x2,tabla[x][y].y2-5,tabla[x][y+2].x1,tabla[x][y+2].y1+5);
                    initGard(tabla[x][y+2].x1,tabla[x][y+2].y1,tabla[x][y+2].x2,tabla[x][y+2].y2);
                    if(turn==1)
                            nrGarduri1--;
                    else nrGarduri2--;
                }else {
                    tabla[x][y].info = 2;
                    tabla[x][y + 1].info = 2;
                    tabla[x][y + 2].info = 2;
                    miscareimposibila();
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

int move(int iNew, int jNew) {
    transfClick(iNew, jNew);
    int iOld,jOld,turnp,color;
    if(turn == 1) {
        iOld=iOld1,jOld=jOld1,turnp=4,color=2;
    }else {
        iOld=iOld2,jOld=jOld2,turnp=3,color=4;
    }

    /*
    mai intai vom vedea miscarile simple de o patratica, cand nu avem pionul advers in cale

    mutarile simple sunt : sus, jos, stanga, dreapta

    pentru a executa aceste mutari, pionul trebuie sa nu aiba gard in directia respectiva

    cand pionul se muta, coordonatele se modifica in felul urmator:

    sus: iNew = iOld - 2, jNew = jOld
    jos: iNew = iOld + 2, jNew = jOld

    stanga: iNew = iOld, jNew = jOld - 2
    dreapta: iNew = iOld, jNew = jOld + 2
    */

    //sus
   if(iNew == iOld - 2 && jNew == jOld && tabla[iNew][jNew].info == 1 && tabla[iOld - 1][jOld].info == 2) {
        cout<<"sus"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de deasupra
        a 2 a : sa fie jNew de deasupra
        a 3 a : spatiul nou sa nu fie ocupat de pionul advers
        a 4 a : sa nu aiba gard in drum

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //jos
    if(iNew == iOld + 2 && jNew == jOld && tabla[iNew][jNew].info == 1 && tabla[iOld + 1][jOld].info == 2) {
        cout<<"jos"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de sub
        a 2 a : sa fie jNew de sub
        a 3 a : spatiul nou sa nu fie ocupat de pionul advers
        a 4 a : sa nu aiba gard in drum

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //stanga
    if(iNew == iOld && jNew == jOld - 2 && tabla[iNew][jNew].info == 1 && tabla[iOld][jOld - 1].info == 2) {
        cout<<"stanga"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew din stanga
        a 2 a : sa fie jNew din stanga
        a 3 a : spatiul nou sa nu fie ocupat de pionul advers
        a 4 a : sa nu aiba gard in drum

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //dreapta
    if(iNew == iOld && jNew == jOld + 2 && tabla[iNew][jNew].info == 1 && tabla[iOld][jOld + 1].info == 2) {
        cout<<"dreapta"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew din dreapta
        a 2 a : sa fie jNew din dreapta
        a 3 a : spatiul nou sa nu fie ocupat de pionul advers
        a 4 a : sa nu aiba gard in drum

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    /*
    acum vom aborda miscarile compuse, mai intai cele mai simple, cand trebuie sa se sara peste un pion
    si acesta nu are gard in spatele sau

    conditiile de pozitie sunt :

    sus peste pion : iNew = iOld - 4, jNew = jOld
    jos peste pion : iNew = iOld + 4, jNew = jOld

    stanga peste pion : iNew = iOld, jNew = jOld - 4
    dreapta peste pion : iNew = iOld, jNew = jOld + 4

    */

    //sus peste pion
    if(iNew == iOld - 4 && jNew == jOld && tabla[iOld - 1][jOld].info == 2 && tabla[iOld - 2][jOld].info != 1
       && tabla[iOld - 3][jOld].info == 2) {
        cout<<"sus peste pion"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de sus peste pion
        a 2 a : sa fie jNew de sus peste pion
        a 3 a : sa nu aiba gard in drum
        a 4 a : sa fie pionul advers pe patratica alaturata
        a 5 a : pionul advers sa nu aiba gard in sus

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //jos peste pion
    if(iNew == iOld + 4 && jNew == jOld && tabla[iOld + 1][jOld].info == 2 && tabla[iOld + 2][jOld].info != 1
       && tabla[iOld + 3][jOld].info == 2) {
        cout<<"jos peste pion"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de jos peste pion
        a 2 a : sa fie jNew de jos peste pion
        a 3 a : sa nu aiba gard in drum
        a 4 a : sa fie pionul advers pe patratica alaturata
        a 5 a : pionul advers sa nu aiba gard in jos

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //stanga peste pion
    if(iNew == iOld && jNew == jOld - 4 && tabla[iOld][jOld - 1].info == 2 && tabla[iOld][jOld - 2].info != 1
       && tabla[iOld][jOld - 3].info == 2) {
        cout<<"stanga peste pion"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de stanga peste pion
        a 2 a : sa fie jNew de stanga peste pion
        a 3 a : sa nu aiba gard in drum
        a 4 a : sa fie pionul advers pe patratica alaturata
        a 5 a : pionul advers sa nu aiba gard in stanga

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }

    //dreapta peste pion
    if(iNew == iOld && jNew == jOld + 4 && tabla[iOld][jOld + 1].info == 2 && tabla[iOld][jOld + 2].info != 1
       && tabla[iOld][jOld + 3].info == 2) {
        cout<<"dreapta peste pion"<<"\n";
        /*
        verificarile sunt in felul urmator:

        prima : sa fie iNew de dreapta peste pion
        a 2 a : sa fie jNew de dreapta peste pion
        a 3 a : sa nu aiba gard in drum
        a 4 a : sa fie pionul advers pe patratica alaturata
        a 5 a : pionul advers sa nu aiba gard in dreapta

        */
        stergereMutariPioni();
        swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
        initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
        //pune pionul pe pozitia noua
        setfillstyle(SOLID_FILL, 0);
        setcolor(15);
        rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
        floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
        //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
        iOld = iNew;
        jOld = jNew;
        if(turn==1)
        iOld1=iOld,jOld1=jOld;
        else iOld2=iOld,jOld2=jOld;
        return 1;
    }


    /*
    acum urmeaza cazurile compuse, cand pionii sunt fata in fata si au gard in spate

    1. daca vrem sa mergem in jos, avem pion in drum si acesta are gard in jos:
        varianta 1 : daca pionul advers nu are gard in stanga, bot-ul se poate muta la stanga jos
            coordonatele sunt : iNew = iOld + 2, jNew = jOld - 2
        varianta 2 : daca pionul advers nu are gard in dreapta, bot-ul se poate muta la dreapta jos
            coordonatele sunt : iNew = iOld + 2, jNew = jOld + 2

    2. daca vrem sa mergem in sus, avem pion in drum si acesta are gard in sus :
        varianta 1 : daca pionul advers nu are gard in stanga, bot-ul se poate muta la stanga sus
            coordonatele sunt : iNew = iOld - 2, jNew = jOld - 2
        varianta 2 : daca pionul advers nu are gard in dreapta, bot-ul se poate muta la dreapta sus
            coordonatele sunt : iNew = iOld - 2, jNew = jOld + 2

    3.daca vrem sa mergem in stanga, avem pion in drum si acesta are gard in stanga sa :
        varianta 1 : daca pionul advers nu are gard in jos, bot-ul se poate muta in jos stanga
            coordonatele sunt : iNew = iOld + 2, jNew = jOld - 2
        varianta 2 : daca pionul advers nu are gard in susm bot-ul se poate muta in sus stanga
            coordonatele sunt : iNew = iOld - 2, jNew = jOld - 2

    4. daca vrem sa mergem in dreapta, avem pion in drum si acesta are gard in dreapta sa :
        varianta 1 : daca pionul advers nu are gard jos, bot-ul poate muta in jos dreapta
            coordonatele sunt : iNew = iOld + 2, jNew = jOld + 2
        varianta 2 : daca pionul advers nu are gard sus, bot-ul poate muta in sus dreapta
            coordonatele sunt : iNew = iOld - 2, jNew = jOld + 2

    */

    //diagonala stanga jos
    if(iNew == iOld + 2 && jNew == jOld - 2 && tabla[iOld + 1][jOld].info == 2 && tabla[iOld + 2][jOld].info != 1
        && tabla[iOld + 3][jOld].info != 2 && tabla[iOld + 2][jOld - 1].info == 2) {
            cout<<"diagonala stanga jos"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga jos
            a 2 a : sa fie jNew de diagonala stanga jos
            a 3 a : sa nu aiba gard in prima patratica de jos
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in jos
            a 6 a : pionul advers sa nu aiba gard in stanga sa

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala dreapta jos
    if(iNew == iOld + 2 && jNew == jOld + 2 && tabla[iOld + 1][jOld].info == 2 && tabla[iOld + 2][jOld].info != 1
        && tabla[iOld + 3][jOld].info != 2 && tabla[iOld + 2][jOld + 1].info == 2) {
            cout<<"diagonala dreapta jos"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala dreapta jos
            a 2 a : sa fie jNew de diagonala dreapta jos
            a 3 a : sa nu aiba gard in prima patratica de jos
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in jos
            a 6 a : pionul advers sa nu aiba gard in dreapta sa

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala stanga sus
    if(iNew == iOld - 2 && jNew == jOld - 2 && tabla[iOld - 1][jOld].info == 2 && tabla[iOld - 2][jOld].info != 1
        && tabla[iOld - 3][jOld].info != 2 && tabla[iOld - 2][jOld - 1].info == 2) {
            cout<<"diagonala stanga sus"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga sus
            a 2 a : sa fie jNew de diagonala stanga sus
            a 3 a : sa nu aiba gard in prima patratica de sus
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in sus
            a 6 a : pionul advers sa nu aiba gard in stanga sa

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala dreapta sus
    if(iNew == iOld - 2 && jNew == jOld + 2 && tabla[iOld - 1][jOld].info == 2 && tabla[iOld - 2][jOld].info != 1
        && tabla[iOld - 3][jOld].info != 2 && tabla[iOld - 2][jOld + 1].info == 2) {
            cout<<"diagonala dreapta sus"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala dreapta sus
            a 2 a : sa fie jNew de diagonala dreapta sus
            a 3 a : sa nu aiba gard in prima patratica de sus
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in sus
            a 6 a : pionul advers sa nu aiba gard in dreapta sa

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala jos stanga
    if(iNew == iOld + 2 && jNew == jOld - 2 && tabla[iOld][jOld - 1].info == 2 && tabla[iOld][jOld - 2].info != 1
        && tabla[iOld][jOld - 3].info != 2 && tabla[iOld + 1][jOld - 2].info == 2) {
            cout<<"diagonala jos stanga"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala jos stanga
            a 2 a : sa fie jNew de diagonala jos stanga
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in stanga
            a 6 a : pionul advers sa nu aiba gard in jos

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala sus stanga
    if(iNew == iOld - 2 && jNew == jOld - 2 && tabla[iOld][jOld - 1].info == 2 && tabla[iOld][jOld - 2].info != 1
        && tabla[iOld][jOld - 3].info != 2 && tabla[iOld - 1][jOld - 2].info == 2) {
            cout<<"diagonala sus stanga"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala sus stanga
            a 2 a : sa fie jNew de diagonala sus stanga
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in stanga
            a 6 a : pionul advers sa nu aiba gard in sus

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala jos dreapta
    if(iNew == iOld + 2 && jNew == jOld + 2 && tabla[iOld][jOld + 1].info == 2 && tabla[iOld][jOld + 2].info != 1
        && tabla[iOld][jOld + 3].info != 2 && tabla[iOld + 1][jOld + 2].info == 2) {
            cout<<"diagonala jos dreapta"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala jos dreapta
            a 2 a : sa fie jNew de diagonala jos dreapta
            a 3 a : sa nu aiba gard in prima patratica din dreapta
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in dreapta
            a 6 a : pionul advers sa nu aiba gard in jos

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //diagonala sus dreapta
    if(iNew == iOld - 2 && jNew == jOld + 2 && tabla[iOld][jOld + 1].info == 2 && tabla[iOld][jOld + 2].info != 1
        && tabla[iOld][jOld + 3].info != 2 && tabla[iOld - 1][jOld + 2].info == 2) {
            cout<<"diagonala sus dreapta"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala sus dreapta
            a 2 a : sa fie jNew de diagonala sus dreapta
            a 3 a : sa nu aiba gard in prima patratica din dreapta
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa aiba gard in dreapta
            a 6 a : pionul advers sa nu aiba gard in sus

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }
    /*
    acum urmeaza cazurile de margine:
        cand un pion este fata in fata cu celalalt si unul din ei este pe ultima patratica a tablei;
        cazurile speciale sunt coluturile tablei, cand ambii pioni se afla pe ultima patratica;

    cazuri generale :
        1.  cand un pion este pe coloana 2(incepand de la 0), iar celalalt este pe coloana 0 si sunt fata in fata,
            cel de pe coloana 2 o poate lua in diagonala jos stanga sau diagonala sus stanga
                coordonatele sunt : jos : iNew = iOld + 2, jNew = jOld - 2
                                    sus : iNew = iOld - 2, jNew = jOld - 2


        2.  cand un pion este pe coloana 14(incepand de la 0), iar celalalt este pe coloana 16 si sunt fata in fata,
            cel de pe coloana 14 o poate lua in diagonala jos dreapta sau diagonala sus dreapta

    cazuri speciale, colturile(aparent merg deja)

    */

    //margine stanga -> jos
    if(iNew == iOld + 2 && jNew == jOld - 2 && tabla[iOld][jOld - 1].info == 2 && tabla[iOld][jOld - 2].info != 1
        && ((jOld - 3) == -1) && tabla[iOld + 1][jOld - 2].info == 2) {
            cout<<"caz de margine stanga jos"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga jos
            a 2 a : sa fie jNew de diagonala stanga jos
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa fie in margine
            a 6 a : pionul advers sa nu aiba gard in jos

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //margine stanga sus
    if(iNew == iOld - 2 && jNew == jOld - 2 && tabla[iOld][jOld - 1].info == 2 && tabla[iOld][jOld - 2].info != 1
        && ((jOld - 3) == -1) && tabla[iOld - 1][jOld - 2].info == 2) {
            cout<<"caz de margine stanga sus"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga sus
            a 2 a : sa fie jNew de diagonala stanga sus
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa fie in margine
            a 6 a : pionul advers sa nu aiba gard in sus

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //margine dreapta jos
    if(iNew == iOld + 2 && jNew == jOld + 2 && tabla[iOld][jOld + 1].info == 2 && tabla[iOld][jOld + 2].info != 1
        && ((jOld + 3) == 17) && tabla[iOld + 1][jOld + 2].info == 2) {
            cout<<"caz de margine dreapta jos"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga jos
            a 2 a : sa fie jNew de diagonala stanga jos
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa fie in margine
            a 6 a : pionul advers sa nu aiba gard in jos

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }

    //margine dreapta sus
    if(iNew == iOld - 2 && jNew == jOld + 2 && tabla[iOld][jOld + 1].info == 2 && tabla[iOld][jOld + 2].info != 1
        && ((jOld + 3) == 17) && tabla[iOld - 1][jOld + 2].info == 2) {
            cout<<"caz de margine dreapta sus"<<"\n";
            /*
            verificarile sunt in felul urmator:

            prima : sa fie iNew de diagonala stanga jos
            a 2 a : sa fie jNew de diagonala stanga jos
            a 3 a : sa nu aiba gard in prima patratica din stanga
            a 4 a : sa fie pionul advers pe patratica alaturata
            a 5 a : pionul advers sa fie in margine
            a 6 a : pionul advers sa nu aiba gard in jos

            */
            stergereMutariPioni();
            swap(tabla[iOld][jOld].info, tabla[iNew][jNew].info);
            initPion(tabla[iNew][jNew].x1+(tabla[iNew][jNew].x2-tabla[iNew][jNew].x1)/2,tabla[iNew][jNew].y1+(tabla[iNew][jNew].y2-tabla[iNew][jNew].y1)/2, 15 , color);
            //pune pionul pe pozitia noua
            setfillstyle(SOLID_FILL, 0);
            setcolor(15);
            rectangle(tabla[iOld][jOld].x1,tabla[iOld][jOld].y1,tabla[iOld][jOld].x2,tabla[iOld][jOld].y2);
            floodfill(tabla[iOld][jOld].x1+30,tabla[iOld][jOld].y1+30,15);
            //am colorat dreptunghiul cu coordonatele vechi cu negru, pentru a disparea vechiul pion
            iOld = iNew;
            jOld = jNew;
            if(turn==1)
            iOld1=iOld,jOld1=jOld;
            else iOld2=iOld,jOld2=jOld;
            return 1;
    }
    return 0; //daca aceasta functie returneaza 0 inseamna ca nu s-a facut mutare
}

int mutariPion(int x,int y){
    int iOld,jOld;
    if(turn==1)
        iOld = iOld1 , jOld = jOld1;
    else
         iOld = iOld2 , jOld = jOld2;
    for(int i = 0;i<17;i+=2)
        for(int j = 0;j<17;j+=2)
            if(tabla[i][j].x1<=x && tabla[i][j].x2>=x && tabla[i][j].y1<=y && tabla[i][j].y2>=y && iOld==i && jOld==j){//se verifica din ce patrat face parte apasarea de mousse
                 if((i-2)>=0 && tabla[i-2][j].info==1&&tabla[i-1][j].info==2){//se ia fiecare caz pe rand(ca in move) doar ca merge doar pe if,fare elsuri
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i-2][j].x1,tabla[i-2][j].y1,tabla[i-2][j].x2,tabla[i-2][j].y2);
                     floodfill(tabla[i-2][j].x1+1,tabla[i-2][j].y1+1,15);
                 }
                 else if((i-4)>=0 && tabla[i-2][j].info!=1&&tabla[i-1][j].info==2&&tabla[i-3][j].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i-4][j].x1,tabla[i-4][j].y1,tabla[i-4][j].x2,tabla[i-4][j].y2);
                     floodfill(tabla[i-4][j].x1+1,tabla[i-4][j].y1+1,15);

                 }
                 if((j-2)>=0&&tabla[i][j-2].info==1&&tabla[i][j-1].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i][j-2].x1,tabla[i][j-2].y1,tabla[i][j-2].x2,tabla[i][j-2].y2);
                     floodfill(tabla[i][j-2].x1+1,tabla[i][j-2].y1+1,15);
                 }
                 else  if((j-4)>=0&&tabla[i][j-2].info!=1&&tabla[i][j-1].info==2&&tabla[i][j-3].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i][j-4].x1,tabla[i][j-4].y1,tabla[i][j-4].x2,tabla[i][j-4].y2);
                     floodfill(tabla[i][j-4].x1+1,tabla[i][j-4].y1+1,15);
                 }
                 if((j+2)<=16&&tabla[i][j+2].info==1&&tabla[i][j+1].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i][j+2].x1,tabla[i][j+2].y1,tabla[i][j+2].x2,tabla[i][j+2].y2);
                     floodfill(tabla[i][j+2].x1+1,tabla[i][j+2].y1+1,15);
                }
                else if((j+4)<=16&&tabla[i][j+2].info!=1&&tabla[i][j+1].info==2&&tabla[i][j+3].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i][j+4].x1,tabla[i][j+4].y1,tabla[i][j+4].x2,tabla[i][j+4].y2);
                     floodfill(tabla[i][j+4].x1+1,tabla[i][j+4].y1+1,15);
                }
                 if((i+2)<=16&&tabla[i+2][j].info==1&&tabla[i+1][j].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i+2][j].x1,tabla[i+2][j].y1,tabla[i+2][j].x2,tabla[i+2][j].y2);
                     floodfill(tabla[i+2][j].x1+1,tabla[i+2][j].y1+1,15);
                 }
                 else if((i+4)<=16&&tabla[i+2][j].info!=1&&tabla[i+1][j].info==2&&tabla[i+3][j].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i+4][j].x1,tabla[i+4][j].y1,tabla[i+4][j].x2,tabla[i+4][j].y2);
                     floodfill(tabla[i+4][j].x1+1,tabla[i+4][j].y1+1,15);
                 }
                 if(i-2>=0&&tabla[i-2][j].info!=1&&tabla[i-1][j].info==2&&tabla[i-3][j].info!=2)
                 {
                     if(tabla[i-2][j-1].info==2&&j-1>=0){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                     floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                     }
                     if(tabla[i-2][j+1].info==2&&j+1<=16){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                     floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                     }

                 }
                 if(i+2<=16&&tabla[i+2][j].info!=1&&tabla[i+3][j].info!=2&&tabla[i+1][j].info==2)
                 {
                     if(j+2<=16&&tabla[i+2][j+1].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                     floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                     if(j-1>=0&&tabla[i+1][j-1].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                     floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                     }
                 }
                 if(j+2<=16&&tabla[i][j+2].info!=1&&tabla[i][j+3].info!=2){
                     if(i+2<=16&&tabla[i+1][j+2].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                     floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);

                     }
                     if(i-2>=0&&tabla[i-1][j+2].info==2){
                     setfillstyle(SOLID_FILL, 2);
                     setcolor(15);
                     rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                     floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                     }
                 }
                 if(j-2>=0&&tabla[i][j-2].info!=1&&tabla[i][j-3].info!=2&&tabla[i][j-1].info==2){
                       if(i+2<=16&&tabla[i+1][j-2].info==2){
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);

                       }
                       if(i-2>=0&&tabla[i-1][j-2].info==2)
                       {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                       }
                    }
                if(j==2&&tabla[i][j-2].info!=1&&tabla[i][j-1].info==2)
                {
                    if(tabla[i-1][j-2].info==2)
                    {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                    }
                    if(tabla[i+1][j-2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                     }
                }
                if(j==14&&tabla[i][j+2].info!=1&&tabla[i][j+1].info==2)
                {
                    if(tabla[i-1][j+2].info==2)
                    {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i-2][j+2].x1,tabla[i-2][j+2].y1,tabla[i-2][j+2].x2,tabla[i-2][j+2].y2);
                        floodfill(tabla[i-2][j+2].x1+1,tabla[i-2][j+2].y1+1,15);
                    }
                    if(tabla[i+1][j].info==2&&tabla[i+1][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                        floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                }
                if(i==17&&tabla[i-2][j].info!=1&&tabla[i-2][j].info==2)
                {
                    if(tabla[i-2][j-1].info==2)
                    {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                    }
                    if(tabla[i][j+1].info==2&&tabla[i-2][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i-2][j-2].x1,tabla[i-2][j-2].y1,tabla[i-2][j-2].x2,tabla[i-2][j-2].y2);
                        floodfill(tabla[i-2][j-2].x1+1,tabla[i-2][j-2].y1+1,15);
                     }
                }
                if(i==14&&tabla[i+2][j].info!=1&&tabla[i+2][j].info==2)
                {
                    if(tabla[i+2][j-1].info==2)
                    {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i+2][j-2].x1,tabla[i+2][j-2].y1,tabla[i+2][j-2].x2,tabla[i+2][j-2].y2);
                        floodfill(tabla[i+2][j-2].x1+1,tabla[i+2][j-2].y1+1,15);
                    }
                    if(tabla[i][j+1].info==2&&tabla[i+2][j+2].info==2)
                        {
                        setfillstyle(SOLID_FILL, 2);
                        setcolor(15);
                        rectangle(tabla[i+2][j+2].x1,tabla[i+2][j+2].y1,tabla[i+2][j+2].x2,tabla[i+2][j+2].y2);
                        floodfill(tabla[i+2][j+2].x1+1,tabla[i+2][j+2].y1+1,15);
                     }
                }


                 return 1;
            }
    return 0;
}
void afisturn(){

    if(turn==1){

    setfillstyle(SOLID_FILL,0);
    bar(750,120, 1200,200);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(0);
    setcolor(GREEN);
    char nume11[100];
    strcpy(nume11,nume1);
    strcat(nume11," IS MOVING...");
    outtextxy(750,120,nume11);
    }
    else if(turn==2){

    setfillstyle(SOLID_FILL,0);
    bar(750,120, 1200,200);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(0);
    setcolor(RED);
    char nume22[100];
    strcpy(nume22,nume2);
    strcat(nume22, " IS MOVING...");
    outtextxy(750,120, nume22);

    }
}
void fisier()
{
    ifstream fin("nume.in");
    char aux[100];
    char name1[100],name2[100];
    strcpy(name1,nume1);
    strcpy(name2,nume2);
    tabel nume[8];
    int i=6;
    while(fin>>aux&&i>=1)//se citesc numele din fisier
        strcpy(nume[i--],aux);
     fin.close();
     strcat(name1,".");
     strcat(name1,name2);
     strcat(name1,".");
     strcat(name1,castigator);
     strcpy(nume[7],name1);//se adauga un nou meci
   ofstream fout("nume.in", ios::trunc);// se adauga elementele in fisier
       for(int j=7;j>=i+1;j--)
        fout<<nume[j]<<" ";
        fout.close();
}
void alternanta(){
    initTable();
    //se alterneaza randul jucatorilor
    bool ok = false;
    while (castig() == 0){
        int distanta1 = distantaMinima(iOld1, jOld1, 0);
        int distanta2 = distantaMinima(iOld2, jOld2, 16);
        cout<<distanta1<<" "<<distanta2<<"\n";
         int x=-1, y=-1;
         afisgard();
         afisturn();
         while (!ismouseclick(WM_LBUTTONDOWN)) {
                delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x >= 800 && x <=1000 && y >= 600 && y <= 650) {
            ok = true;
            break;
        }
        while(mutariPion(x,y)==0&&putGard(x,y)==0){
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
            getmouseclick(WM_LBUTTONDOWN, x, y);
        }

        if(mutariPion(x,y)==1)
        while(move(x,y) == 0){
                while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
                getmouseclick(WM_LBUTTONDOWN, x, y);
            }
        turn=3-turn;
    }
    if(ok == true) {
        iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8,turn=1,type,nrGarduri1=10,nrGarduri2=10,fisier();
        closegraph();
        menu();
    }
}
void putaName()
{
       settextstyle(8,HORIZ_DIR,5);
       setcolor(RED);
       outtextxy(300,450,"PUT A NAME!");
       delay(1000);
       setcolor(0);
      setfillstyle(SOLID_FILL,0);
       bar(290,450,580,490);

}
void namepage2(){
    initwindow(600,600,"QUORIDOR");
    settextstyle(8,HORIZ_DIR,5);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(130,120,"PUT YOUR NAME");
    setcolor(RED);
    rectangle(105,110,500,170);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(220,230,"PLAYER 2");
    rectangle(140,310,460,370);
    int i=0;
     settextstyle(8,HORIZ_DIR,3);
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(470,510,570,550);
    rectangle(30,510,240,550);
    floodfill(471,511,15);
    floodfill(31,511,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(480,520,"START");
    outtextxy(45,520,"BACK TO MENU");
    setbkcolor(0);
    settextstyle(8,HORIZ_DIR,4);
    int x,y;
    char nume[100]="\0";
     while(1)
     {
          while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
             if(kbhit()){//se verifica ce taste au fost apasate
             int key=getch();
             if((key<='Z'&&key>='A')||(key<='z'&&key>='a'))//este litera
                nume[i++]=char(key);
            else if(key==8)
            {nume[i-1]='\0',i--;}
             else if(key==13){
                    if(nume[0]!='\0')
                   closegraph(),nume[i]='\0',strcpy(nume2,nume),alternanta();
                    else putaName();
            }
            setfillstyle(SOLID_FILL,0);
            setcolor(15);
            rectangle(140,310,460,370);
            floodfill(141,311,15);
            setcolor(RED);
            outtextxy(160,320,nume);


         }
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x >= 30 && x <=240 && y >= 510 && y <= 550)
            closegraph(),menu(),nume[i]='\0',strcpy(nume2,nume);
        else if(x>=470&&x<=570&&y>=510&&y<=550&&computer==0){
                if(nume[0]!=NULL)
                closegraph(),nume[i]='\0',strcpy(nume2,nume),alternanta();
                else putaName();}
    }
}
void namepage1()
{
    initwindow(600,600,"QUORIDOR");
    settextstyle(8,HORIZ_DIR,5);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(130,120,"PUT YOUR NAME");
    setcolor(RED);
    rectangle(105,110,500,170);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(220,230,"PLAYER 1");
    rectangle(140,310,460,370);
    int i=0;
     settextstyle(8,HORIZ_DIR,3);
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(470,510,570,550);
    rectangle(30,510,240,550);
    floodfill(471,511,15);
    floodfill(31,511,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(490,520,"NEXT");
    outtextxy(45,520,"BACK TO MENU");
    setbkcolor(0);
    settextstyle(8,HORIZ_DIR,4);
    int x,y;
    char nume[100]="\0";
     while(1)
     {
          while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
             if(kbhit()){//se verifica ce tasta a fost apasata
             int key=getch();
             if((key<='Z'&&key>='A')||(key<='z'&&key>='a'))//este litera
                nume[i++]=char(key);//se adauga o litera la nume
            else if(key==8)
            {nume[i-1]='\0',i--;}
            else if(key==13){
            if(nume[0]!=NULL){
                if(computer==0)
                 closegraph(),strcpy(nume1,nume),namepage2();
                else if(computer==1){
                     nume[i]='\0',strcpy(nume1,nume),nume2[0]='\0',strcpy(nume2,"Bot");
            if(computertactic1==1)
               closegraph(), alternantacompTactic();
           else if(computertactic2==1)
                closegraph(), alternantacompTacticMedium();
            else closegraph(),alternantacomp();}

            }
            else putaName();}
            setfillstyle(SOLID_FILL,0);
            setcolor(15);
            rectangle(140,310,460,370);
            floodfill(141,311,15);
            setcolor(GREEN);
            outtextxy(160,320,nume);


         }
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);//se verifica ce butoane au fost apasate
        if(x >= 30 && x <=240 && y >= 510 && y <= 550&&nume!=NULL)
            closegraph(),nume[i]='\0',strcpy(nume1,nume),menu();
        else if(x>=470&&x<=570&&y>=510&&y<=550&&computer==0){
                if(nume[0]!=NULL)
            closegraph(),strcpy(nume1,nume),namepage2();
                else putaName();}
        else if(x>=470&&x<=570&&y>=510&&y<=550&&computer==1){
                if(nume[0]!=NULL){
                nume[i]='\0',strcpy(nume1,nume),nume2[0]='\0',strcpy(nume2,"Bot");
            if(computertactic1==1)
               closegraph(), alternantacompTactic();
           else if(computertactic2==1)
                closegraph(), alternantacompTacticMedium();
            else closegraph(),alternantacomp();}
                else putaName();}



     }

}
void computerpage(){
    closegraph();
    initwindow(600,600);
    setfillstyle(SOLID_FILL,0);
    bar(0, 0, 600, 600);
    setcolor(RED);
    rectangle(70,90,530,180);
    settextstyle(8,HORIZ_DIR,5);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(80,120,"CHOOSE YOUR LEVEL");//titlul de choose your lebe
    setfillstyle(SOLID_FILL,15);
    setcolor(15);
    rectangle(150,250,450,300);
    floodfill(151,251,15);//se coloreaza inauntru butonului
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(15);
    setcolor(0);
    outtextxy(260,260,"EASY");
    setfillstyle(SOLID_FILL,15);
    setcolor(15);
    rectangle(150,350,450,400);
    floodfill(171,350+1,15);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(15);
    setcolor(0);
    outtextxy(240,360,"MEDIUM");
    setfillstyle(SOLID_FILL,15);
    setcolor(15);
    rectangle(150,450,450,500);
    floodfill(151,450+1,15);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(15);
    setcolor(0);
    outtextxy(260,460,"HARD");
    ButonAcasa.x1 = 30, ButonAcasa.x2 =230, ButonAcasa.y1 = 530, ButonAcasa.y2 = 570;
    setfillstyle(SOLID_FILL,15);
    setcolor(WHITE);
    rectangle(ButonAcasa.x1, ButonAcasa.y1, ButonAcasa.x2, ButonAcasa.y2);
    floodfill(ButonAcasa.x1+1,ButonAcasa.y1+1,15);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(15);
    setcolor(0);
    outtextxy(40,540,"BACK TO MENU");
    int x,y,ok=1;
    while(ok){
    while (!ismouseclick(WM_LBUTTONDOWN)) {//se verifica daca este apasat vreun buton
                    delay(100);
                }
    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=150&&x<=450&&y>=250&&y<=300)
        closegraph(),ok=0,computertactic1=0,namepage1();//alternantacomp();
    else if(x>=150&&x<=450&&y>=350&&y<=400)
        closegraph(),computertactic2=1,namepage1(),ok=0;
    else if(x>=30&&x<=230&&y>=530&&y<=570)
        closegraph(),ok=0,menu();
    else if(x>=150&&x<=450&&y>=450&&y<=500)
        {
          closegraph(),computertactic1=1,namepage1();
        }
    }


}

void endgame(){

    cleardevice();
    setbkcolor(0);
    int x = 1200 / 2;
    int y = 800 / 2;
    setcolor(15);
    settextstyle(8, HORIZ_DIR, 4);
    outtextxy(x - 120 + 2, y - 50 + 2, "Game over");
    setcolor(15);
    outtextxy(x - 120, y - 50, "Game over");
    ButonAcasa.x1 = 800, ButonAcasa.x2 = 1000, ButonAcasa.y1 = 600, ButonAcasa.y2 = 650;
    setcolor(WHITE);
    rectangle(ButonAcasa.x1, ButonAcasa.y1, ButonAcasa.x2, ButonAcasa.y2);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(0);
    setcolor(15);
    outtextxy(812,614,"BACK TO MENU");
    setcolor(WHITE);
    rectangle(200, ButonAcasa.y1, 400, ButonAcasa.y2);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(0);
    setcolor(15);
    outtextxy(270,614,"EXIT");
    if(iOld2==16){

      strcpy(castigator,nume2);
      fisier();
      settextstyle(8,HORIZ_DIR,5);
      setbkcolor(0);
      setcolor(RED);
      strcat(nume2," WIN!");//se pun numele castigatorului si cu cuvantul WIN
      outtextxy(670,414,nume2);

    }
    else{
        strcpy(castigator,nume1);
        fisier();
        settextstyle(8,HORIZ_DIR,5);
        setbkcolor(0);
        setcolor(GREEN);
        strcat(nume1," WIN!");//se pun numele castigatorului si cu cuvantul WIN
;        outtextxy(670,414,nume1);
    }
    int ok=1;
    while(ok){
    while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
        getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=800&&x<=1000&&y>=600&&y<=650)
        closegraph(),menu(),ok=0;
    else   if(x>=200&&x<=400&&y>=600&&y<=650)
        closegraph();}

}
int castig(){
    if(iOld2==16||iOld1==0 || iOld2 == 18 || iOld1 == -2){
        endgame();
        return 1;
    }
    else
        return 0;
}
void randomFences(){
    srand(time(0));
    int x, y; //coordonate ale matricei, adica i, j
    x = rand() % 17;
    y = rand() % 17;
    bool ok = true;
    while( ok == true ) {
        if( ( (x % 2 == 0 && y % 2 == 1)  || (x % 2 == 1 && y % 2 == 0 ) ) && putGard(tabla[x][y].x1, tabla[x][y].y1) == 1) {

            ok = false;
            break;
        }
        if(ok == true) {
            x = rand() % 17;
            y = rand() % 17;
        }
    }
}
void randomMoves(){
    int x = time(0);
    srand(x);
    int y = rand() % 4 + 1;
    int ok = true;
    while(ok == true) {
        if(y == 1) {
            if(move(tabla[iOld2-2][jOld2].x1+1,tabla[iOld2-2][jOld2].y1+1) == 1) {
                ok = false;
                break;
            }
        }else if(y == 2) {
            if(move(tabla[iOld2][jOld2+2].x1+1,tabla[iOld2][jOld2+2].y1+1) == 1) {
                ok = false;
                break;
            }
        }else if(y == 3) {
            if(move(tabla[iOld2+2][jOld2].x1+2,tabla[iOld2+2][jOld2].y1+2) == 1) {
                ok = false;
                break;
            }
        }else if(y == 4) {
            if(move(tabla[iOld2][jOld2-2].x1+2,tabla[iOld2][jOld2-2].y1+2) == 1) {
                ok = false;
                break;
            }
        }

        if(ok == true) {
            y = rand() % 4 + 1;
        }
    }

}
void rulespage5(){
    initwindow(900,600);
    settextstyle(8,HORIZ_DIR,6);
    outtextxy(335,100,"HELP");
      readimagefile("picture5.jpg",270,250,570,590);
    setcolor(RED);
    rectangle(300,100,500,150);
    setcolor(WHITE);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(50,200,"*If there is a fence behind the said pawn, the player can place his pawn");
    outtextxy(50,230,"to the left or the right of the other pawn");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(720,50,885,90);
    floodfill(721,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(727,57,"BACK TO MENU");
    int x,y;
   while(100){
   while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=720&&x<=885&&y>=50&&y<=90)
            closegraph(),menu();
            }

}
void rulespage4(){
    initwindow(900,600);
    settextstyle(8,HORIZ_DIR,6);
    outtextxy(335,100,"HELP");
      readimagefile("picture4.jpg",270,250,570,590);
    setcolor(RED);
    rectangle(300,100,500,150);
    setcolor(WHITE);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(50,200,"*When two pawns face each other on neighbouring squares which are not separated by a fence");
    outtextxy(50,230,"the player whose turn it is can jump the opponent’s pawn and place himself behind him");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(720,50,885,90);
    floodfill(721,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(727,57,"BACK TO MENU");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(20,50,185,90);
    floodfill(21,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(45,57,"NEXT PAGE");
    int x,y;
    while(100){
   while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=720&&x<=885&&y>=50&&y<=90)
            closegraph(),menu();
        else if(x>=20&&x<=185&&y>=50&&y<=90)
           rulespage5();
            }
}
void rulespage3(){
    initwindow(900,600);
    settextstyle(8,HORIZ_DIR,6);
    outtextxy(335,100,"HELP");
    readimagefile("picture3.jpg",270,250,570,590);
    setcolor(RED);
    rectangle(300,100,500,150);
    setcolor(WHITE);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(50,200,"*You can block your opponent by placing the walls");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(720,50,885,90);
    floodfill(721,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(727,57,"BACK TO MENU");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(20,50,185,90);
    floodfill(21,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(45,57,"NEXT PAGE");
    int x,y;
    while(100){
   while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=720&&x<=885&&y>=50&&y<=90)
            closegraph(),menu();
        else if(x>=20&&x<=185&&y>=50&&y<=90)
           rulespage4();
            }
}
void rulespage2(){
    initwindow(900,600);
    settextstyle(8,HORIZ_DIR,6);
    outtextxy(335,100,"HELP");
    readimagefile("picture2.jpg",280,250,570,600);
    setcolor(RED);
    rectangle(300,100,500,150);
    setcolor(WHITE);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(50,200,"*click on the pawn and then move it to one of the green boxes");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(720,50,885,90);
    floodfill(721,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(727,57,"BACK TO MENU");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(20,50,185,90);
    floodfill(21,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(45,57,"NEXT PAGE");
    int x,y;
    while(100){
    while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=720&&x<=885&&y>=50&&y<=90)
            closegraph(),menu();
        else if(x>=20&&x<=185&&y>=50&&y<=90)
            rulespage3();
            }
}
void rulespage1()
{
     initwindow(900,600);
    settextstyle(8,HORIZ_DIR,6);
    outtextxy(335,100,"HELP");
     readimagefile("picture1.jpg",250,250,570,600);
     setcolor(RED);
    rectangle(300,100,500,150);
    setcolor(WHITE);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(50,200,"*To win the game, reach the opposite site faster than your opponent");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(720,50,885,90);
    floodfill(721,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(727,57,"BACK TO MENU");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(20,50,185,90);
    floodfill(21,52,15);
    setcolor(0);
    setbkcolor(15);
    outtextxy(45,57,"NEXT PAGE");
     int x, y;
    while(100){
    while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x>=720&&x<=885&&y>=50&&y<=90)
            closegraph(),menu();
        else if(x>=20&&x<=185&&y>=50&&y<=90)
            rulespage2();
            }
}
void alternantacomp(){
    initTable();
    bool ok = false;
    while(castig()==0)
    {
       afisgard();
       afisturn();
      if(turn==1)
      {
           int x=-1, y=-1;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x >= 800 && x <=1000 && y >= 600 && y <= 650) {
            ok = true;
            break;
        }
        while(mutariPion(x,y)==0 && putGard(x,y)==0){
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
            }
            getmouseclick(WM_LBUTTONDOWN, x, y);
        }
        if(mutariPion(x,y)==1)
        while(move(x,y) == 0){
                while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
                getmouseclick(WM_LBUTTONDOWN, x, y);
            }

        }
        else
        {  delay(500);
            srand(time(0));
            int x=rand()%2+1;

            if(x == 1) {
                //cout<<x<<"\n";
                randomMoves();
            }else if(x == 2) {
                //cout<<x<<" ";
                randomFences();
            }
        }
        turn=3-turn;
      }
      if(ok == true) {
            iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8,turn=1,type,nrGarduri1=10,nrGarduri2=10;
            fisier();
            closegraph();
            menu();
      }
}

void classament()
{
    initwindow(600,600);
    settextstyle(8,HORIZ_DIR,5);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(150,110,"LAST 7 GAMES");//afiseaza titlul
    setcolor(RED);
    rectangle(140,100,470,160);
    setcolor(15);
    outtextxy(50,210,"NAMES");
    outtextxy(400,210,"WINNER");
    settextstyle(8,HORIZ_DIR,2);
    ifstream fin("nume.in");//se deshide fisierul pentru citire
    tabel nume[8];
    int i=7;
    char aux[100];
    int wide=260;
    setcolor(RED);
    line(50,250,550,250);
    while (fin >> aux&&i>0)//se citesc numele din fisier si se pun in "nume" de la dreapta la stanga
        strcpy(nume[i--],aux);
    fin.close();
    ofstream fout("nume.in", ios::trunc); // se deschidere fisier pentru a pastra numele
    setcolor(15);
    for(int j=i+1;j<=7;j++){//afisam in acest fel pentru ca cea mai veche lupta sa se afle pe primul loc
        setcolor(15);
        char *p;
        strcpy(aux,nume[j]);
        p=strtok(aux,".");//numele sunt separate prin punct
        int nr=2,legth=50;
        while(p&&nr){
           int legth2=textwidth(p);//se calculeaza mereu distanta la care trebuie puse
            outtextxy(legth,wide,p);
            legth+=legth2+10;
            if(nr==2)
                {outtextxy(legth,wide,"vs");// se pune vs intre cele 2 numel
                    legth2=textwidth("vs");
                     legth+=legth2+10;}

            nr--;
            p=strtok(NULL,".");}
        outtextxy(400,wide,p);
          wide+=30;
          setcolor(RED);
           line(50,wide-10,550,wide-10);//linia care desparte 2 meciuri
           line(300,wide-40,300,wide-10);}//linia dintre names si winner
  for(int j=7;j>=i+1;j--)//se pun  numele inapoi in fisier
        fout<<nume[j]<<" ";
    fout.close();
    setfillstyle(SOLID_FILL,15);
    setcolor(15);
    rectangle(50,500,250,540);
    floodfill(51,501,15);
    settextstyle(8,HORIZ_DIR,3);
    setbkcolor(15);
    setcolor(0);
    outtextxy(60,510,"BACK TO MENU");
    int x,y;
     while(100){
    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(100);
    getmouseclick(WM_LBUTTONDOWN,x,y);
    if(x>=50&&x<=250&&y>=500&&y<=540)
        closegraph(),menu();}


}
void menu()
{
    initwindow(600, 600, "QUORIDOR MENU");
    setfillstyle(SOLID_FILL,0);
    strcpy(castigator,"unfinished");
    bar(0, 0, 600, 600);
    computer=computertactic1=computertactic2=0;
    setcolor(RED);
    rectangle(100,100,500,200);
    rectangle(105,105,495,195);
    settextstyle(8,HORIZ_DIR,7);
    setbkcolor(0);
    setcolor(WHITE);
    outtextxy(140,120,"quoridor");
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(WHITE);
    Button2vs2.x1=150,Button2vs2.y1=250,Button2vs2.x2=450,Button2vs2.y2=300;
    rectangle(150,250,450,300);
    floodfill(151,250+1,15);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(WHITE);
    setcolor(GREEN);
    outtextxy(200,260,"2 PLAYERS");
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(WHITE);
    Buttoncomp.x1=170,Buttoncomp.y1=350,Buttoncomp.x2=440,Buttoncomp.y2=400;
    rectangle(150,350,450,400);
    floodfill(171,350+1,15);
    settextstyle(8,HORIZ_DIR,4);
    setbkcolor(WHITE);
    setcolor(GREEN);
    outtextxy(220,360,"COMPUTER");
    setcolor(15);
    setfillstyle(SOLID_FILL, 15);
    rectangle(60,30,90,60);
    floodfill(61,31,15);
    setbkcolor(0);
    settextstyle(3,HORIZ_DIR,3);
    setcolor(RED);
    setbkcolor(15);
    outtextxy(70,32,"?");
    setfillstyle(SOLID_FILL, 15);
    setcolor(15);
    rectangle(510,30,540,60);
    floodfill(511,31,15);
    setbkcolor(0);
    settextstyle(3,HORIZ_DIR,3);
    setcolor(RED);
    setbkcolor(15);
    outtextxy(520,32,"$");
   setcolor(WHITE);
    line(0,520,600,520);
    line(50,0,50,600);
    line(550,0,550,600);
    int x,y;
    while(100){
    while(!ismouseclick(WM_LBUTTONDOWN))
        delay(100);
    getmouseclick(WM_LBUTTONDOWN,x,y);

    if(Button2vs2.x1<=x&&Button2vs2.x2>=x&&Button2vs2.y1<=y&&Button2vs2.y2>=y)
        turn=1,closegraph(),namepage1(),computer=0;
    else if(Buttoncomp.x1<=x&&Buttoncomp.x2>=x&&Buttoncomp.y1<=y&&Buttoncomp.y2>=y)
       turn=1,computer=1,computerpage();
    else if(x>=60&&x<=90&&y>=30&&y<=60)
        rulespage1();
    else if(x>=510&&x<=540&&y>=30&&y<=60)
        classament();
    }
}
void alternantacompTactic() {
    initTable();
    bool ok = false;
    int distanta1, distanta2; //distanta de la pion 1/2 la castig
    while(castig()==0)
    {
        afisturn();
         afisgard();
      if(turn==1)
      {
           int x=-1, y=-1;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x >= 800 && x <=1000 && y >= 600 && y <= 650) {
            ok = true;
            break;
        }
        while(mutariPion(x,y)==0 && putGard(x,y)==0){
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
            }
            getmouseclick(WM_LBUTTONDOWN, x, y);
        }
        if(mutariPion(x,y)==1)
        while(move(x,y) == 0){
                while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
                getmouseclick(WM_LBUTTONDOWN, x, y);
            }

        }
        else
        {
            delay(500);
            distanta1 = distantaMinima(iOld1, jOld1, 0) - 1 ;
            distanta2 = distantaMinima(iOld2, jOld2, 16);

            cout<<"Distantele sunt : ";

            cout<<distanta1 << " " <<distanta2 <<"\n";

            int D0 = 0, D1 = 0, D2 = 0, D3 = 0;
            string miscare0 = "null", miscare1 = "null", miscare2 = "null", miscare3 = "null";
            //D si miscare sunt asociate

            //0 -> jos
            //1 -> sus
            //2 -> stanga
            //3 -> dreapta

            if(distanta2 <= distanta1 || nrGarduri2 == 0) {
                cout<<"Am intrat pe prima varianta "<<"\n";
                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                    //daca nu are gard in jos
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, jos
                    //operatia 1, jos peste pion
                    //operatia 2, jos, diagonala stanga
                    //operatia 3, jos, diagonala dreapta

                    if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                        v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                        D0 = v[0].distanta;
                        miscare0 = "jos";
                    }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                        if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                            v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                            D0 = v[1].distanta;
                            miscare0 = "jos peste pion";
                        }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                            //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                            if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D0 = v[2].distanta;
                                    miscare0 = "jos diagonala stanga";
                                }else {
                                    D0 = v[3].distanta;
                                    miscare0 = "jos diagonala dreapta";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D0 = v[2].distanta;
                                miscare0 = "jos diagonala stanga";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D0 = v[3].distanta;
                                miscare0 = "jos diagonala dreapta";
                            }

                        }
                    }
                }
                if(tabla[iOld2 - 1][jOld2].info == 2) {
                    //daca nu are gard in sus
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, sus
                    //operatia 1, sus peste pion
                    //operatia 2, sus, diagonala stanga
                    //operatia 3, sus, diagonala dreapta

                    if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                        v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                        D1 = v[0].distanta;
                        miscare1 = "sus";
                    }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                        if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                            v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                            D1 = v[1].distanta;
                            miscare1 = "sus peste pion";
                        }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                            if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D1 = v[2].distanta;
                                    miscare1 = "sus diagonala stanga";
                                }else {
                                    D1 = v[3].distanta;
                                    miscare1 = "sus diagonala dreapta";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D1 = v[2].distanta;
                                miscare1 = "sus diagonala stanga";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D1 = v[3].distanta;
                                miscare1 = "sus diagonala dreapta";
                            }

                        }
                    }

                }
                if(tabla[iOld2][jOld2 - 1].info == 2) {
                    //daca nu are gard in stanga
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, stanga
                    //operatia 1, stanga peste pion
                    //operatia 2, stanga diagonala jos
                    //operatia 3, stanga diagonala sus

                    if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                        v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                        D2 = v[0].distanta;
                        miscare2 = "stanga";
                    }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                        if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                            v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                            D2 = v[1].distanta;
                            miscare2 = "stanga peste pion";
                        }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                            if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D2 = v[2].distanta;
                                    miscare2 = "stanga diagonala jos";
                                }else {
                                    D2 = v[3].distanta;
                                    miscare2 = "stanga diagonala sus";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D2 = v[2].distanta;
                                miscare2 = "stanga diagonala jos";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D2 = v[3].distanta;
                                miscare2 = "stanga diagonala sus";
                            }
                        }

                    }
                }
                if(tabla[iOld2][jOld2 + 1].info == 2) {
                    //daca nu are gard in dreapta
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, dreapta
                    //operatia 1, dreapta peste pion
                    //operatia 2, dreapta diagonala jos
                    //operatia 3, dreapta diagonala sus

                    if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                        v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                        D3 = v[0].distanta;
                        miscare3 = "dreapta";
                    }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                        if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                            v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                            D3 = v[1].distanta;
                            miscare3 = "dreapta peste pion";
                        }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                            if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                            }
                            if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D3 = v[2].distanta;
                                    miscare3 = "dreapta diagonala jos";
                                }else {
                                    D3 = v[3].distanta;
                                    miscare3 = "dreapta diagonala sus";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D3 = v[2].distanta;
                                miscare3 = "dreapta diagonala jos";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D3 = v[3].distanta;
                                miscare3 = "dreapta diagonala sus";
                            }

                        }
                    }

                }

                bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                cout<<"Distantele sunt in felul urmator : "<<"\n";

                cout<<"Daca fac "<< miscare0 << " distanta este : "<<D0<<"\n";
                cout<<"Daca fac "<< miscare1 << " distanta este : "<<D1<<"\n";
                cout<<"Daca fac "<< miscare2 << " distanta este : "<<D2<<"\n";
                cout<<"Daca fac "<< miscare3 << " distanta este : "<<D3<<"\n";
                //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                if(D0 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D0)
                            ok0 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D0) {
                            ok0 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D0) {
                            ok0 = false;
                        }
                    }
                }else ok0 = false;
                if(D1 != 0) {
                    if(D0 !=0 ) {
                        if(D0 < D1)
                            ok1 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D1) {
                            ok1 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D1) {
                            ok1 = false;
                        }
                    }
                }else ok1 = false;
                if(D2 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D2)
                            ok2 = false;
                    }
                    if(D0 != 0) {
                        if(D0 < D2) {
                            ok2 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D2) {
                            ok2 = false;
                        }
                    }
                }else ok2 = false;
                if(D3 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D3)
                            ok3 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D3) {
                            ok3 = false;
                        }
                    }
                    if(D0 !=0 ){
                        if(D0 < D3) {
                            ok3 = false;
                        }
                    }
                }else ok3 = false;

                //cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                if(ok0 == true) {
                    if(miscare0 == "jos") {
                        move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                    }else if(miscare0 == "jos peste pion") {
                        move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                    }else if(miscare0 == "jos diagonala stanga") {
                        move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                    }else if(miscare0 == "jos diagonala dreapta") {
                        move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                    }
                }else if(ok1 == true) {
                    if(miscare1 == "sus") {
                        move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                    }else if(miscare1 == "sus peste pion") {
                        move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                    }else if(miscare1 == "sus diagonala stanga") {
                        move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                    }else if(miscare1 == "sus diagonala dreapta") {
                        move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                    }
                }else if(ok2 == true) {
                    if(miscare2 == "stanga") {
                        move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                    }else if(miscare2 == "stanga peste pion") {
                        move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                    }else if(miscare2 == "stanga diagonala jos") {
                        move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                    }else if(miscare2 == "stanga diagonala sus") {
                        move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                    }
                }else if(ok3 == true) {
                    if(miscare3 == "dreapta") {
                        move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                    }else if(miscare3 == "dreapta peste pion") {
                        move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                    }else if(miscare3 == "dreapta diagonala jos") {
                        move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                    }else if(miscare3 == "dreapta diagonala sus") {
                        move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                    }
                }
            }else if(distanta2 > distanta1 && nrGarduri2 != 0) {
                cout<<"Am intrat pe a 2 a varianta"<<"\n";

                for(int i = 0; i<6; i++) {
                    d1nou[i].distanta = 0;
                }

                //sus spre stanga
                if(tabla[iOld1 - 1][jOld1].info == 2 && tabla[iOld1 - 1][jOld1 - 1].info == 2 && tabla[iOld1 - 1][jOld1 - 2].info == 2) {
                    tabla[iOld1 - 1][jOld1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 2].info = 0;
                    d1nou[0].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[0].operatie = 0;
                    tabla[iOld1 - 1][jOld1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 2].info = 2;
                }
                //sus spre dreapta
                if(tabla[iOld1 - 1][jOld1].info == 2 && tabla[iOld1 - 1][jOld1 + 1].info == 2 && tabla[iOld1 - 1][jOld1 + 2].info == 2) {
                    tabla[iOld1 - 1][jOld1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 2].info = 0;
                    d1nou[1].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[1].operatie = 1;
                    tabla[iOld1 - 1][jOld1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 2].info = 2;
                }
                //stanga jos
                if(tabla[iOld1][jOld1 - 1].info == 2 && tabla[iOld1 - 1][jOld1 - 1].info == 2 && tabla[iOld1 - 2][jOld1 - 1].info == 2) {
                    tabla[iOld1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 2][jOld1 - 1].info = 0;
                    d1nou[2].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[2].operatie = 2;
                    tabla[iOld1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 2][jOld1 - 1].info = 2;
                }
                //dreapta jos
                if(tabla[iOld1][jOld1 + 1].info == 2 && tabla[iOld1 - 1][jOld1 + 1].info == 2 && tabla[iOld1 - 2][jOld1 + 1].info == 2) {
                    tabla[iOld1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 2][jOld1 + 1].info = 0;
                    d1nou[3].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[3].operatie = 3;
                    tabla[iOld1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 2][jOld1 + 1].info = 2;
                }
                //jos spre stanga
                if(tabla[iOld1 + 1][jOld1].info == 2 && tabla[iOld1 + 1][jOld1 - 1].info == 2 && tabla[iOld1 + 1][jOld1 - 2].info == 2) {
                    tabla[iOld1 + 1][jOld1].info = 0;
                    tabla[iOld1 + 1][jOld1 - 1].info = 0;
                    tabla[iOld1 + 1][jOld1 - 2].info = 0;
                    d1nou[4].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[4].operatie = 4;
                    tabla[iOld1 + 1][jOld1].info = 2;
                    tabla[iOld1 + 1][jOld1 - 1].info = 2;
                    tabla[iOld1 + 1][jOld1 - 2].info = 2;
                }
                //jos spre dreapta
                if(tabla[iOld1 + 1][jOld1].info == 2 && tabla[iOld1 + 1][jOld1 + 1].info == 2 && tabla[iOld1 + 1][jOld1 + 2].info == 2) {
                    tabla[iOld1 + 1][jOld1].info = 0;
                    tabla[iOld1 + 1][jOld1 + 1].info = 0;
                    tabla[iOld1 + 1][jOld1 + 2].info = 0;
                    d1nou[5].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[5].operatie = 5;
                    tabla[iOld1 + 1][jOld1].info = 2;
                    tabla[iOld1 + 1][jOld1 + 1].info = 2;
                    tabla[iOld1 + 1][jOld1 + 2].info = 2;
                }


                cout<<"Daca pun gard sus spre stanga distanta e : "<<d1nou[0].distanta<<"\n";
                cout<<"Daca pun gard sus spre dreapta distanta e : "<<d1nou[1].distanta<<"\n";
                cout<<"Daca pun gard stanga jos distanta e : "<<d1nou[2].distanta<<"\n";
                cout<<"Daca pun gard dreapta jos distanta e : "<<d1nou[3].distanta<<"\n";
                cout<<"Daca pun gard jos spre stanga distanta e : "<<d1nou[4].distanta<<"\n";
                cout<<"Daca pun gard jos spre dreapta distanta e : "<<d1nou[5].distanta<<"\n";
                cout<<"-----------------------------------------------------------"<<"\n";

                bool sort;
                do{
                    sort = true;
                    for(int i = 0; i<5; i++) {
                        if(d1nou[i].distanta < d1nou[i + 1].distanta) {
                            swap(d1nou[i], d1nou[i + 1]);
                            sort = false;
                        }
                    }
                }while (!sort);

                int valoare = d1nou[0].distanta; //valoare ajutatoare pt a compara distantele egale daca se pune gard
                int cntValoare1 = 0; //se contorizeaza valorile egale, diferite de 0
                int cntDiferenta = 0; //se contorizeaza valorile diferite de 0

                for(int i = 0; i<6; i++) {
                    if(d1nou[i].distanta == valoare) {
                        cntValoare1++;
                    }
                    if(d1nou[i].distanta != 0)  {
                        cntDiferenta++;
                    }
                }

                if(cntDiferenta == cntValoare1) {
                    cout<<"Nu are rost sa pun gard "<<"\n";
                    if(tabla[iOld2 + 1][jOld2].info == 2)  {
                        //daca nu are gard in jos
                        mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                        //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                        //operatia 0, jos
                        //operatia 1, jos peste pion
                        //operatia 2, jos, diagonala stanga
                        //operatia 3, jos, diagonala dreapta

                        if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                            v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                            D0 = v[0].distanta;
                            miscare0 = "jos";
                        }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                            if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                D0 = v[1].distanta;
                                miscare0 = "jos peste pion";
                            }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                    v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                }
                                if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                    v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                }

                                if(v[2].distanta != 0 && v[3].distanta !=0) {
                                    if(v[2].distanta < v[3].distanta) {
                                        D0 = v[2].distanta;
                                        miscare0 = "jos diagonala stanga";
                                    }else {
                                        D0 = v[3].distanta;
                                        miscare0 = "jos diagonala dreapta";
                                    }
                                }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                    D0 = v[2].distanta;
                                    miscare0 = "jos diagonala stanga";
                                }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                    D0 = v[3].distanta;
                                    miscare0 = "jos diagonala dreapta";
                                }

                            }
                        }
                }
                    if(tabla[iOld2 - 1][jOld2].info == 2) {
                        //daca nu are gard in sus
                        mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                        //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                        //operatia 0, sus
                        //operatia 1, sus peste pion
                        //operatia 2, sus, diagonala stanga
                        //operatia 3, sus, diagonala dreapta

                        if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                            v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                            D1 = v[0].distanta;
                            miscare1 = "sus";
                        }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                            if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                D1 = v[1].distanta;
                                miscare1 = "sus peste pion";
                            }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                    v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                }
                                if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                    v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                }

                                if(v[2].distanta != 0 && v[3].distanta !=0) {
                                    if(v[2].distanta < v[3].distanta) {
                                        D1 = v[2].distanta;
                                        miscare1 = "sus diagonala stanga";
                                    }else {
                                        D1 = v[3].distanta;
                                        miscare1 = "sus diagonala dreapta";
                                    }
                                }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                    D1 = v[2].distanta;
                                    miscare1 = "sus diagonala stanga";
                                }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                    D1 = v[3].distanta;
                                    miscare1 = "sus diagonala dreapta";
                                }

                            }
                        }

                }
                    if(tabla[iOld2][jOld2 - 1].info == 2) {
                        //daca nu are gard in stanga
                        mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                        //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                        //operatia 0, stanga
                        //operatia 1, stanga peste pion
                        //operatia 2, stanga diagonala jos
                        //operatia 3, stanga diagonala sus

                        if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                            v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                            D2 = v[0].distanta;
                            miscare2 = "stanga";
                        }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                            if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                D2 = v[1].distanta;
                                miscare2 = "stanga peste pion";
                            }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                    v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                }
                                if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                    v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                }

                                if(v[2].distanta != 0 && v[3].distanta !=0) {
                                    if(v[2].distanta < v[3].distanta) {
                                        D2 = v[2].distanta;
                                        miscare2 = "stanga diagonala jos";
                                    }else {
                                        D2 = v[3].distanta;
                                        miscare2 = "stanga diagonala sus";
                                    }
                                }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                    D2 = v[2].distanta;
                                    miscare2 = "stanga diagonala jos";
                                }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                    D2 = v[3].distanta;
                                    miscare2 = "stanga diagonala sus";
                                }
                            }

                        }
                }
                    if(tabla[iOld2][jOld2 + 1].info == 2) {
                        //daca nu are gard in dreapta
                        mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                        //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                        //operatia 0, dreapta
                        //operatia 1, dreapta peste pion
                        //operatia 2, dreapta diagonala jos
                        //operatia 3, dreapta diagonala sus

                        if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                            v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                            D3 = v[0].distanta;
                            miscare3 = "dreapta";
                        }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                            if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                D3 = v[1].distanta;
                                miscare3 = "dreapta peste pion";
                            }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                    v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                }
                                if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                    v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                }

                                if(v[2].distanta != 0 && v[3].distanta !=0) {
                                    if(v[2].distanta < v[3].distanta) {
                                        D3 = v[2].distanta;
                                        miscare3 = "dreapta diagonala jos";
                                    }else {
                                        D3 = v[3].distanta;
                                        miscare3 = "dreapta diagonala sus";
                                    }
                                }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                    D3 = v[2].distanta;
                                    miscare3 = "dreapta diagonala jos";
                                }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                    D3 = v[3].distanta;
                                    miscare3 = "dreapta diagonala sus";
                                }

                            }
                        }

                }

                    bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                   // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                    if(D0 != 0) {
                        if(D1 !=0 ) {
                            if(D1 < D0)
                                ok0 = false;
                        }
                        if(D2 != 0) {
                            if(D2 < D0) {
                                ok0 = false;
                            }
                        }
                        if(D3 !=0 ){
                            if(D3 < D0) {
                                ok0 = false;
                            }
                        }
                    }else ok0 = false;
                    if(D1 != 0) {
                        if(D0 !=0 ) {
                            if(D0 < D1)
                                ok1 = false;
                        }
                        if(D2 != 0) {
                            if(D2 < D1) {
                                ok1 = false;
                            }
                        }
                        if(D3 !=0 ){
                            if(D3 < D1) {
                                ok1 = false;
                            }
                        }
                    }else ok1 = false;
                    if(D2 != 0) {
                        if(D1 !=0 ) {
                            if(D1 < D2)
                                ok2 = false;
                        }
                        if(D0 != 0) {
                            if(D0 < D2) {
                                ok2 = false;
                            }
                        }
                        if(D3 !=0 ){
                            if(D3 < D2) {
                                ok2 = false;
                            }
                        }
                    }else ok2 = false;
                    if(D3 != 0) {
                        if(D1 !=0 ) {
                            if(D1 < D3)
                                ok3 = false;
                        }
                        if(D2 != 0) {
                            if(D2 < D3) {
                                ok3 = false;
                            }
                        }
                        if(D0 !=0 ){
                            if(D0 < D3) {
                                ok3 = false;
                            }
                        }
                    }else ok3 = false;

                    //cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                    //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                    if(ok0 == true) {
                            cout<<miscare0<<"\n";
                            if(miscare0 == "jos") {
                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                            }else if(miscare0 == "jos peste pion") {
                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                            }else if(miscare0 == "jos diagonala stanga") {
                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                            }else if(miscare0 == "jos diagonala dreapta") {
                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                            }
                        }else if(ok1 == true) {
                            cout<<miscare1<<"\n";
                            if(miscare1 == "sus") {
                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                            }else if(miscare1 == "sus peste pion") {
                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                            }else if(miscare1 == "sus diagonala stanga") {
                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                            }else if(miscare1 == "sus diagonala dreapta") {
                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                            }
                        }else if(ok2 == true) {
                            cout<<miscare2<<"\n";
                            if(miscare2 == "stanga") {
                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                            }else if(miscare2 == "stanga peste pion") {
                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                            }else if(miscare2 == "stanga diagonala jos") {
                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                            }else if(miscare2 == "stanga diagonala sus") {
                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                            }
                        }else if(ok3 == true) {
                            cout<<miscare3<<"\n";
                            if(miscare3 == "dreapta") {
                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                            }else if(miscare3 == "dreapta peste pion") {
                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                            }else if(miscare3 == "dreapta diagonala jos") {
                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                            }else if(miscare3 == "dreapta diagonala sus") {
                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                }
                            }
                    }else {
                        bool verif = false;
                        for(int i = 0; i<=5; i++) {
                            if(d1nou[i].distanta != 0) {
                                verif = true;
                                if( d1nou[i].operatie == 0 ) {
                                    if(putGard(tabla[iOld1 - 1][jOld1 - 2].x1 + 1, tabla[iOld1 - 1][jOld1 - 2].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                        //cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                        //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            if(miscare0 == "jos") {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                     break;
                                }else if( d1nou[i].operatie == 1 ) {
                                    if(putGard(tabla[iOld1 - 1][jOld1].x1 + 1, tabla[iOld1 - 1][jOld1].y1 + 1) == 0 ) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                           // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                           // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                           // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 2 ) {
                                    if(putGard(tabla[iOld1][jOld1 - 1].x1 + 1, tabla[iOld1][jOld1 - 1].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                            //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                        }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 3 ) {
                                    if(putGard(tabla[iOld1][jOld1 + 1].x1 + 1, tabla[iOld1][jOld1 + 1].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                    // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                    // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                    // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                            if(miscare0 == "jos") {
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 4 ) {
                                    if(putGard(tabla[iOld1 + 1][jOld1 - 2].x1 + 1, tabla[iOld1][jOld1 - 2].y1 + 1) == 0) {
                                            if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                        // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                        }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 5 ) {
                                    if(putGard(tabla[iOld1 + 1][jOld1].x1 + 1, tabla[iOld1 + 1][jOld1].y1 + 1) == 0) {
                                                                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                    //  cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                    // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            if(miscare0 == "jos") {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }
                                }
                            }


                        if(verif == false) {
                                cout<<"Nu pot pune gard si fac miscare : ";
                                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                //daca nu are gard in jos
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, jos
                                //operatia 1, jos peste pion
                                //operatia 2, jos, diagonala stanga
                                //operatia 3, jos, diagonala dreapta

                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                    D0 = v[0].distanta;
                                    miscare0 = "jos";
                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                        D0 = v[1].distanta;
                                        miscare0 = "jos peste pion";
                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D0 = v[2].distanta;
                                                miscare0 = "jos diagonala stanga";
                                            }else {
                                                D0 = v[3].distanta;
                                                miscare0 = "jos diagonala dreapta";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D0 = v[2].distanta;
                                            miscare0 = "jos diagonala stanga";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D0 = v[3].distanta;
                                            miscare0 = "jos diagonala dreapta";
                                        }

                                    }
                                }
                            }
                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                //daca nu are gard in sus
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, sus
                                //operatia 1, sus peste pion
                                //operatia 2, sus, diagonala stanga
                                //operatia 3, sus, diagonala dreapta

                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                    D1 = v[0].distanta;
                                    miscare1 = "sus";
                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                        D1 = v[1].distanta;
                                        miscare1 = "sus peste pion";
                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D1 = v[2].distanta;
                                                miscare1 = "sus diagonala stanga";
                                            }else {
                                                D1 = v[3].distanta;
                                                miscare1 = "sus diagonala dreapta";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D1 = v[2].distanta;
                                            miscare1 = "sus diagonala stanga";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D1 = v[3].distanta;
                                            miscare1 = "sus diagonala dreapta";
                                        }

                                    }
                                }

                            }
                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                //daca nu are gard in stanga
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, stanga
                                //operatia 1, stanga peste pion
                                //operatia 2, stanga diagonala jos
                                //operatia 3, stanga diagonala sus

                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                    D2 = v[0].distanta;
                                    miscare2 = "stanga";
                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                        D2 = v[1].distanta;
                                        miscare2 = "stanga peste pion";
                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D2 = v[2].distanta;
                                                miscare2 = "stanga diagonala jos";
                                            }else {
                                                D2 = v[3].distanta;
                                                miscare2 = "stanga diagonala sus";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D2 = v[2].distanta;
                                            miscare2 = "stanga diagonala jos";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D2 = v[3].distanta;
                                            miscare2 = "stanga diagonala sus";
                                        }
                                    }

                                }
                            }
                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                //daca nu are gard in dreapta
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, dreapta
                                //operatia 1, dreapta peste pion
                                //operatia 2, dreapta diagonala jos
                                //operatia 3, dreapta diagonala sus

                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                    D3 = v[0].distanta;
                                    miscare3 = "dreapta";
                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                        D3 = v[1].distanta;
                                        miscare3 = "dreapta peste pion";
                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                        }
                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D3 = v[2].distanta;
                                                miscare3 = "dreapta diagonala jos";
                                            }else {
                                                D3 = v[3].distanta;
                                                miscare3 = "dreapta diagonala sus";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D3 = v[2].distanta;
                                            miscare3 = "dreapta diagonala jos";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D3 = v[3].distanta;
                                            miscare3 = "dreapta diagonala sus";
                                        }

                                    }
                                }

                            }

                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                            if(D0 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D0)
                                        ok0 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D0) {
                                        ok0 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D0) {
                                        ok0 = false;
                                    }
                                }
                            }else ok0 = false;
                            if(D1 != 0) {
                                if(D0 !=0 ) {
                                    if(D0 < D1)
                                        ok1 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D1) {
                                        ok1 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D1) {
                                        ok1 = false;
                                    }
                                }
                            }else ok1 = false;
                            if(D2 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D2)
                                        ok2 = false;
                                }
                                if(D0 != 0) {
                                    if(D0 < D2) {
                                        ok2 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D2) {
                                        ok2 = false;
                                    }
                                }
                            }else ok2 = false;
                            if(D3 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D3)
                                        ok3 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D3) {
                                        ok3 = false;
                                    }
                                }
                                if(D0 !=0 ){
                                    if(D0 < D3) {
                                        ok3 = false;
                                    }
                                }
                            }else ok3 = false;

                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                        //  cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                            if(ok0 == true) {
                                cout<<miscare0<<" "<<"\n";
                                if(miscare0 == "jos") {
                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                }else if(miscare0 == "jos peste pion") {
                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                }else if(miscare0 == "jos diagonala stanga") {
                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                }else if(miscare0 == "jos diagonala dreapta") {
                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                }
                            }else if(ok1 == true) {
                                cout<<miscare1<<" "<<"\n";
                                if(miscare1 == "sus") {
                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                }else if(miscare1 == "sus peste pion") {
                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                }else if(miscare1 == "sus diagonala stanga") {
                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                }else if(miscare1 == "sus diagonala dreapta") {
                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                }
                            }else if(ok2 == true) {
                                cout<<miscare2<<" "<<"\n";
                                if(miscare2 == "stanga") {
                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                }else if(miscare2 == "stanga peste pion") {
                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                }else if(miscare2 == "stanga diagonala jos") {
                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                }else if(miscare2 == "stanga diagonala sus") {
                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                }
                            }else if(ok3 == true) {
                                cout<<miscare3<<" "<<"\n";
                                if(miscare3 == "dreapta") {
                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                }else if(miscare3 == "dreapta peste pion") {
                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                }else if(miscare3 == "dreapta diagonala jos") {
                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                }else if(miscare3 == "dreapta diagonala sus") {
                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                }
                            }
                        }
                    }
                }

            }

        turn=3-turn;
        }

        if(ok == true) {
            iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8,turn=1,type,nrGarduri1=10,nrGarduri2=10;
            fisier();
            closegraph();
            menu();
        }
}
void alternantacompTacticMedium() {
    initTable();
    bool ok = false;
    int distanta1, distanta2; //distanta de la pion 1/2 la castig
    while(castig()==0)
    {
        afisturn();
         afisgard();
      if(turn==1)
      {
           int x=-1, y=-1;
        while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(20);
        }
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x >= 800 && x <=1000 && y >= 600 && y <= 650) {
            ok = true;
            break;
        }
        while(mutariPion(x,y)==0 && putGard(x,y)==0){
            while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
            }
            getmouseclick(WM_LBUTTONDOWN, x, y);
        }
        if(mutariPion(x,y)==1)
        while(move(x,y) == 0){
                while (!ismouseclick(WM_LBUTTONDOWN)) {
                    delay(100);
                }
                getmouseclick(WM_LBUTTONDOWN, x, y);
            }

        }
        else
        {
            delay(500);
            distanta1 = distantaMinima(iOld1, jOld1, 0) + 1;
            distanta2 = distantaMinima(iOld2, jOld2, 16);

            cout<<"Distantele sunt : ";

            cout<<distanta1 << " " <<distanta2 <<"\n";

            int D0 = 0, D1 = 0, D2 = 0, D3 = 0;
            string miscare0 = "null", miscare1 = "null", miscare2 = "null", miscare3 = "null";
            //D si miscare sunt asociate

            //0 -> jos
            //1 -> sus
            //2 -> stanga
            //3 -> dreapta

            if(distanta2 <= distanta1 || nrGarduri2 == 0) {
                cout<<"Am intrat pe prima varianta "<<"\n";
                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                    //daca nu are gard in jos
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, jos
                    //operatia 1, jos peste pion
                    //operatia 2, jos, diagonala stanga
                    //operatia 3, jos, diagonala dreapta

                    if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                        v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                        D0 = v[0].distanta;
                        miscare0 = "jos";
                    }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                        if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                            v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                            D0 = v[1].distanta;
                            miscare0 = "jos peste pion";
                        }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                            //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                            if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D0 = v[2].distanta;
                                    miscare0 = "jos diagonala stanga";
                                }else {
                                    D0 = v[3].distanta;
                                    miscare0 = "jos diagonala dreapta";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D0 = v[2].distanta;
                                miscare0 = "jos diagonala stanga";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D0 = v[3].distanta;
                                miscare0 = "jos diagonala dreapta";
                            }

                        }
                    }
                }
                if(tabla[iOld2 - 1][jOld2].info == 2) {
                    //daca nu are gard in sus
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, sus
                    //operatia 1, sus peste pion
                    //operatia 2, sus, diagonala stanga
                    //operatia 3, sus, diagonala dreapta

                    if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                        v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                        D1 = v[0].distanta;
                        miscare1 = "sus";
                    }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                        if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                            v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                            D1 = v[1].distanta;
                            miscare1 = "sus peste pion";
                        }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                            if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D1 = v[2].distanta;
                                    miscare1 = "sus diagonala stanga";
                                }else {
                                    D1 = v[3].distanta;
                                    miscare1 = "sus diagonala dreapta";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D1 = v[2].distanta;
                                miscare1 = "sus diagonala stanga";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D1 = v[3].distanta;
                                miscare1 = "sus diagonala dreapta";
                            }

                        }
                    }

                }
                if(tabla[iOld2][jOld2 - 1].info == 2) {
                    //daca nu are gard in stanga
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, stanga
                    //operatia 1, stanga peste pion
                    //operatia 2, stanga diagonala jos
                    //operatia 3, stanga diagonala sus

                    if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                        v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                        D2 = v[0].distanta;
                        miscare2 = "stanga";
                    }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                        if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                            v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                            D2 = v[1].distanta;
                            miscare2 = "stanga peste pion";
                        }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                            if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                            }
                            if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D2 = v[2].distanta;
                                    miscare2 = "stanga diagonala jos";
                                }else {
                                    D2 = v[3].distanta;
                                    miscare2 = "stanga diagonala sus";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D2 = v[2].distanta;
                                miscare2 = "stanga diagonala jos";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D2 = v[3].distanta;
                                miscare2 = "stanga diagonala sus";
                            }
                        }

                    }
                }
                if(tabla[iOld2][jOld2 + 1].info == 2) {
                    //daca nu are gard in dreapta
                    mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                    //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                    //operatia 0, dreapta
                    //operatia 1, dreapta peste pion
                    //operatia 2, dreapta diagonala jos
                    //operatia 3, dreapta diagonala sus

                    if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                        v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                        D3 = v[0].distanta;
                        miscare3 = "dreapta";
                    }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                        if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                            v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                            D3 = v[1].distanta;
                            miscare3 = "dreapta peste pion";
                        }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                            if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                            }
                            if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                            }

                            if(v[2].distanta != 0 && v[3].distanta !=0) {
                                if(v[2].distanta < v[3].distanta) {
                                    D3 = v[2].distanta;
                                    miscare3 = "dreapta diagonala jos";
                                }else {
                                    D3 = v[3].distanta;
                                    miscare3 = "dreapta diagonala sus";
                                }
                            }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                D3 = v[2].distanta;
                                miscare3 = "dreapta diagonala jos";
                            }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                D3 = v[3].distanta;
                                miscare3 = "dreapta diagonala sus";
                            }

                        }
                    }

                }

                bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                cout<<"Distantele sunt in felul urmator : "<<"\n";

                cout<<"Daca fac "<< miscare0 << " distanta este : "<<D0<<"\n";
                cout<<"Daca fac "<< miscare1 << " distanta este : "<<D1<<"\n";
                cout<<"Daca fac "<< miscare2 << " distanta este : "<<D2<<"\n";
                cout<<"Daca fac "<< miscare3 << " distanta este : "<<D3<<"\n";
                //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                if(D0 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D0)
                            ok0 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D0) {
                            ok0 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D0) {
                            ok0 = false;
                        }
                    }
                }else ok0 = false;
                if(D1 != 0) {
                    if(D0 !=0 ) {
                        if(D0 < D1)
                            ok1 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D1) {
                            ok1 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D1) {
                            ok1 = false;
                        }
                    }
                }else ok1 = false;
                if(D2 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D2)
                            ok2 = false;
                    }
                    if(D0 != 0) {
                        if(D0 < D2) {
                            ok2 = false;
                        }
                    }
                    if(D3 !=0 ){
                        if(D3 < D2) {
                            ok2 = false;
                        }
                    }
                }else ok2 = false;
                if(D3 != 0) {
                    if(D1 !=0 ) {
                        if(D1 < D3)
                            ok3 = false;
                    }
                    if(D2 != 0) {
                        if(D2 < D3) {
                            ok3 = false;
                        }
                    }
                    if(D0 !=0 ){
                        if(D0 < D3) {
                            ok3 = false;
                        }
                    }
                }else ok3 = false;

                //cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                if(ok0 == true) {
                    if(miscare0 == "jos") {
                        move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                    }else if(miscare0 == "jos peste pion") {
                        move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                    }else if(miscare0 == "jos diagonala stanga") {
                        move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                    }else if(miscare0 == "jos diagonala dreapta") {
                        move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                    }
                }else if(ok1 == true) {
                    if(miscare1 == "sus") {
                        move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                    }else if(miscare1 == "sus peste pion") {
                        move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                    }else if(miscare1 == "sus diagonala stanga") {
                        move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                    }else if(miscare1 == "sus diagonala dreapta") {
                        move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                    }
                }else if(ok2 == true) {
                    if(miscare2 == "stanga") {
                        move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                    }else if(miscare2 == "stanga peste pion") {
                        move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                    }else if(miscare2 == "stanga diagonala jos") {
                        move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                    }else if(miscare2 == "stanga diagonala sus") {
                        move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                    }
                }else if(ok3 == true) {
                    if(miscare3 == "dreapta") {
                        move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                    }else if(miscare3 == "dreapta peste pion") {
                        move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                    }else if(miscare3 == "dreapta diagonala jos") {
                        move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                    }else if(miscare3 == "dreapta diagonala sus") {
                        move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                    }
                }
            }else if(distanta2 > distanta1 && nrGarduri2 != 0) {
                cout<<"Am intrat pe a 2 a varianta"<<"\n";

                for(int i = 0; i<6; i++) {
                    d1nou[i].distanta = 0;
                }

                //sus spre stanga
                if(tabla[iOld1 - 1][jOld1].info == 2 && tabla[iOld1 - 1][jOld1 - 1].info == 2 && tabla[iOld1 - 1][jOld1 - 2].info == 2) {
                    tabla[iOld1 - 1][jOld1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 2].info = 0;
                    d1nou[0].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[0].operatie = 0;
                    tabla[iOld1 - 1][jOld1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 2].info = 2;
                }
                //sus spre dreapta
                if(tabla[iOld1 - 1][jOld1].info == 2 && tabla[iOld1 - 1][jOld1 + 1].info == 2 && tabla[iOld1 - 1][jOld1 + 2].info == 2) {
                    tabla[iOld1 - 1][jOld1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 2].info = 0;
                    d1nou[1].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[1].operatie = 1;
                    tabla[iOld1 - 1][jOld1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 2].info = 2;
                }
                //stanga jos
                if(tabla[iOld1][jOld1 - 1].info == 2 && tabla[iOld1 - 1][jOld1 - 1].info == 2 && tabla[iOld1 - 2][jOld1 - 1].info == 2) {
                    tabla[iOld1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 1][jOld1 - 1].info = 0;
                    tabla[iOld1 - 2][jOld1 - 1].info = 0;
                    d1nou[2].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[2].operatie = 2;
                    tabla[iOld1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 1][jOld1 - 1].info = 2;
                    tabla[iOld1 - 2][jOld1 - 1].info = 2;
                }
                //dreapta jos
                if(tabla[iOld1][jOld1 + 1].info == 2 && tabla[iOld1 - 1][jOld1 + 1].info == 2 && tabla[iOld1 - 2][jOld1 + 1].info == 2) {
                    tabla[iOld1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 1][jOld1 + 1].info = 0;
                    tabla[iOld1 - 2][jOld1 + 1].info = 0;
                    d1nou[3].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[3].operatie = 3;
                    tabla[iOld1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 1][jOld1 + 1].info = 2;
                    tabla[iOld1 - 2][jOld1 + 1].info = 2;
                }
                //jos spre stanga
                if(tabla[iOld1 + 1][jOld1].info == 2 && tabla[iOld1 + 1][jOld1 - 1].info == 2 && tabla[iOld1 + 1][jOld1 - 2].info == 2) {
                    tabla[iOld1 + 1][jOld1].info = 0;
                    tabla[iOld1 + 1][jOld1 - 1].info = 0;
                    tabla[iOld1 + 1][jOld1 - 2].info = 0;
                    d1nou[4].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[4].operatie = 4;
                    tabla[iOld1 + 1][jOld1].info = 2;
                    tabla[iOld1 + 1][jOld1 - 1].info = 2;
                    tabla[iOld1 + 1][jOld1 - 2].info = 2;
                }
                //jos spre dreapta
                if(tabla[iOld1 + 1][jOld1].info == 2 && tabla[iOld1 + 1][jOld1 + 1].info == 2 && tabla[iOld1 + 1][jOld1 + 2].info == 2) {
                    tabla[iOld1 + 1][jOld1].info = 0;
                    tabla[iOld1 + 1][jOld1 + 1].info = 0;
                    tabla[iOld1 + 1][jOld1 + 2].info = 0;
                    d1nou[5].distanta = distantaMinima(iOld1, jOld1, 0);
                    d1nou[5].operatie = 5;
                    tabla[iOld1 + 1][jOld1].info = 2;
                    tabla[iOld1 + 1][jOld1 + 1].info = 2;
                    tabla[iOld1 + 1][jOld1 + 2].info = 2;
                }


                cout<<"Daca pun gard sus spre stanga distanta e : "<<d1nou[0].distanta<<"\n";
                cout<<"Daca pun gard sus spre dreapta distanta e : "<<d1nou[1].distanta<<"\n";
                cout<<"Daca pun gard stanga jos distanta e : "<<d1nou[2].distanta<<"\n";
                cout<<"Daca pun gard dreapta jos distanta e : "<<d1nou[3].distanta<<"\n";
                cout<<"Daca pun gard jos spre stanga distanta e : "<<d1nou[4].distanta<<"\n";
                cout<<"Daca pun gard jos spre dreapta distanta e : "<<d1nou[5].distanta<<"\n";
                cout<<"-----------------------------------------------------------"<<"\n";

                bool sort;
                do{
                    sort = true;
                    for(int i = 0; i<5; i++) {
                        if(d1nou[i].distanta < d1nou[i + 1].distanta) {
                            swap(d1nou[i], d1nou[i + 1]);
                            sort = false;
                        }
                    }
                }while (!sort);



                    bool verif = false;
                    for(int i = 0; i<=5; i++) {
                            if(d1nou[i].distanta != 0) {
                                verif = true;
                                if( d1nou[i].operatie == 0 ) {
                                    if(putGard(tabla[iOld1 - 1][jOld1 - 2].x1 + 1, tabla[iOld1 - 1][jOld1 - 2].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                        //cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                        //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            if(miscare0 == "jos") {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                     break;
                                }else if( d1nou[i].operatie == 1 ) {
                                    if(putGard(tabla[iOld1 - 1][jOld1].x1 + 1, tabla[iOld1 - 1][jOld1].y1 + 1) == 0 ) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                           // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                           // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                           // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 2 ) {
                                    if(putGard(tabla[iOld1][jOld1 - 1].x1 + 1, tabla[iOld1][jOld1 - 1].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                            //cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                        }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 3 ) {
                                    if(putGard(tabla[iOld1][jOld1 + 1].x1 + 1, tabla[iOld1][jOld1 + 1].y1 + 1) == 0) {
                                        if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                    // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                    // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                    // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                            if(miscare0 == "jos") {
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 4 ) {
                                    if(putGard(tabla[iOld1 + 1][jOld1 - 2].x1 + 1, tabla[iOld1][jOld1 - 2].y1 + 1) == 0) {
                                            if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                                //daca nu are gard in jos
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, jos
                                                //operatia 1, jos peste pion
                                                //operatia 2, jos, diagonala stanga
                                                //operatia 3, jos, diagonala dreapta

                                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                    D0 = v[0].distanta;
                                                    miscare0 = "jos";
                                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                        D0 = v[1].distanta;
                                                        miscare0 = "jos peste pion";
                                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D0 = v[2].distanta;
                                                                miscare0 = "jos diagonala stanga";
                                                            }else {
                                                                D0 = v[3].distanta;
                                                                miscare0 = "jos diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }

                                                    }
                                                }
                                            }
                                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                                //daca nu are gard in sus
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, sus
                                                //operatia 1, sus peste pion
                                                //operatia 2, sus, diagonala stanga
                                                //operatia 3, sus, diagonala dreapta

                                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                    D1 = v[0].distanta;
                                                    miscare1 = "sus";
                                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                        D1 = v[1].distanta;
                                                        miscare1 = "sus peste pion";
                                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D1 = v[2].distanta;
                                                                miscare1 = "sus diagonala stanga";
                                                            }else {
                                                                D1 = v[3].distanta;
                                                                miscare1 = "sus diagonala dreapta";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }

                                                    }
                                                }

                                            }
                                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                                //daca nu are gard in stanga
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, stanga
                                                //operatia 1, stanga peste pion
                                                //operatia 2, stanga diagonala jos
                                                //operatia 3, stanga diagonala sus

                                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                    D2 = v[0].distanta;
                                                    miscare2 = "stanga";
                                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                        D2 = v[1].distanta;
                                                        miscare2 = "stanga peste pion";
                                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D2 = v[2].distanta;
                                                                miscare2 = "stanga diagonala jos";
                                                            }else {
                                                                D2 = v[3].distanta;
                                                                miscare2 = "stanga diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }

                                                }
                                            }
                                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                                //daca nu are gard in dreapta
                                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                                //operatia 0, dreapta
                                                //operatia 1, dreapta peste pion
                                                //operatia 2, dreapta diagonala jos
                                                //operatia 3, dreapta diagonala sus

                                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                    D3 = v[0].distanta;
                                                    miscare3 = "dreapta";
                                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                        D3 = v[1].distanta;
                                                        miscare3 = "dreapta peste pion";
                                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                        }
                                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                        }

                                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                            if(v[2].distanta < v[3].distanta) {
                                                                D3 = v[2].distanta;
                                                                miscare3 = "dreapta diagonala jos";
                                                            }else {
                                                                D3 = v[3].distanta;
                                                                miscare3 = "dreapta diagonala sus";
                                                            }
                                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }

                                                    }
                                                }

                                            }

                                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                            if(D0 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D0)
                                                        ok0 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D0) {
                                                        ok0 = false;
                                                    }
                                                }
                                            }else ok0 = false;
                                            if(D1 != 0) {
                                                if(D0 !=0 ) {
                                                    if(D0 < D1)
                                                        ok1 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D1) {
                                                        ok1 = false;
                                                    }
                                                }
                                            }else ok1 = false;
                                            if(D2 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D2)
                                                        ok2 = false;
                                                }
                                                if(D0 != 0) {
                                                    if(D0 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                                if(D3 !=0 ){
                                                    if(D3 < D2) {
                                                        ok2 = false;
                                                    }
                                                }
                                            }else ok2 = false;
                                            if(D3 != 0) {
                                                if(D1 !=0 ) {
                                                    if(D1 < D3)
                                                        ok3 = false;
                                                }
                                                if(D2 != 0) {
                                                    if(D2 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                                if(D0 !=0 ){
                                                    if(D0 < D3) {
                                                        ok3 = false;
                                                    }
                                                }
                                            }else ok3 = false;

                                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                        // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                            if(ok0 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                if(miscare0 == "jos") {
                                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos peste pion") {
                                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala stanga") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare0 == "jos diagonala dreapta") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok1 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                                if(miscare1 == "sus") {
                                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus peste pion") {
                                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala stanga") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare1 == "sus diagonala dreapta") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }else if(ok2 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                                if(miscare2 == "stanga") {
                                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga peste pion") {
                                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                                }else if(miscare2 == "stanga diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                                }
                                            }else if(ok3 == true) {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                                if(miscare3 == "dreapta") {
                                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta peste pion") {
                                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala jos") {
                                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                                }else if(miscare3 == "dreapta diagonala sus") {
                                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                                }
                                            }
                                        }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }else if( d1nou[i].operatie == 5 ) {
                                    if(putGard(tabla[iOld1 + 1][jOld1].x1 + 1, tabla[iOld1 + 1][jOld1].y1 + 1) == 0) {
                                                                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                            //daca nu are gard in jos
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, jos
                                            //operatia 1, jos peste pion
                                            //operatia 2, jos, diagonala stanga
                                            //operatia 3, jos, diagonala dreapta

                                            if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                                D0 = v[0].distanta;
                                                miscare0 = "jos";
                                            }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                                if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                                    D0 = v[1].distanta;
                                                    miscare0 = "jos peste pion";
                                                }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                                    //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                                    if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                                        v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D0 = v[2].distanta;
                                                            miscare0 = "jos diagonala stanga";
                                                        }else {
                                                            D0 = v[3].distanta;
                                                            miscare0 = "jos diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D0 = v[2].distanta;
                                                        miscare0 = "jos diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D0 = v[3].distanta;
                                                        miscare0 = "jos diagonala dreapta";
                                                    }

                                                }
                                            }
                                        }
                                        if(tabla[iOld2 - 1][jOld2].info == 2) {
                                            //daca nu are gard in sus
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, sus
                                            //operatia 1, sus peste pion
                                            //operatia 2, sus, diagonala stanga
                                            //operatia 3, sus, diagonala dreapta

                                            if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                                v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                                D1 = v[0].distanta;
                                                miscare1 = "sus";
                                            }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                                if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                                    v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                                    D1 = v[1].distanta;
                                                    miscare1 = "sus peste pion";
                                                }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                                    if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                                        v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D1 = v[2].distanta;
                                                            miscare1 = "sus diagonala stanga";
                                                        }else {
                                                            D1 = v[3].distanta;
                                                            miscare1 = "sus diagonala dreapta";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D1 = v[2].distanta;
                                                        miscare1 = "sus diagonala stanga";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D1 = v[3].distanta;
                                                        miscare1 = "sus diagonala dreapta";
                                                    }

                                                }
                                            }

                                        }
                                        if(tabla[iOld2][jOld2 - 1].info == 2) {
                                            //daca nu are gard in stanga
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, stanga
                                            //operatia 1, stanga peste pion
                                            //operatia 2, stanga diagonala jos
                                            //operatia 3, stanga diagonala sus

                                            if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                                v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                                D2 = v[0].distanta;
                                                miscare2 = "stanga";
                                            }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                                if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                                    D2 = v[1].distanta;
                                                    miscare2 = "stanga peste pion";
                                                }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D2 = v[2].distanta;
                                                            miscare2 = "stanga diagonala jos";
                                                        }else {
                                                            D2 = v[3].distanta;
                                                            miscare2 = "stanga diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D2 = v[2].distanta;
                                                        miscare2 = "stanga diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D2 = v[3].distanta;
                                                        miscare2 = "stanga diagonala sus";
                                                    }
                                                }

                                            }
                                        }
                                        if(tabla[iOld2][jOld2 + 1].info == 2) {
                                            //daca nu are gard in dreapta
                                            mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                            //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                            //operatia 0, dreapta
                                            //operatia 1, dreapta peste pion
                                            //operatia 2, dreapta diagonala jos
                                            //operatia 3, dreapta diagonala sus

                                            if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                                v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                                D3 = v[0].distanta;
                                                miscare3 = "dreapta";
                                            }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                                if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                                    v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                                    D3 = v[1].distanta;
                                                    miscare3 = "dreapta peste pion";
                                                }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                                    if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                                        v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                                    }
                                                    if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                                        v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                                    }

                                                    if(v[2].distanta != 0 && v[3].distanta !=0) {
                                                        if(v[2].distanta < v[3].distanta) {
                                                            D3 = v[2].distanta;
                                                            miscare3 = "dreapta diagonala jos";
                                                        }else {
                                                            D3 = v[3].distanta;
                                                            miscare3 = "dreapta diagonala sus";
                                                        }
                                                    }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                                        D3 = v[2].distanta;
                                                        miscare3 = "dreapta diagonala jos";
                                                    }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                                        D3 = v[3].distanta;
                                                        miscare3 = "dreapta diagonala sus";
                                                    }

                                                }
                                            }

                                        }

                                        bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                                        //cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                                        if(D0 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D0)
                                                    ok0 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D0) {
                                                    ok0 = false;
                                                }
                                            }
                                        }else ok0 = false;
                                        if(D1 != 0) {
                                            if(D0 !=0 ) {
                                                if(D0 < D1)
                                                    ok1 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D1) {
                                                    ok1 = false;
                                                }
                                            }
                                        }else ok1 = false;
                                        if(D2 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D2)
                                                    ok2 = false;
                                            }
                                            if(D0 != 0) {
                                                if(D0 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                            if(D3 !=0 ){
                                                if(D3 < D2) {
                                                    ok2 = false;
                                                }
                                            }
                                        }else ok2 = false;
                                        if(D3 != 0) {
                                            if(D1 !=0 ) {
                                                if(D1 < D3)
                                                    ok3 = false;
                                            }
                                            if(D2 != 0) {
                                                if(D2 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                            if(D0 !=0 ){
                                                if(D0 < D3) {
                                                    ok3 = false;
                                                }
                                            }
                                        }else ok3 = false;

                                    //  cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                                    // cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                                        if(ok0 == true) {
                                            if(miscare0 == "jos") {
                                                cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare0<<" "<<"\n";
                                                move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos peste pion") {
                                                move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala stanga") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare0 == "jos diagonala dreapta") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok1 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare1<<" "<<"\n";
                                            if(miscare1 == "sus") {
                                                move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus peste pion") {
                                                move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala stanga") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare1 == "sus diagonala dreapta") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }else if(ok2 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare2<<" "<<"\n";
                                            if(miscare2 == "stanga") {
                                                move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga peste pion") {
                                                move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                            }else if(miscare2 == "stanga diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                            }
                                        }else if(ok3 == true) {
                                            cout<<"Nu am putut pune gard si am facut miscarea : "<<miscare3<<" "<<"\n";
                                            if(miscare3 == "dreapta") {
                                                move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta peste pion") {
                                                move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala jos") {
                                                move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                            }else if(miscare3 == "dreapta diagonala sus") {
                                                move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                            }
                                        }
                                    }else cout<<"Am pus gard"<<"\n";
                                    break;
                                }
                                }
                            }


                    if(verif == false) {
                                cout<<"Nu pot pune gard si fac miscare : ";
                                if(tabla[iOld2 + 1][jOld2].info == 2)  {
                                //daca nu are gard in jos
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, jos
                                //operatia 1, jos peste pion
                                //operatia 2, jos, diagonala stanga
                                //operatia 3, jos, diagonala dreapta

                                if(tabla[iOld2 + 2][jOld2].info == 1) { //daca spatiul de jos este liber <=> operatia 0
                                    v[0].distanta = distantaMinima(iOld2 + 2, jOld2, 16);
                                    D0 = v[0].distanta;
                                    miscare0 = "jos";
                                }else if(tabla[iOld2 + 2][jOld2].info == 3) {//daca spatiul de jos este ocupat cu pionul advers
                                    if(tabla[iOld2 + 3][jOld2].info == 2) { //daca pionul advers nu are in spatele lui gard <=> operatia 1
                                        v[1].distanta = distantaMinima(iOld2 + 4, jOld2, 16);
                                        D0 = v[1].distanta;
                                        miscare0 = "jos peste pion";
                                    }else if( (tabla[iOld2 + 3][jOld2].info == 0) || (iOld2 == 14 && tabla[iOld2 + 2][jOld2].info == 3)) {
                                        //daca pionul advers are in spatele lui gard sau  pionul se afla pe linia 14 si adversarul in fata lui <=> ultimele 2 operatii
                                        if(tabla[iOld2 + 2][jOld2 - 1].info == 2) { //daca in stanga pionului advers nu exista gard <=> operatia 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 + 2][jOld2 + 1].info == 2) { //daca in dreapta pionului advers nu exista gard <=> operatia 3
                                            v[3].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D0 = v[2].distanta;
                                                miscare0 = "jos diagonala stanga";
                                            }else {
                                                D0 = v[3].distanta;
                                                miscare0 = "jos diagonala dreapta";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D0 = v[2].distanta;
                                            miscare0 = "jos diagonala stanga";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D0 = v[3].distanta;
                                            miscare0 = "jos diagonala dreapta";
                                        }

                                    }
                                }
                            }
                            if(tabla[iOld2 - 1][jOld2].info == 2) {
                                //daca nu are gard in sus
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, sus
                                //operatia 1, sus peste pion
                                //operatia 2, sus, diagonala stanga
                                //operatia 3, sus, diagonala dreapta

                                if(tabla[iOld2 - 2][jOld2].info == 1) { //daca spatiul de deasupra pionului este liber <=> operatia 0
                                    v[0].distanta = distantaMinima(iOld2 - 2, jOld2, 16);
                                    D1 = v[0].distanta;
                                    miscare1 = "sus";
                                }else if(tabla[iOld2 - 2][jOld2].info == 3) { //daca pe spatiul de deasupra pionului este pionul advers
                                    if(tabla[iOld2 - 3][jOld2].info == 2) { //daca pionul advers nu are gard deasupra lui <=> operatia 1
                                        v[1].distanta = distantaMinima(iOld2 - 4, jOld2, 16);
                                        D1 = v[1].distanta;
                                        miscare1 = "sus peste pion";
                                    }else if( tabla[iOld2 - 3][jOld2].info == 0 ) { //daca pionul advers are gard deasupra
                                        if(tabla[iOld2 - 2][jOld2 - 1].info == 2) { //daca pionul advers nu are gard in stanga
                                            v[2].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 - 2][jOld2 + 1].info == 2) { //daca pionul advers nu are gard in dreapta
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D1 = v[2].distanta;
                                                miscare1 = "sus diagonala stanga";
                                            }else {
                                                D1 = v[3].distanta;
                                                miscare1 = "sus diagonala dreapta";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D1 = v[2].distanta;
                                            miscare1 = "sus diagonala stanga";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D1 = v[3].distanta;
                                            miscare1 = "sus diagonala dreapta";
                                        }

                                    }
                                }

                            }
                            if(tabla[iOld2][jOld2 - 1].info == 2) {
                                //daca nu are gard in stanga
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, stanga
                                //operatia 1, stanga peste pion
                                //operatia 2, stanga diagonala jos
                                //operatia 3, stanga diagonala sus

                                if(tabla[iOld2][jOld2 - 2].info == 1) { //daca in stanga pionului este spatiu liber
                                    v[0].distanta = distantaMinima(iOld2, jOld2 - 2, 16);
                                    D2 = v[0].distanta;
                                    miscare2 = "stanga";
                                }else if(tabla[iOld2][jOld2 - 2].info == 3) { //daca in stanga pionului este spatiu ocupat de pionul advers
                                    if(tabla[iOld2][jOld2 - 3].info == 2 && jOld2 > 2) { //daca in spatele pionului advers nu este gard <=> operatie 1
                                        v[1].distanta = distantaMinima(iOld2, jOld2 - 4, 16);
                                        D2 = v[1].distanta;
                                        miscare2 = "stanga peste pion";
                                    }else if( (tabla[iOld2][jOld2 - 3].info == 0) || (jOld2 == 2 && tabla[iOld2][jOld2 - 2].info == 3)) { //daca in spatele pionului advers este gard sau e situatie de margine
                                        if(tabla[iOld2 + 1][jOld2 - 2].info == 2) { //daca sub pionul advers nu exista gard <=> operatie 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 - 2, 16);
                                        }
                                        if(tabla[iOld2 - 1][jOld2 - 2].info == 2) { //daca deasupra pionului advers nu exista gard <=> operatie 3
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 - 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D2 = v[2].distanta;
                                                miscare2 = "stanga diagonala jos";
                                            }else {
                                                D2 = v[3].distanta;
                                                miscare2 = "stanga diagonala sus";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D2 = v[2].distanta;
                                            miscare2 = "stanga diagonala jos";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D2 = v[3].distanta;
                                            miscare2 = "stanga diagonala sus";
                                        }
                                    }

                                }
                            }
                            if(tabla[iOld2][jOld2 + 1].info == 2) {
                                //daca nu are gard in dreapta
                                mutare v[4] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}}; //vector de mutari
                                //primul parametru semnifica distanta minima si al 2 lea parametru semnifica operatia
                                //operatia 0, dreapta
                                //operatia 1, dreapta peste pion
                                //operatia 2, dreapta diagonala jos
                                //operatia 3, dreapta diagonala sus

                                if(tabla[iOld2][jOld2 + 2].info == 1) { //daca spatiul este liber <=> operatie 0
                                    v[0].distanta = distantaMinima(iOld2, jOld2 + 2, 16);
                                    D3 = v[0].distanta;
                                    miscare3 = "dreapta";
                                }else if(tabla[iOld2][jOld2 + 2].info == 3 && jOld2 != 14) { //daca spatiul din dreapta este ocupat cu pionul advers
                                    if(tabla[iOld2][jOld2 + 3].info == 2) { //daca pionul advers nu are gard in dreapta sa <=> operatie 1
                                        v[1].distanta = distantaMinima(iOld2, jOld2 + 4, 16);
                                        D3 = v[1].distanta;
                                        miscare3 = "dreapta peste pion";
                                    }else if( (tabla[iOld2][jOld2 + 3].info == 0) || ( jOld2 == 14 && tabla[iOld2][jOld2 + 2].info == 3) ){ //daca pionul advers are gard in spatele sau situatie de margine
                                        if(tabla[iOld2 + 1][jOld2 + 2].info == 2) { //daca nu este gard sub pionul advers <=> operatie 2
                                            v[2].distanta = distantaMinima(iOld2 + 2, jOld2 + 2, 16);
                                        }
                                        if(tabla[iOld2 - 1][jOld2 + 2].info == 2) { //daca nu este gard deasupra pionului advers <=> operatie 3
                                            v[3].distanta = distantaMinima(iOld2 - 2, jOld2 + 2, 16);
                                        }

                                        if(v[2].distanta != 0 && v[3].distanta !=0) {
                                            if(v[2].distanta < v[3].distanta) {
                                                D3 = v[2].distanta;
                                                miscare3 = "dreapta diagonala jos";
                                            }else {
                                                D3 = v[3].distanta;
                                                miscare3 = "dreapta diagonala sus";
                                            }
                                        }else if(v[2].distanta != 0 && v[3].distanta == 0) {
                                            D3 = v[2].distanta;
                                            miscare3 = "dreapta diagonala jos";
                                        }else if(v[2].distanta == 0 && v[3].distanta != 0) {
                                            D3 = v[3].distanta;
                                            miscare3 = "dreapta diagonala sus";
                                        }

                                    }
                                }

                            }

                            bool ok0 = true, ok1 = true, ok2 = true, ok3 = true;

                        // cout<<D0 <<" "<<D1 <<" "<<D2 <<" "<<D3 <<"\n";

                            if(D0 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D0)
                                        ok0 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D0) {
                                        ok0 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D0) {
                                        ok0 = false;
                                    }
                                }
                            }else ok0 = false;
                            if(D1 != 0) {
                                if(D0 !=0 ) {
                                    if(D0 < D1)
                                        ok1 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D1) {
                                        ok1 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D1) {
                                        ok1 = false;
                                    }
                                }
                            }else ok1 = false;
                            if(D2 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D2)
                                        ok2 = false;
                                }
                                if(D0 != 0) {
                                    if(D0 < D2) {
                                        ok2 = false;
                                    }
                                }
                                if(D3 !=0 ){
                                    if(D3 < D2) {
                                        ok2 = false;
                                    }
                                }
                            }else ok2 = false;
                            if(D3 != 0) {
                                if(D1 !=0 ) {
                                    if(D1 < D3)
                                        ok3 = false;
                                }
                                if(D2 != 0) {
                                    if(D2 < D3) {
                                        ok3 = false;
                                    }
                                }
                                if(D0 !=0 ){
                                    if(D0 < D3) {
                                        ok3 = false;
                                    }
                                }
                            }else ok3 = false;

                        // cout<<ok0 <<" "<<ok1 <<" "<<ok2<<" "<<ok3 <<"\n";
                        //  cout<<miscare0<<" "<<miscare1<<" "<<miscare2<<" "<<miscare3<<"\n";

                            if(ok0 == true) {
                                cout<<miscare0<<" "<<"\n";
                                if(miscare0 == "jos") {
                                    move(tabla[iOld2 + 2][jOld2].x1 + 1, tabla[iOld2 + 2][jOld2].y1 + 1);
                                }else if(miscare0 == "jos peste pion") {
                                    move(tabla[iOld2 + 4][jOld2].x1 + 1, tabla[iOld2 + 4][jOld2].y1 + 1);
                                }else if(miscare0 == "jos diagonala stanga") {
                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                }else if(miscare0 == "jos diagonala dreapta") {
                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                }
                            }else if(ok1 == true) {
                                cout<<miscare1<<" "<<"\n";
                                if(miscare1 == "sus") {
                                    move(tabla[iOld2 - 2][jOld2].x1 + 1, tabla[iOld2 - 2][jOld2].y1 + 1);
                                }else if(miscare1 == "sus peste pion") {
                                    move(tabla[iOld2 - 4][jOld2].x1 + 1, tabla[iOld2 - 4][jOld2].y1 + 1);
                                }else if(miscare1 == "sus diagonala stanga") {
                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                }else if(miscare1 == "sus diagonala dreapta") {
                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                }
                            }else if(ok2 == true) {
                                cout<<miscare2<<" "<<"\n";
                                if(miscare2 == "stanga") {
                                    move(tabla[iOld2][jOld2 - 2].x1 + 1, tabla[iOld2][jOld2 - 2].y1 + 1);
                                }else if(miscare2 == "stanga peste pion") {
                                    move(tabla[iOld2][jOld2 - 4].x1 + 1, tabla[iOld2][jOld2 - 4].y1 + 1);
                                }else if(miscare2 == "stanga diagonala jos") {
                                    move(tabla[iOld2 + 2][jOld2 - 2].x1 + 1, tabla[iOld2 + 2][jOld2 - 2].y1 + 1);
                                }else if(miscare2 == "stanga diagonala sus") {
                                    move(tabla[iOld2 - 2][jOld2 - 2].x1 + 1, tabla[iOld2 - 2][jOld2 - 2].y1 + 1);
                                }
                            }else if(ok3 == true) {
                                cout<<miscare3<<" "<<"\n";
                                if(miscare3 == "dreapta") {
                                    move(tabla[iOld2][jOld2 + 2].x1 + 1, tabla[iOld2][jOld2 + 2].y1 + 1);
                                }else if(miscare3 == "dreapta peste pion") {
                                    move(tabla[iOld2][jOld2 + 4].x1 + 1, tabla[iOld2][jOld2 + 4].y1 + 1);
                                }else if(miscare3 == "dreapta diagonala jos") {
                                    move(tabla[iOld2 + 2][jOld2 + 2].x1 + 1, tabla[iOld2 + 2][jOld2 + 2].y1 + 1);
                                }else if(miscare3 == "dreapta diagonala sus") {
                                    move(tabla[iOld2 - 2][jOld2 + 2].x1 + 1, tabla[iOld2 - 2][jOld2 + 2].y1 + 1);
                                }
                            }
                        }

                }

            }

        turn=3-turn;
        }

        if(ok == true) {
            iOld1 = 16, jOld1 = 8, iOld2 = 0, jOld2 = 8,turn=1,type,nrGarduri1=10,nrGarduri2=10;
            fisier();
            closegraph();
            menu();
        }
}

int main(){
    menu();
    getch();
    closegraph();
    return 0;
}
