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

//추상화 시키는것(상속) 공통된 속성 : 재사용 하기위하여 사용

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
	GameObject(int pos, const char* face, Screen* screen)  //기본 생성자는 사용할수는 있지만 할수가 없다.
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
		:GameObject(pos,face,screen)   //부모 생성자 직접 호출 1.new 2.멤버초기화 3.템포러리함수 무시
	{
	}

	//int getPosition()  // 이렇게 하는 이유는 코드 적는거에 따라 다르게 할수잇다.
	//{
	//	return GameObject::getPosition();
	//}

	void moveLeft()
	{
		setPosition(getPosition() - 1); //중복사용 하지않는 이상 부모 클래스 함수 바로 사용 가능 소속 안적어도 됨
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