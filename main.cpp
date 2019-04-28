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
	int pos;dddddd
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