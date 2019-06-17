#include "myString.h"
#define _CRT_SECURE_NO_WARNINGS
myString::myString(int size) : size(size),data(new char[size])
{
	memset(data,'\0', size);
}
myString::myString(const char* inp)
	: size(strlen(inp)+1),data(new char[strlen(inp)+1])
{
	strcpy(this->data, inp);
}
myString::myString(const myString& other)
	:size(other.size),data(new char[other.size])
{
	strcpy(this->data, other.data);
}
myString::~myString()
{
	if (data)
	{
		delete[] data;
	}
	data = nullptr;
	size = 0;
}


myString& myString::operator=(const myString& other)
{
	if (data)
	{
		delete[] data;
	}
	data = new char[other.size];
	size = other.size;
	strcpy(data, other.data);

	return *this;
}

myString myString::operator+(const myString& other)
{
	myString temporary(this->size + other.size - 1);
	strcpy(temporary.data, this->data);
	strcat(temporary.data, other.data);
	return temporary;
}

ostream& operator<<(ostream& os, const myString& mine)
{
	os << mine.data;
	return os;
}


