// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Screen.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Integer.h"
#include "GameObjects.h"
#include"myString.h"

using namespace std;

int main()
{

	myString hello = "hello";
	myString world = "world";
	myString helloworld = hello + world;
	world = "new world";
	
	cout << helloworld << endl;
	cout << hello + world << endl;
#if 0
	Integer i = 10;
	Integer j = 20;
	Integer k( 0 );
	Integer m(-1);
	Integer l(-10);

	l = k = i + j + m;
	//l.operator=(k.operator=(  operator+(operator+(i, j), m) ));

	l.print(); // 29

	Integer::printStat();
	GameObjects& objects = GameObjects::getInstance();


	objects.add(new Player{ 30, "(^_^)" });
	objects.add(new Enemy{ 60, "(*--*)" });

	Screen& screen = Screen::getInstance();
	while (true)
	{
		screen.clear();

		objects.update();

		screen.render();
		Sleep(66);
	}
	return 0;
#endif
}