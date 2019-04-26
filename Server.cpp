#include <iostream>
#include <winsock2.h>
#include<time.h>
using namespace std;

#pragma comment(lib,"WS2_32.LIB")

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "도메인 네임 : www.Jangho.com " << endl;
	}


	WSADATA wsaData;
	BYTE   nMajor = 2, nMinor = 2;
	WORD   wVersionRequested = MAKEWORD(nMinor, nMajor);
	int      nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet == SOCKET_ERROR)
	{
		cout << "윈도우 소켓을 초기화 할 수 없습니다." << endl;
		return -1;
	}

	if (LOBYTE(wsaData.wVersion) != nMajor ||
		HIBYTE(wsaData.wVersion) != nMinor)
	{
		cout << "윈도우 소켓 " << nMajor << "." << nMinor << " 을 사용할 수 없습니다." << endl;
		WSACleanup();
		return -1;
	}


	struct hostent *host;
	host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		cout << "에러 : 'gethostbyname'" << endl;
		WSACleanup();
		return 0;
	}

	cout << "호스트 이름 : \t" << host->h_name << endl;

	int i = 0;
	while (host->h_aliases[i] != NULL)
	{
		cout << "aliases name : \t\t" << host->h_aliases[i] << endl;
		i++;
	}


	i = 0;
	while (host->h_addr_list[i] != NULL)
	{
		struct in_addr inaddr; /* IP 주소를 저장할 구조체 */
		inaddr.s_addr = *((u_long *)(host->h_addr_list[i]));
		cout << hex << "호스트의 IP 주소 값(16진수) : \t " << inet_addr(inet_ntoa(inaddr)) << endl;
		cout << "호스트의 IP 주소 값(10진수) : \t" << inet_ntoa(inaddr) << endl << endl;
		i++;
	}

	WSACleanup();
	int year_support = 1900;
	time_t now = time(NULL); //시스템 시각을 얻어옴
	struct tm *lt = localtime(&now); //tm 구조체로 변환

	cout << dec << lt->tm_year + year_support << "년 " << lt->tm_mon + 1 << "월 " << lt->tm_mday  << "일 " <<
		lt->tm_hour << "시 " << lt->tm_min << "분 " << lt->tm_sec << "초 " << endl;
	system("pause");
	return 0;

}