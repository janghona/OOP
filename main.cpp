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


class Screen {
private:
	int size;
	char* screen;
public:
	Screen()
	{}
	Screen()
		:size(80),screen(new char[size+1])
	{
	}
	~Screen()
	{
		delete[] screen;
	}
	void draw()
	{
		memset(&screen, ' ', size);
		screen[size] = '\0';
	}
	int getSize()
		{
		return size;
		}
};
class Player {
private:
	int pos;
	int hp;
	int mp;
	char face[20];
public:
	Player() 
	{
	}
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
		if (pos > screen->size) return;
		this->pos = pos;
	}

	int getPosition() // getter 함수
	{
		return pos;
	}

	void draw(Screen* screen)
	{
		if (pos < 0 || pos >= screen->getSize()) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void moveLeft()
	{
		pos = pos - 1;
	}

	void moveRight()
	{
		pos = pos + 1;
	}
};

class Enemy {
private:
	int pos;
	int hp;
	char face[20];
public:
	Enemy()
	{
	}
	Enemy(int pos, int hp, const char* face)
		:pos(pos), hp(hp)
	{
		strcpy(this->face, face);
	}
	~Enemy()
	{
	}
	void setPosition(int pos)
	{
		if (pos > screen_size) return;
		this->pos = pos;
	}

	int getPosition()
	{
		return pos;
	}
	void draw(char* screen)
	{
		if (pos < 0 || pos >= screen_size) return;
		strncpy(&screen[pos], face, strlen(face));
	}
	void moveRandom()
	{
		pos = pos + rand() % 3 - 1;
	}
};

class Bullet {
private:
	int pos;
	char face[20];
	bool isFiring;
public:
	Bullet()
	{
	}
	Bullet(const char* face)
		:pos(-1),isFiring(false)
	{
		strcpy(this->face, face);
	}
	~Bullet()
	{
	}
	void setPostion(int pos,Screen* screen)
	{
		if (pos > screen->size) return;
		this->pos = pos;
	}

	int getPosition()
	{
		return pos;
	}
	void draw(char* screen)
	{
		if (pos == -1) return;
		if (pos < 0 || pos >= screen_size) return;
		strncpy(&screen[pos], face, strlen(face));
	}
	bool isAlive()
	{
		isFiring = true;
	}
	void moveLeft()
	{
		pos = pos - 1;
	}
	void moveRight()
	{
		pos = pos + 1;
	}
	void setDead()
	{
		pos = -1;
	}
};

int main()
{
	Screen screen;
	Player player(30,10,10,"(^__^)");
	Enemy enemy(60,10,"(*__*)");
	Bullet bullet("+");

	screen.draw();
	while (true)
	{
		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				bullet.setPostion(player.getPosition());
				break;
			}
		}
		player.draw(&screen);
		enemy.draw(&screen);
		bullet.draw(&screen);

		enemy.moveRandom();
		// update
		if (bullet.isAlive()) {
			if (bullet.getPosition < enemy.getPosition) {
				bullet.moveRight();
			}
			else if (bullet.getPosition > enemy.getPosition) {
				bullet.moveLeft();
			}
			else {
				bullet.setDead();
			}
		}
		
		printf("%s\r", screen);
		Sleep(66);
	}


	return 0;
}