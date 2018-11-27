#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h> 

void gotoxy(int PosX,int PosY);//перемещение по консоли
void Field();//Построение поля
void OutputField();//Вывод поля на экран
int Result(int PosX, int PosY); //Определение количества очков за попадание
int menu();//Меню
void TextColor(int color);//Процедура изменения цвета текста
void Game();//Процедура с игрой
void InformationGame();//Вывод информации об игре
void RulesGame();//Вывод правил игры
void Preview(); //Превью при заходе в игру

const int N=27,M=45;//параметры матрицы(поле для тира)
const int Shots=4;//Кол-во выстрелов
char matrix[N][M];

int main() //!!!!!!!!!!!!!!!!!!!Основная программа!!!!!!!!!!!!!!!!!!!!!
{
	system("mode con cols=120 lines=60");
	system("color F0");
	int Button;
	Preview();
	do{
       system("color 0F");
	   Button=menu();
	   if (Button==1)
	   Game();
	   else if (Button==2)
	   InformationGame();
	   else if (Button==3)
	   RulesGame();
    } while(Button!=4);
	printf("Do svidaniya!!!");
	return 0;
}

void Game()//Игра
{
	system("cls");
	Field();
	int x,y;
	int SumPC = 0, SumU=0;
	gotoxy(0,N+4);
	printf("Chtobi strelyat', nazhymite Enter");
	printf("\nVashi balli za vistrely:");
	int i=0;
	while(i<Shots)
	{
	 	do{
	 		x=rand()%M;
 			y=rand()%N;
 			gotoxy(x+25,y);
 			printf("X");
 			Sleep(200);
 			gotoxy(x+25,y);
 			printf("%c",matrix[y][x]);
	 	} while(!kbhit());
	 	
	 	if (getch()==(char)13){
	    	gotoxy(x+25,y);
	        printf("X");
	        gotoxy(0,N+7+i);
	        SumU+=Result(x,y);
	        printf("Za %i-y vistrel vi polushaete %i ochk.",i+1,Result(x,y));
	        i++;
        }
	}
	gotoxy(0,N+7+i);
	printf("Vasha summa balov = %i\n",SumU);
	system("pause");
	system("cls");
	Field();
	gotoxy(5, N + 4);
	printf("!!!Strelyaet PC!!!", i+1);
    int RandomCount;
	for(i = 0; i < Shots; i++)
	{
		RandomCount=rand()%4+5;
		for(int j=0; j<RandomCount;j++){
		x = rand()%M;
		y = rand()%N;
		gotoxy(x + 25, y);
		printf("X");
		Sleep(150);
		gotoxy(x + 25, y);
		printf("%c",matrix[y][x]);
        }
		gotoxy(x + 25, y);
		printf("X");
		gotoxy(0,N+7+i);
		SumPC+=Result(x,y);
	    printf("Za %i-y vistrel PC polushaet %i ochk.",i+1,Result(x,y));
	}
	gotoxy(0,N+7+i);
	printf("Summa balov PC = %i\n", SumPC);
	system("pause");
	system("cls");
	printf("Resul'tat pol'zovatelya: %i\n", SumU);
	printf("Resul'tat PC: %i\n", SumPC);
	gotoxy(20, 27);
	if(SumPC > SumU)
		printf("!!!AHAHHAHAHAH STUPID PEOPLE, WE WILL STILL TAKE OVER THE WORLD AHAHAHA!!!");
	else if (SumU>SumPC)
		printf("!!!Oh, the computer admits defeat, YOU'RE TEARING ME APART USER!!!");
	else{
		gotoxy(40, 27);
		printf("!!!OHH DRAW!!!");
	}
	gotoxy(0, 3);
	system("pause");
}

void InformationGame()//Вывод информации об игре
{
	system("cls");
	printf("!!!!!!!!!!!!!!!!!!!!Informaciya ob igre!!!!!!!!!!!!!!!!!!\n\n");
	printf("Nazvanie igri - dartc\nNapisali kod etoy igti studenti gruppi TMP-41:\nHromov Nikita, Bodyagin Mikhail, Manevskiy Raman");
	printf("\n\nChtobi viyti ot suda, nazhmite Esc...\n");
	while(getch()!=(char)27);
}

void RulesGame()//Вывод правил игры
{
	system("cls");
	printf("!!!!!!!!!!!!!!!!!!!!Pravila igri!!!!!!!!!!!!!!!!!!!!!\n\n");
	printf("Glavnoe pravilo, kak i v luboy drugoy igre - pobedit' protivnika. V dannom sluchae vash protivnik - PC\n");
	printf("Dlya togo, chtobi pobedit', pol'sovatelu neobhodimo nabrat' bol'she ballov za vistreli chem PC\n");
	printf("Chtobi nachat' igrat' v tir, nado zayti v podmenu ""Game"".\n");
	printf("U pol'zovatelya est' %i popitki dlya vistrela.\n",Shots);
	printf("Slozhnost' v tom, chto ""pricel"" budet begat' po vsemu polu i pol'zovatelu neobhodimo nazhat' Enter v nuzhniy moment,\n");
	printf("dlya togo, chtobi proizvesti vistrel.\n");
	printf("Chem blizhe k centru popadaet pol'zovatel', tem bol'she on poluchaet ochkov za vistrel.\n\n");
	printf("Ochki za popadanie:\n");
	printf("%c - 20 ochkov;\n",(char)219);
	printf("%c - 15 ochkov;\n",(char)178);
	printf("%c - 10 ochkov;\n",(char)177);
	printf("%c - 5 ochkov;\n",(char)176);
	printf("Za promah - 0 chkov.\n\n");
	printf("Chtobi viyti ot suda, nazhmite Esc...\n");
	while(getch()!=(char)27);
}
	

