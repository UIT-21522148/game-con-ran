#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;

// khoi tao danh sach toa do cua x va y
int td_x[100] = {0}, td_y[100] = {0};
// khoi tao do dai cua ran la 4
int do_dai = 4;
//------------------------------------
void game();
void gotoxy( int column, int line );
void vetuong();
void taoran();
void veran();
void dichuyen(int x, int y);
//chương trình chính
int main(){
    game();
}

// hàm chạy game
void game(){
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
		Sleep(100);
	};
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

