#include"̹����.h"
#include<iostream>
using namespace std;


tanklist t;
int power = 0,live=0,speed=0;
direction dir = u;
point ptank;

void pause() {//��ͣ
	while (1)
	{
		Sleep(300);
		if (GetAsyncKeyState(VK_SPACE))
		{
			break;
		}

	}
}
//��ͣ

void endgame() {//������Ϸ
	system("cls");
	Sleep(300);
	cout << "����˱ȣ��ⶼ����";
	cin.sync();
	char c;
	while (1)
	{
		cin.get(c);
		Sleep(1000);
		if (c == 'y')
		{
			break;
		}
	}
	exit(0);
}
//������Ϸ

void esc() {//�����˳���Ϸ
	while (1)
	{
		Sleep(300);
		cin.sync();
		cout << "Ҫ�˳���Ϸ��";
		cout << "��Ҫ�˳��밴y" ;
		if (cin.get() == 'y')
		{
			endgame();
		}
		else
		{
			break;
		}

	}
}
//�����˳���Ϸ

void win() {//��ʤ
	system("cls");
	cin.sync();
	Sleep(300);
	cout << "ţ��";
	char c;
	while (1)
	{	
		cin.get(c);
		Sleep(1000);
		if (c == 'y')
		{
			break;
		}
	}
	exit(0);
}
//��ʤ

void print_something() {
	point p;
	p.x = 40;
	p.y = 2;
	t.get_tank(ptank,live,power,speed,dir);
	gotoxy(p);
	cout<< "��ǰ����Ϊ��"<<fraction;
	p.y += 2;
	gotoxy(p);
	cout<<"��ǰ����Ϊ��"<<live;
	p.y += 2;
	gotoxy(p);
	cout << "��ǰ����Ϊ��" << power;
	p.y += 2;
	gotoxy(p);
	cout << "��ǰ�ٶ�Ϊ��" << speed;
}

void initgame() {//��ʼ����Ϸ�������µ���
	system("mode con cols=100 lines=40");
	point p1, p2, p3;
	p1.x = 1;
	p1.y = 1;
	p2.x = 20;
	p2.y = 1;
	p3.x = 1;
	p3.y = 10;
	t.tank_add(p1);
	t.tank_add(p2);
	t.tank_add(p3);
	cout << "��ʼ��Ϸ�밴y" << endl;
	while (true)
	{
		if (cin.get() == 'y')
		{
			break;
		}
		cin.get();
	}
	cin.sync();
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//�ڶ���ֵ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	system("cls");
}
//��ʼ����Ϸ��������������



void startgame() {
	initgame();
	int size;
	direction dir;
	int time0 = 0;
	while (1)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			t.player_tank_move(u);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			t.player_tank_move(d);
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			t.player_tank_move(l);
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			t.player_tank_move(r);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			t.player_attack();
		}
		else if (GetAsyncKeyState(VK_SPACE))
		{
			pause();
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			esc();
		}
		Sleep(175);
		t.move_all();
		t.kill();
		t.print_all();
		t.get_size(size);
		print_something();
		if (size < 1)
		{
			win();
		}
	}
}

int main() {
	srand((unsigned)time(NULL));
	ran = rand();
	startgame();
	endgame();
	return 0;
}