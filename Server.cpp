#include <iostream>
#include <winsock2.h>
#include<time.h>
using namespace std;

#pragma comment(lib,"WS2_32.LIB")

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "������ ���� : www.Jangho.com " << endl;
	}


	WSADATA wsaData;
	BYTE   nMajor = 2, nMinor = 2;
	WORD   wVersionRequested = MAKEWORD(nMinor, nMajor);
	int      nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet == SOCKET_ERROR)
	{
		cout << "������ ������ �ʱ�ȭ �� �� �����ϴ�." << endl;
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != nMajor ||
		HIBYTE(wsaData.wVersion) != nMinor)
	{
		cout << "������ ���� " << nMajor << "." << nMinor << " �� ����� �� �����ϴ�." << endl;
		WSACleanup();
		return -1;
	}


	struct hostent *host;
	host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		cout << "���� : 'gethostbyname'" << endl;
		WSACleanup();
		return 0;
	}

	cout << "ȣ��Ʈ �̸� : \t" << host->h_name << endl;

	int i = 0;
	while (host->h_aliases[i] != NULL)
	{
		cout << "aliases name : \t\t" << host->h_aliases[i] << endl;
		i++;
	}


	i = 0;
	while (host->h_addr_list[i] != NULL)
	{
		struct in_addr inaddr; /* IP �ּҸ� ������ ����ü */
		inaddr.s_addr = *((u_long *)(host->h_addr_list[i]));
		cout << hex << "ȣ��Ʈ�� IP �ּ� ��(16����) : \t " << inet_addr(inet_ntoa(inaddr)) << endl;
		cout << "ȣ��Ʈ�� IP �ּ� ��(10����) : \t" << inet_ntoa(inaddr) << endl << endl;
		i++;
	}

	WSACleanup();
	int year_support = 1900;
	time_t now = time(NULL); //�ý��� �ð��� ����
	struct tm *lt = localtime(&now); //tm ����ü�� ��ȯ

	cout << dec << lt->tm_year + year_support << "�� " << lt->tm_mon + 1 << "�� " << lt->tm_mday  << "�� " <<
		lt->tm_hour << "�� " << lt->tm_min << "�� " << lt->tm_sec << "�� " << endl;
	system("pause");
	return 0;

}