void gotoxy(int PosX, int PosY) //перемещение курсора по экрану
{
	COORD position;										
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    position.X=PosX;
    position.Y=PosY;
    SetConsoleCursorPosition(hConsole, position);
}

void Field()
{
	system("cls");
	int i,j;
	for(i=0;i<N;i++)//Построение поля 
	{
		for(j=0;j<M;j++)
		{
			if (i==0&&j==0) matrix[i][j]=(char)218;
			else if (i==0&&j==M-1) matrix[i][j]=(char)191;
			else if(i==N-1&&j==0) matrix[i][j]=(char)192;
			else if(i==N-1&&j==M-1) matrix[i][j]=(char)217;
			else if((i==0&&j>0)||(i==N-1&&j>0)) matrix[i][j]=(char)196;
			else if(i>0&&(j==0||j==M-1)) matrix[i][j]=(char)179; 
			else if(i<=(N+1)/2&&i>=(N-3)/2&&j<=(M+3)/2&&j>=(M-5)/2) matrix[i][j]=(char)219; 
			else if(i<=(N+5)/2&&i>=(N-7)/2&&j<=(M+9)/2&&j>=(M-11)/2) matrix[i][j]=(char)178; 
			else if(i<=(N+11)/2&&i>=(N-13)/2&&j<=(M+19)/2&&j>=(M-21)/2) matrix[i][j]=(char)177; 
			else if(i<=(N+19)/2&&i>=(N-21)/2&&j<=(M+33)/2&&j>=(M-35)/2) matrix[i][j]=(char)176; 
			else matrix[i][j]=' '; 
		}
	}
	OutputField();
}

void OutputField()//вывод поля на экран
{
	int i,j;
	for(i=0;i<N;i++) 
	{
		for(j=0;j<M;j++)
		{
			gotoxy(j+25,i);
			printf("%c",matrix[i][j]);
		}
		printf("\n");
	}
}

int Result(int PosX, int PosY)//Количество очков за попадание
{
	int Shot=0;
	switch(matrix[PosY][PosX])
	{
		case (char)219: Shot=20; break;
		case (char)178: Shot=15; break;
		case (char)177: Shot=10; break;
		case (char)176: Shot=5; break;
	}
	return Shot;
}

int menu()//Перемещение по меню
	{
		int h=1;
		system("cls");
		char a=' ';
		const int n=5;
		system("color F0");
		while(a!=(char)13)
		{
           //gotoxy(0,0);
            //system("color F0");
           if (h==1)TextColor(10);
           printf("To game\n");
		   TextColor(0);
		   if (h==2)TextColor(10);
		   printf("Infa about game\n");
		   TextColor(0);
            if (h==3)TextColor(10);
		   printf("Rules\n");
		   TextColor(0);
		   if (h==4)TextColor(10);
		   printf("Exit\n");
		   TextColor(0); 
		   a=getch();
		   switch(a){
 			 case 'w':case 'W':
		   	 --h;
			 if (h==0) h=n-1;
			 break;
			 
			 case 's':case 'S': 
			 ++h; 
			 if (h==n) h=1;
			 break;
		   }system("cls");
		   
		}
		return h;
	}
	
void TextColor(int color)//Изменение цвета
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,(WORD) (240|color));
}

void Preview()//Вывод превью на экран
{
	const int Y = 20, X = 80;
	char zastavka[Y][X];
	int i, j;
	for(i = 0; i < Y; i++)
		for(j = 0; j < X; j++)
			zastavka[i][j] = (char)177;
	for(j = 4; j < 16; j++)
	{
		zastavka[Y-16][j] = (char)176;
		zastavka[Y-5][j] = (char)176;
	}
	for(j = 22; j < 31; j++)
	{
		zastavka[Y-16][j] = (char)176;
		zastavka[Y-10][j] = (char)176;
	}
	for(j = 37; j < 46; j++)
	{
		zastavka[Y-16][j] = (char)176;
		zastavka[Y-10][j] = (char)176;
	}
	for(j = 51; j < 62; j++)
		zastavka[Y-16][j] = (char)176;
	for(j = 67; j < 77; j++)
	{
		zastavka[Y-16][j] = (char)176;
		zastavka[Y-5][j] = (char)176;
	}
	for(i = 4; i < 16; i++)
	{
		zastavka[i][5] = (char)176;
		zastavka[i][16] = (char)176;
		zastavka[i][21] = (char)176;
		zastavka[i][31] = (char)176;
		zastavka[i][36] = (char)176;
		zastavka[i][56] = (char)176;
		zastavka[i][66] = (char)176;
		zastavka[Y-15][76] = (char)176;
		zastavka[Y-6][76] = (char)176;
	}
	for(i = 4; i < 11; i++)
		zastavka[i][46] = (char)176;
	system("cls");
	for(i = 0; i < Y; i++)
		for(j = 0; j < X; j++)
		{
			gotoxy(j + 20, i + 13);
			printf("%c", zastavka[i][j]);
			if (!kbhit())Sleep(1);
			else Sleep(0);
		}
	getch();	
	getch();
}
