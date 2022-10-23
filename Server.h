#pragma once
#pragma comment(lib, "ws2_32.lib") //링커

#define PORT 8080 //PORT를 사용할때는 예약된 포트를 제외하고 사용
#define PACKET_SIZE 1024

#include <iostream> // c++ stadard input output
#include <winsock2.h> // winsock
#include <windows.h> // ZeroMemory
#include <vector> //vector
#include <utility> //pair
#include <thread> //thread
#include <cstdlib>

class CLIENT {
public:
	SOCKET client;
	SOCKADDR_IN clientaddr = { 0 }; //SOCKADDR 구조체에서 sa_family가 AF_INET(IPv4)인 경우에 사용하는 구조체
	int clientsize = sizeof clientaddr;
	int number = -1;
	CLIENT() { }
};

typedef std::pair<CLIENT, std::string> pii;	//pair는 두 개체를 단일 개체로 처리하는 기능을 제공하는 구조체

std::vector<pii> Client;	//pair 타입을 저장하는 vector