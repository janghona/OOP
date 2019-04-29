// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
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
		: pos(pos), hp(hp), mp(mp)   //��� �ʱ�ȭ ����Ʈ ���� this�� ���� ����鼭 �Ѵ�. �޸� ���� ����鼭 �ٷ� �Ѵ�. �迭�� ����ʱ�ȭ����Ʈ ���� �Ұ���
	{
		strcpy(this->face, face);
	}
	~Player()
	{
	}

	void setPostion(int pos)   // Ŭ���� �����ڰ� ������ �Ҽ� �ְ� �����.(�Լ� ��� ����)
	{
		if (pos > screen->size) return;
		this->pos = pos;
	}

	int getPosition() // getter �Լ�
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