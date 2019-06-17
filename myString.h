#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
class myString
{
	int size;
	char* data;
public:
	myString(int size);
	myString(const char* inp);
	myString(const myString& other);
	~myString();

	myString& operator=(const myString& other);
	myString operator+(const myString& other);

	friend ostream& operator<<(ostream& os, const myString& mine);
};

