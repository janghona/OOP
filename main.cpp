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

const int screen_size = 80;

class Player {

private:
	int pos;
	int hp;
	int mp;
	char face[20];

public:
	Player() {}
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
		if (pos > screen_size) return;
		this->pos = pos;
	}

	int getPosition() // getter �Լ�
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
		strncpy(&screen[pos], this->face, strlen(this->face));
	}
};

class Bullet {
private:
	int pos;
	char face[20];
public:
	Bullet()
	{
	}
	Bullet(int pos, const char* face)
		:pos(pos)
	{
		strcpy(this->face, face);
	}
	~Bullet()
	{
	}
	void setPostion(int pos)
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
		strncpy(&screen[pos], this->face, strlen(this->face));
	}

};

int main()
{
	
	char screen[screen_size + 1];
	Player player(30,10,10,"(^__^)");
	Enemy enemy(60,10,"(*__*)");
	Bullet bullet(-1,"+");

	while (true)
	{
		int playerPos = player.getPosition();
		int enemyPos = enemy.getPosition();
		int bulletPos = bullet.getPosition();
		for (int i = 0; i < screen_size; i++) screen[i] = ' ';
		screen[screen_size] = '\0';

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				playerPos = (playerPos - 1) % screen_size;
				break;
			case 'd':
				playerPos = (playerPos + 1) % screen_size;
				break;
			case ' ':
				bulletPos = playerPos;
				break;
			}
		}
		player.draw(screen);
		enemy.draw(screen);
		if (bulletPos != -1)
			bullet.draw(screen);

		// update
		enemyPos = (enemyPos + rand() % 3 - 1) % screen_size;
		if (bulletPos != -1) {
			if (bulletPos < enemyPos) {
				bulletPos = (bulletPos + 1) % screen_size;
			}
			else if (bulletPos > enemyPos) {
				bulletPos = (bulletPos - 1) % screen_size;
			}
			else {
				bulletPos = -1;
			}
		}
		
		printf("%s\r", screen);
		Sleep(66);
	}


	return 0;
}