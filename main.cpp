// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

const int screen_size = 80;

class Player {

private:
	int pos;dddddd
	int hp;
	int mp;
	char face[20];

public:
	Player() {}
	Player(int pos, int hp, int mp, const char* face)
		: pos(pos), hp(hp), mp(mp)   //멤버 초기화 리스트 먼저 this는 그후 만들면서 한다. 메모리 공간 만들면서 바로 한다. 배열은 멤버초기화리스트 에서 불가능
	{
		strcpy(this->face, face);
	}

	~Player()
	{
	}

	void setPostion(int pos)   // 클래스 개발자가 제한을 할수 있게 만든다.(함수 사용 이유)
	{
		if (pos > screen_size) return;
		this->pos = pos;
	}

	int getPosition() // getter 함수
	{
		return pos;
	}

	void draw(char* screen)
	{
		strncpy(&screen[pos], this->face, strlen(this->face));
	}
};

class Enemy {
private:
	int pos;

public:
	

	Enemy()
	{
	}
	~Enemy()
	{
	}
};

class Bullet {
private:
	int pos;
public:
	

	Bullet()
	{
	}
	~Bullet()
	{

	}
};

int main()
{
	
	char screen[screen_size + 1];
	Player player(30,10,10,"(^__^)");
	Enemy enemy;
	Bullet bullet;

	player.setPostion(20);

	while (true)
	{
		for (int i = 0; i < screen_size; i++) screen[i] = ' ';
		screen[screen_size] = '\0';

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.getPosition = (player.getPosition - 1) % screen_size;
				break;
			case 'd':
				player.getPosition = (player.getPosition + 1) % screen_size;
				break;
			case ' ':
				bullet.pos = player.getPosition;
				break;
			}
		}
		player.draw(screen);
		enemy.draw(screen);
		if (bullet.pos != -1)
			bullet.draw(screen);

		// update
		enemy.pos = (enemy.pos + rand() % 3 - 1) % screen_size;
		if (bullet.pos != -1) {
			if (bullet.pos < enemy.pos) {
				bullet.pos = (bullet.pos + 1) % screen_size;
			}
			else if (bullet.pos > enemy.pos) {
				bullet.pos = (bullet.pos - 1) % screen_size;
			}
			else {
				bullet.pos = -1;
			}
		}
		
		printf("%s\r", screen);
		Sleep(66);
	}


	return 0;
}