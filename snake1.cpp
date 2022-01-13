#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <winbgim.h>
using namespace std;

// khoi tao danh sach toa do cua x va y
int td_x[100] = {0}, td_y[100] = {0};
// khoi tao do dai cua ran la 4
int do_dai = 4;
//------------------------------------
void game(int toc_do, int tang_toc);
void gotoxy( int column, int line );
void vetuong();
void taoran();
void veran();
void dichuyen(int x, int y);
bool gameover();
void xu_ly(int x, int y, int &score, int &toc_do, int tang_toc);
void tao_thuc_an(int x, int y);
void an_thuc_an(int &x, int &y);
bool kt_qua(int x, int y);
void showHighScore();
void checkHighScore(int score);
void getHighScore();
void ktratemdiem();
bool ktrateprong();
void showText(int x, int y, char *str){
	outtextxy(x,y,str);
	delay(200);
}

//chương trình chính
int main(){
	int chon;
// in ra màng hình đầu tiên các option
    gotoxy(50,10);
	cout << "1. Mode";
	gotoxy(50,11);
	cout << "2. High score";
	gotoxy(50,12);
	cout << "3. About" << endl;
// nhập vào số và ép đúng số mới nhận
	do{
		gotoxy(50,13);
		cout << "Moi nhap yeu cau theo so: ";
		cin >> chon;
	}while (chon >3 or chon < 0);
// nếu chọn Mode
	if (chon == 1){
		// làm sạch màng hình
		system("cls");
		gotoxy(50,10);
		cout << "1. Tang toc";
		gotoxy(50,11);
		cout << "2. Binh thuong";
		// lựa chọn giữa 2 mode
		do{
			gotoxy(50,13);
			cout << "Moi nhap yeu cau theo so: ";
			cin >> chon;
		}while (chon >2 or chon < 0);
		if (chon == 1){
			// làm sạch màng hình
			system("cls");
			// các level
			gotoxy(50,10);
			cout << "1. Easy";
			gotoxy(50,11);
			cout << "2. Normal";
			gotoxy(50,12);
			cout << "3. Hard" << endl;
			do{
				gotoxy(50,13);
				cout << "Moi nhap yeu cau theo so: ";
				cin >> chon;
			}while (chon >3 or chon < 0);
			// tốc độ của các level
			if (chon == 1){
				game(300,4);
			} else if (chon == 2){
				game(200,4);
			} else{
				game(100,4);
			}
		}else if (chon == 2){
			system("cls");
			gotoxy(50,10);
			cout << "1. Easy";
			gotoxy(50,11);
			cout << "2. Normal";
			gotoxy(50,12);
			cout << "3. Hard" << endl;
			do{
				gotoxy(50,13);
				cout << "Moi nhap yeu cau theo so: ";
				cin >> chon;
			}while (chon >3 or chon < 0);
			if (chon == 1){
				game(300,0);
			} else if (chon == 2){
				game(200,0);
			} else{
				game(100,0);
			}
		}
	}// nếu chọn coi high score
	else if(chon == 2){
		//high score
	}
	//nếu chọn about
	else{
		// giúp cout ra UNICODE
		_setmode(_fileno(stdout), 0x00020000);
		_setmode(_fileno(stdout), 0x00040000);
		system("cls");
		// cout ra phần about
		wcout << "\t\t\t\t" << L"GIỚI THIỆU" << endl;
		wcout << "\t" << L"Chào mừng thầy và các bạn trải nghiệm game rắn săn mồi của team POWER RANGER"<< endl;
		wcout << "\t" << L"Giới thiệu thành viên:"<< endl;
		wcout << L"\t\t\t+ Ngô Quốc Huy" << endl << L"\t\t\t+ Lê Nhật Bình" << endl << L"\t\t\t+ Nguyễn Phú Kiệt" << endl;
		wcout << L"\t\t\t+ Nguyễn Phan Phúc Hiển" << endl << L"\t\t\t+ Lê Tú" << endl;
		wcout << L"\t\t\t\tHƯỚNG DẪN" << endl;
		wcout << L"\tDùng phím mũi tên để di chuyển rắn ăn mồi nhiều nhất có thể nhưng không để\n\tchạm thân và tường" << endl;
		wcout << L"\t\t\t\tCÁC CHỨC NĂNG";
		wcout << L"\nCác chức năng sẽ bao gồm 2 chế độ: rắn sẽ tăng tốc khi ăn hoặc là không." << endl;
		wcout << L"\tHigh score sẽ được lưu vào file txt để có thể xuất ra xem";
	}
	// dừng màn hình cho đến khi nhập 1 kí tự
	_getch();
}

