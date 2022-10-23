#include "Server.h"

void recvData(SOCKET s, int num) {
	char buffer[PACKET_SIZE] = { 0 };
	recv(s, buffer, sizeof buffer, 0); //User name 받기
	Client[num].second = buffer;

	while (TRUE) {
		ZeroMemory(buffer, sizeof buffer);
		recv(s, buffer, sizeof buffer, 0); //Message 받기
		std::cout << Client[num].second << " : " << buffer << std::endl;
	}
}

void ACCEPT(SOCKET& s) { //클라이언트들의 접속을 수용하는 함수
	int cnt = 0;
	while (TRUE) {
		Client.push_back(pii(CLIENT(), ""));
		//client 측 소켓 생성 및 정보를 담을 구조체 생성 및 값 할당. Client가 접속을 요청하면 승인해주는 역할
		//accept(소켓, 소켓 구성요소 구조체의 주소, 구조체의 크기를 담고있는 변수 주소)
		Client[cnt].first.client = accept(s, (SOCKADDR*)&Client[cnt].first.clientaddr, &Client[cnt].first.clientsize);
		Client[cnt].first.number = cnt;
		std::thread(recvData, Client[cnt].first.client, cnt).detach();	//recvData 함수 쓰레드 실행
		cnt += 1;
	}
}

int main() {
	WSADATA wsa;	//Windows의 소켓 초기화 정보를 저장하기 위한 구조체
	WSAStartup(MAKEWORD(2, 2), &wsa);	//Windows에 어느 소켓을 활용할 것인지 알려줌.WSAStartup(소켓버전, WSADATA 구조체 주소);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//AF_INET(IPv4), SOCK_STREAM(연결지향형), IPPROTO_TCP(TCP 프로토콜)인자를 가진 소켓 생성

	SOCKADDR_IN addr = { 0 };	//sa_family가 AF_INET(IPv4)인 경우에 사용하는 구조체
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	bind(server, (SOCKADDR*)&addr, sizeof addr);	//소켓에 설정한 주소정보를 묶음. bind(소켓, 소켓 구성요소 구조체의 주소, 구조체 크기)
	listen(server, SOMAXCONN);	//연결을 수신하는 상태로 소켓 상태 변경(소켓 접속 대기 상태). SOMAXCONN은 한번에 요청 가능한 최대 접속승인 수

	std::thread(ACCEPT, std::ref(server)).detach();	//ACCEPT 함수 실행 쓰레드를 쓰레드 개체와 분리하여 독립적으로 사용

	char name[PACKET_SIZE],
		message[PACKET_SIZE];

	while (TRUE) {
		ZeroMemory(name, sizeof name);	//메모리 시작 주소부터 메모리 크기만큼 0으로 초기화
		ZeroMemory(message, sizeof message);
		std::cin >> name >> message;
		for (int i = 0; i < Client.size(); i++)
			if (!strcmp(Client[i].second.c_str(), name))
				send(Client[i].first.client, message, sizeof message, 0);	//Client에 메시지 전송
	}
}