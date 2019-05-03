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

//�߻�ȭ ��Ű�°�(���) ����� �Ӽ� : ���� �ϱ����Ͽ� ���

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) {}
	~Screen() { delete[] screen; }

	void draw(int pos, const char* face) 
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render() 
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject{
	int pos;
	char face[20];
	Screen* screen;

public:
	GameObject(int pos, const char* face, Screen* screen)  //�⺻ �����ڴ� ����Ҽ��� ������ �Ҽ��� ����.
		: pos(pos), screen(screen)
	{
		strcpy(this->face, face);
	}

	int getPosition()
	{
		return pos;
	}

	void setPosition(int pos)
	{
		this->pos = pos;
	}

	void draw()
	{
		screen->draw(pos, face);
	}
};

class Player : public GameObject {

public:
	Player(int pos, const char* face, Screen* screen)
		:GameObject(pos,face,screen)   //�θ� ������ ���� ȣ�� 1.new 2.����ʱ�ȭ 3.���������Լ� ����
	{
	}

	//int getPosition()  // �̷��� �ϴ� ������ �ڵ� ���°ſ� ���� �ٸ��� �Ҽ��մ�.
	//{
	//	return GameObject::getPosition();
	//}

	void moveLeft()
	{
		setPosition(getPosition() - 1); //�ߺ���� �����ʴ� �̻� �θ� Ŭ���� �Լ� �ٷ� ��� ���� �Ҽ� ����� ��
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void update()
	{

	}

};

class Enemy : public GameObject{

public:
	Enemy(int pos, const char* face, Screen* screen) : GameObject(pos,face,screen)
	{
	}

	void moveRandom()
	{
		setPosition(getPosition() + rand() % 3 -1);
	}

	void update()
	{
		moveRandom();
	}
};

class Bullet : public GameObject{
	
	bool isFiring;

public:
	Bullet(int pos, const char* face, Screen* screen) : GameObject(pos,face,screen), isFiring(false)
	{
	}

	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void draw()
	{
		if (isFiring == false) return;
		GameObject::draw();
	}

	void fire(int player_pos)
	{
		isFiring = true;
		setPosition(player_pos);
	}

	void update(int enemy_pos)
	{
		if (isFiring == false) return;
		int pos = getPosition();
		if (pos < enemy_pos) {
			pos = pos + 1;
		}
		else if (pos > enemy_pos) {
			pos = pos - 1;
		}
		else {
			isFiring = false;
		}
		setPosition(pos);
	}
};

int main()
{
	Screen screen{ 80 };
	Player player{ 30, "(^_^)", &screen };
	Enemy enemy{ 60, "(*--*)", &screen };
	Bullet bullet( -1, "+", &screen);

	while (true)
	{
		screen.clear();

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
				bullet.fire(player.getPosition());
				break;
			}
		}
		player.draw();
		enemy.draw();
		bullet.draw();

		player.update();
		enemy.update();
		bullet.update(enemy.getPosition());
		
		screen.render();
		Sleep(66);
	}

	return 0;
}