// hàm chạy game
void game(int toc_do, int tang_toc){
    int score = 0;
    system("cls");
    //tạo khung
    vetuong();
    taoran();
    veran();

    int x = td_x[0];
    int y = td_y[0];
//0: đi xuống
//1: đi lên
//2: đi qua phải
//3: đi qua trái
    int huong = 2;
// tạo thức ăn ban đầu
    int x_ta = 40;
    int y_ta = 16;
    tao_thuc_an(x_ta,y_ta);
// chạy game
	while (true){
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && huong != 0)
				{
					huong = 1;
				}
				else if (c == 80 && huong != 1)
				{
					huong = 0;
				}
				else if (c == 75 && huong != 2)
				{
					huong = 3;
				}
				else if (c == 77 && huong != 3)
				{
					huong = 2;
				}
			}
		}
		//------ di chuyển ---
		if (huong == 0)
		{
			y++;
		}
		else if (huong == 1)
		{
			y--;
		}
		else if (huong == 2)
		{
			x++;
		}
		else if (huong ==3)
		{
			x--;
		}
		gotoxy(td_x[do_dai-1], td_y[do_dai-1]);
		cout << " ";
		//di chuyển rắn
		dichuyen(x,y);
		veran();
		//tốc độ
		Sleep(toc_do);
		xu_ly(x_ta,y_ta,score,toc_do,tang_toc);
// kiểm tra rắn có ăn thức ăn chưa
	an_thuc_an(x_ta,y_ta);
		if (gameover())
		{
		//In ra chữ game over
		gotoxy(50,14);
		cout<<"GAME OVER";
		break;
		}
	}
}


// hàm chỉ đến tọa độ x,y
void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
    );
  }
// làm vẽ tường
void vetuong()
{
    for (int i = 10; i < 105; i++){
        gotoxy(i,1);
        cout << "+";
        gotoxy(i,26);
        cout << "+";
    }
    for (int i = 1; i < 26; i++){
        gotoxy(10,i);
        cout << "+";
        gotoxy(104,i);
        cout << "+";
    }
}
// hàm tạo rắn
void taoran(){
    int x_dau = 50;
    int y_dau = 10;
    for (int i = 0; i < do_dai; i++){
        td_x[i] = x_dau--;
        td_y[i] = y_dau;
    }
}
// hàm vẽ rắn
void veran(){
    for (int i = 0; i < do_dai; i++){
        gotoxy(td_x[i],td_y[i]);
        if (i == 0){
            cout << "0";
        }else {
            cout << "o";
        }
    }
}
//hàm giúp rắn di chuyển
void dichuyen(int x, int y)
{
	//them x,y vao dau toa do x va y
	for (int i = do_dai -1;i > 0;i--)
	{
		td_x[i] = td_x[i-1];
		td_y[i] = td_y[i-1];
	}
	td_x[0] = x;
	td_y[0] = y;
}
//Hàm xác định rắn đã cắn vào mình hay chạm tường chưa
bool gameover()
{
for (int i=1;i<do_dai;i++)
    if (td_x[i]==td_x[0]&td_y[i]==td_y[0])
    return true;
if (td_x[0]==10||td_x[0]==105||td_y[0]==1||td_y[0]==26)
    return true;
return false;
}
// Tạo ra thức ăn trên bản đồ
void tao_thuc_an(int x, int y)
{
    gotoxy(x,y);
    cout << "a";
}
// kiểm tra rắn có ăn thức ăn chưa
void an_thuc_an( int &x, int &y)
{
    if (td_x[0] == x && td_y[0] == y)
    {
        do_dai +=1; // nếu ăn rồi thì độ dài của rắn cộng 1
        // random một vị trí mới cho thức ăn
        do{
            x = rand() % (104 - 11 + 1) + 11;
            y = rand() % (25 - 2 + 1 ) + 2;
        } while(kt_qua(x,y));
        // tạo thức ăn ở vị trí mới
        tao_thuc_an(x,y);
    }
}
// kiểm tra quả random có bị trùng thân rắn không
bool kt_qua(int x, int y)
{
    for (int i = 0; i < do_dai; ++i)
    {
        if (x == td_x[i] && y == td_y[i])
        {
            return true;
        }
    }
    return false;
}
// xử lý điểm, tốc độ rắn
void xu_ly(int x, int y, int &score, int &toc_do, int tang_toc){
    if (td_x[0] == x and td_y[0] == y){
        gotoxy(2,28);
		score += 5;
		cout << "diem hien tai la: " << score;
		toc_do -= tang_toc;
	}
}  
struct HighScore{
	int score;
	char name[30];
};
  HighScore highscore[5];
