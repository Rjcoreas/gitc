 #include<stdio.h>
 #include<windows.h>
 #include<conio.h>
 #include<stdlib.h>
 #include<list>

 using namespace std;
    // defining the vay
 #define UP 72
 #define LEFT 75
 #define RIGHT 77
 #define DOWN 80

  // function gotoxy to set the position for the objects in the console


 void gotoxy(int x, int y){
 HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);

 }

 // funtion hidecursor is for hide the cursor and change the size of the cursor also

 void HideCursor(){
 HANDLE hCon;
 hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 CONSOLE_CURSOR_INFO cci;
 cci.dwSize = 50;
 cci.bVisible = FALSE;

 SetConsoleCursorInfo(hCon,&cci);

 }
// draw horizontal line
 void Square(){
    for(int i = 2; i < 78; i++){
        gotoxy(i,4);
        printf("%c", 205);
        gotoxy(i,33);
        printf("%c", 205);
    }
// draw vertical line
     for(int i = 5; i < 33; i++){
        gotoxy(2,i);
        printf("%c", 186);
        gotoxy(77,i);
        printf("%c", 186);
    }
        // draw the corners
        gotoxy(2,4); printf("%c", 201);
        gotoxy(2,33); printf("%c", 200);
        gotoxy(77,4); printf("%c", 187);
        gotoxy(77,33); printf("%c", 188);
 }
        // Bar is to draw he energy bar
 void Bar(){

        gotoxy(71,1);
        printf("%c%c%c%c", 205, 205, 205, 205);
        gotoxy(71,3);
        printf("%c%c%c%c", 205, 205, 205, 205);
        gotoxy(70,2); printf("%c", 186);
        gotoxy(75,2); printf("%c", 186);
        gotoxy(70,1); printf("%c", 201);
        gotoxy(75,1); printf("%c", 187);
        gotoxy(70,3); printf("%c", 200);
        gotoxy(75,3); printf("%c", 188);
 } //main class kraft with the methods and variables for position and objects.
 class KRAFT{
    int x,y;
    int energy;
    int life;
 public:
     KRAFT(int _x, int _y, int _energy, int _life):x(_x), y(_y), energy(_energy), life(_life){}
     int X(){ return x;}
     int Y(){ return y;}
     int LIF() {return life;}
     void ENER() { energy--;}
     void draw();
     void clean();
     void moving();
     void draw_energy();
     void explode();

 };

// KRAFT::draw to make

 void KRAFT::draw(){
        gotoxy(x,y);   printf("  %c", 193);
        gotoxy(x,y+1); printf(" %c%c%c", 91,88,93);
        gotoxy(x,y+2); printf("%c%c %c%c", 40,174,175,41);
 }

 //erase the spacecraft from the previous position
void KRAFT::clean(){
        gotoxy(x,y);   printf("     ");
        gotoxy(x,y+1); printf("     ");
        gotoxy(x,y+2); printf("     ");
}
// move the spacecraft using the arrows in the keyboard
void KRAFT::moving(){
     if(kbhit()){
             char tecla = getch();
             clean();
             if(tecla== LEFT && x>3)x--;
             if(tecla== RIGHT && x+6 <78)x++;
             if(tecla== UP && y>5)y--;
             if(tecla== DOWN && y+3 < 33)y++;

             draw();
             draw_energy();
        }
}
// function to draw energy
void KRAFT::draw_energy(){
        gotoxy(50,2); printf("life %d", life);
        gotoxy(62,2); printf("Energy");
        gotoxy(71,2); printf("    ");
        for (int i = 0; i < energy; i++){

           gotoxy(71+i,2); printf("%c",219);
        }
}
// when energy ran out the spacecraft explode
void KRAFT::explode(){
    if(energy==0){
        clean();
        gotoxy(x,y);  printf("  ** ");
        gotoxy(x,y);  printf(" ****");
        gotoxy(x,y);  printf("  ** ");
        Sleep(200);

        clean();
        gotoxy(x,y);  printf(" * **");
        gotoxy(x,y);  printf(" *##*");
        gotoxy(x,y);  printf(" * **");
        Sleep(200);

        clean();

        life--;
        energy = 4;
        draw_energy();
        draw();
    }

}

// class for asteroids

class AST{
     int x,y;
public:
    AST(int _x, int _y):x(_x),y(_y){}
    void draw();
    void moving();
    void crash(class KRAFT &N);
    int X() { return x;}
    int Y() { return y;}

};

//function to draw the asteroids
    void AST::draw(){

    gotoxy(x,y); printf("%c", 184);

    }
// move each asteroid
    void AST::moving(){
        gotoxy(x,y); printf(" ");
        y++;
        if(y > 32){
            x = rand()%71 +5;
            y = 5;
        }

        draw();

    }
// function to decrease energy bar when the space kraft crash with the asteroids
    void AST::crash(class KRAFT &N){
        if( x>= N.X() && x < N.X()+6 && y >= N.Y() &&
    y <= N.Y()+2) {

        N.ENER();
        N.draw();
        N.draw_energy();
        x = rand()%71 +5;
        y = 5;
    }

    }
 // class for the shoots
    class SHOOT{
        int x,y;
    public:
        SHOOT(int _x, int _y): x(_x), y(_y){}
        int X(){ return x;}
        int Y(){ return y;}
        void moving();
        bool sout();
    };
// function to move the shoots
 void SHOOT::moving(){
    gotoxy(x,y); printf(" ");
    y--;
    gotoxy(x,y); printf("*");
 }
// avoid the shoots leave the play ring or square
 bool SHOOT::sout(){
    if(y == 5) return true;
    return false;
 }

 int main(){
// function to hide the cursor in the console
    HideCursor();
// draw the play ring
    Square();
// draw the life bar rectangle
    Bar();
// Create the objects
    KRAFT N(37,30,4,3);
// draw the spacecraft in the position 37,30
    N.draw();
// draw the energy bar
    N.draw_energy();

    list<AST*> A;
    list<AST*>::iterator itA;
    for(int i=0; i<5; i++){
            A.push_back(new AST(rand()%75 +3, rand()%5+5));

    }

    list<SHOOT*> S;
    list<SHOOT*>::iterator it;
    bool game_over = false;
    int score = 0;
    while(!game_over){

        gotoxy(4,2); printf(" Score %d",score);
        if(kbhit()){

            char tecla = getch();
            if(tecla=='s')
                S.push_back(new SHOOT(N.X()+2, N.Y()-1));
        }

        for(it = S.begin(); it != S.end(); it++)
        {
             (*it)->moving();
             if((*it)->sout()){
                    gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = S.erase(it);
             }
        }

        for(itA = A.begin(); itA != A.end(); itA++){
            (*itA)->moving();
            (*itA)->crash(N);
        }

        for(itA= A.begin(); itA != A.end(); itA++){
            for(it = S.begin(); it != S.end(); it++){
                if((*itA)->X() == (*it)->X() && ( (*itA)->Y()+1==(*it)->Y() || (*itA)->Y()==(*it)->Y())){

                    gotoxy((*it)->X(), (*it)->Y()); printf(" ");
                    delete(*it);
                    it = S.erase(it);

                    A.push_back(new AST(rand()%74+3,5));
                    gotoxy((*itA)->X(), (*itA)->Y()); printf(" ");
                    delete(*itA);
                    itA = A.erase(itA);

                    score+=5;
                }
            }

        }
        if (N.LIF()== 0) game_over = true;
        N.explode();
        N.moving();
        Sleep(40);

    }

    return 0;

  }
