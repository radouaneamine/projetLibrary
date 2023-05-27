//
// 
// quelque fonctions pour le design de la console
//

#include <windows.h>
#pragma comment(lib,"Comdlg32.lib")
void color(DWORD d){
	const HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle,d);
	//  9  = FOREGROUND_BLUE | FOREGROUND_INTENSITY ; // blue
	// 10  = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	// 11  = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	// 12  = red
	// 14  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
	// 15  = white
	// FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	// 240 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
	// 249 = blue bk white 
 }
void getxy(int *x, int *y){
	const HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

      CONSOLE_SCREEN_BUFFER_INFO csbi;
      if(GetConsoleScreenBufferInfo( handle, &csbi ) ){
           *x =(int) csbi.dwCursorPosition.X;
	       *y =(int) csbi.dwCursorPosition.Y;
      }
      else x = y = 0;
}		
void gotoxy(int x, int y)
{
   COORD coord = {x,y};
   const HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

   SetConsoleCursorPosition(handle,coord);
} 
void printHline(int x, int y ,int H){
	  gotoxy(x,y);
	  color(15);
      for ( int i = 0; i < H; i++) printf("\xC4"); 
	  color(15);
}
void printVline(int x, int y ,int V){
     gotoxy(x,y);
	 color(15);
     for ( int i = 0; i < V; i++){
		  gotoxy(x,y+i); 
		 printf("\xB3");
	 }
	 color(15);
}
void title(int x, int y, const char * str){
	COORD coord ={x,y};
	const HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleScreenBufferSize(handle,coord);
    SetConsoleTitle(str);
}	


void design(){
   int x,y;
   getxy(&x,&y);
   y+=2; 	
   gotoxy(0,y);
   color(14);
   for(int i=0;i<80;i++){
	printf("%c",219);
	Sleep(5);
   }
}

void resulta(){
	int x,y,d=30;
	getxy(&x,&y);
	color(15);
	printHline(x+d,y+1 ,20);
	color(14);	
	gotoxy(x+d+4,y+2);
	printf("resultats");
	color(15);	
	printHline(x+d,y+3 ,20);	
	printf("\n");	
}









