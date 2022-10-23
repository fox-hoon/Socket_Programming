#include "Client.h"

void recvData(SOCKET& s) {
	char buffer[PACKET_SIZE];
	while (TRUE) {
		ZeroMemory(buffer, sizeof buffer);	//버퍼를 0으로 초기화
		recv(s, buffer, sizeof buffer, 0);	//recv 함수는 대상 소켓으로부터 보내온 정보를 받아주는 역할
		std::cout << "Server : " << buffer << std::endl;
	}
}

int main() {
	char IP[PACKET_SIZE] = { 0 },
		name[PACKET_SIZE] = { 0 };

	std::cout << "User name : ";
	std::cin >> name;
	std::cout << "IP : ";
	std::cin >> IP;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = { 0 };
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	while (connect(server, (SOCKADDR*)&addr, sizeof addr));	//connect 함수는 지정된 소켓에 연결을 설정
	send(server, name, sizeof name, 0); //이름보내기

	std::thread(recvData, std::ref(server)).detach();	//recvData 함수 쓰레드 실행

	while (TRUE) {
		ZeroMemory(name, sizeof name);
		std::cout << "Message : ";
		std::cin >> name;
		send(server, name, sizeof name, 0);	//서버에 메시지 전송
	}
}