char* score_str= new char[20];
void ktratepdiem(){
 if (ktrateprong()){
 	for ( int i=0;i<5;i++){
	 
 	strcpy(highscore[i].name,"PLAYER");
 	highscore[i].score=0;
 	
 }getHighScore();
}

else { char arr[20];
 int count=0;
 FILE *f;
 f=fopen("highscore.txt","r");
 for (int i=0;i<5;){
 	while (!feof(f)){
 		count++;
 		fscanf(f,"%s",arr);
 		if ( count%2==1){
 			strcpy(highscore[i].name,arr);
 			
		 }else {
		 	highscore[i].score=atoi(arr);
		 	i++;
		 	
		 }
	 }
 }
}
}
bool ktrateprong(){
	FILE *fp;
	long size;
	fp=fopen("highscore.txt","r");
	if (fp){
		fseek(fp,0,SEEK_END);
		size=ftell(fp);
		fclose(fp);
		
	}return ( size==0);
	
}
void showHighScore(){
	FILE *f;
	f=fopen("highscore.txt","r");
	char ch[20];
	settextstyle(1,0,5);
	outtextxy(150,50,"HIGH SCORE");
	settextstyle(1,0,4);
	int y=150,count=0;
	while(!feof(f)){
		if(count==10) break;
		count++;
		fscanf(f,"%s",ch);
		if (count%2==1){
			outtextxy(180,y,ch);
			y+=50;
			
		}else{
			outtextxy(500,y-50,ch);
			
		}
	} fclose(f);
}
void getHighScore(){
	FILE *f;
	f=fopen("highscore.txt","w");
	for(int i =0;i<5;i++){
		fputs(highscore[i].name,f);
		fputs(" ",f);
		fprintf(f,"%d",highscore[i].score);
		fputs("\n",f);
		
	} fclose(f);
	
}
void checkHighScore(int _score){
	char _name[20]={""};
	for (int i=0;i<5;i++){
		if(_score>highscore[i].score){
			settextstyle(1,0,3);
			for (int j=0;j<50;j++){
				if (j%2==0){
					if (i==0)
					outtextxy(460,100,"BEST SCORE");
					else 
					outtextxy(460,100,"HIGH SCORE");
					delay(100);
					
				}else{
					if(i==0)
					outtextxy(460,100,"BEST SCORE");
					else
					outtextxy(460,100,"HIGH SCORE");
					delay(100);
					
				}
			}
			settextstyle(1,0,2);
			outtextxy(430,150,"PLAYER:");
			delay(100);
			char ch1;
			int x=0;
			char str[2];
			str[1]=0;
			while( ch1!=13 && x<10){
				do{
					ch1=getch();
				}while(ch1<65 && ch1>90 || ch1<97 && ch1>132);
				x++;
				str[0]=ch1;
				strcat(_name,str);
				outtextxy(540,150,_name);
				
			}
			for (int j=4;j>i;j--){
				strcpy(highscore[j].name,highscore[j-1].name);
				highscore[j].score=highscore[j-1].score;
				
			}
			strcpy(highscore[i].name,_name);
			highscore[i].score=_score;
			break;
		}
	} getHighScore();
	
} 

