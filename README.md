# Simple Chat with Socket Programming
+ C++ 소켓 통신을 사용한 간단한 채팅 프로그램
+ **서버**
  + Socket 생성 -> Socket에 이름연결(bind) -> 클라이언트 연결 대기(listen) -> 클라이언트 연결 승인(accept) -> 클라이언트로부터 메시지 받음
+ **클라이언트**
  + Socket 생성 -> 서버에 연결 시도(connect) -> 서버에 메시지 전달
  ![image](https://user-images.githubusercontent.com/84726924/197379449-65519330-4974-4790-a763-9ae08022e53e.png)
***
# Server
+ **#include <WinSock2.h> / #pragma comment(lib, "ws2_32.lib")**
  + 소켓을 사용하기 위해선 라이브러리 링크를 걸어줘야 한다.
+ **#define PORT 8080**
  + PORT는 이미 예약된 포트를 제외하고 사용해야 한다.
  ![image](https://user-images.githubusercontent.com/84726924/197380204-ab7f6a70-ecf5-4d3a-b045-44a953eaadfd.png)
+ **WWSADATA wsa; / WSAStratup(MAKEWORD(2,2),&wsa);**
  + WSADATA는 Windows의 소켓 초기화 정보를 저장하기 위한 구조체이다.
  + WSADATA(소켓버전, WSADATA 구조체 주소);
    + Windows에 어느 소켓을 사용할 것인지 알려준다. 첫 번째 인자는 소켓 버전이 들어가고, 2.2 버전을 WORD 타입으로 들어가게 된다. 2.2 버전은 실수(float)이므로, 정수값으로 변환하여 넣어줄 수 있게 MAKEWORD 매크로를 사용한다.
    + 두 번째 인자에는 WSADATA 구조체의 포인터타입이 들어간다.
    
  ![image](https://user-images.githubusercontent.com/84726924/197380339-00551156-b8c2-47d0-971f-263cad84734e.png)
+ **SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);**
  + AF_INET(IPv4), SOCK_STREAM(연결지향형), IPPROTO_TCP(TCP 프로토콜)인자를 가진 소켓을 생성한다.
  + TCP 소켓은 크게 2가지로 나뉘게 된다. 첫 번째는 다른 컴퓨터로부터 들어오는 접속 승인 요청을 수락해주는 소켓이 존재해야 한다. 두 번째는 다른 컴퓨터와 연결된 소켓이 있어야 한다.
  
  ![image](https://user-images.githubusercontent.com/84726924/197380808-d905ea17-7ecd-4237-b727-4255fc92c3fd.png)
+ **SOCKADDR_IN addr = { 0 };**
  + SOCKADDR_IN 구조체는 Internet Address Family에서 Windows 소켓에서 소켓을 연결할 로컬 또는 원격 주소를 지정하는 데 사용된다. 즉, 주소정보를 담아두는 구조체이다.
  + **addr.sin_addr.s_addr = htonl(INADDR_ANY);**
    + 서버는 현재 동작되는 컴퓨터의 IP 주소로 설정해주어야 한다. INADDR_ANY를 넣어주면 현재 동작되는 컴퓨터 IP 주소로 설정하게 된다.
  + **addr.sin_port = PORT;**
    + PORT 번호를 설정한다. 16비트 안에서 표현할 수 있는 숫자로 정해야 하고, 이미 예약된 포트는 제외하고 설정해야 한다.
  + **addr.sin_family = AF_INET;**
    + SOCKADDR_IN 구조체는 sin_family가 반드시 AF_INET이어야 사용할 수 있다.
    
  ![image](https://user-images.githubusercontent.com/84726924/197381078-1df6e608-0b90-4cb6-b7d8-1eafbc6933ac.png)
+ **bind(server, (SOCKADDR\*)&addr, sizeof addr);**
  + bind 함수는 소켓에 주소정보를 연결한다. 설정한 주소 정보를 WinSock2.h에 정의된 bind 함수를 이용하여 소켓에 묶어준다.
  + 첫 번째 인자로는 소켓을 넣어주고, 두 번째 인자에는 bind될 소켓에 할당할 주소정보를 담고있는 구조체의 주소가 들어간다. 세 번째 인자는 두 번째 인자로 넣은 구조체의 크기가 들어간다.
+ **listen(server, SOMAXCONN);**
  + listen 함수는 연결을 수신하는상태로 소켓의 상태를 변경한다. 즉, 소켓을 접속 대기 상태로 만들어준다. 
  + SOMAXCONN은 한꺼번에 요청 가능한 최대 접속승인 수를 의미한다.
  
  ![image](https://user-images.githubusercontent.com/84726924/197381219-f7f8639d-2485-4961-ae2a-6074ee86a735.png)
+ **Client[cnt].first.client = accept(s, (SOCKADDR\*)&Client[cnt].first.clientaddr, &Client[cnt].first.clientsize);**
+ **accept(소켓, 소켓 구성요소 주소체의 주소, 그 구조체의 크기를 담고있는 변수의 주소);**
  + 클라이언트 측 소켓 생성 및 정보를 담을 구조체 생성 및 값 할당, 클라이언트가 접속 요청하면 승인해주는 역할을 한다.
  + accept 함수를 이용하여 접속 요청을 수락해준다. 이 함수는 동기화된 방식으로 동작된다. 동기화된 방식이란 요청을 마무리 하기 전까지 계속 대기상태에 놓이게 되는 것을 말한다.
  
  ![image](https://user-images.githubusercontent.com/84726924/197381348-b390c112-1e83-49b9-9ccd-eb6923e4d489.png)
+ **void recvData(SOCKET s, int num)**
  + 해당 함수는 클라이언트로부터 메시지를 받아와서 출력하는 역할을 수행한다.
+ **recv(s, buffer, sizeof buffer, 0);**
  + recv 함수는 대상 소켓으로부터 보내온 정보를 받아주는 역할을 한다. 
  
  ![image](https://user-images.githubusercontent.com/84726924/197381504-c9126727-898c-4643-a9ed-c8db3dfc9569.png)
***
# Client
+ **connect(server, (SOCKADDR\*)&addr, sizeof addr)**
+ **connect(소켓, 소켓 구성요소 구조체의 주소, 그 구조체의 크기);**
  + connect 함수는 지정된 소켓에 연결을 설정해준다. 서버에 연결하기위해 connect 함수를 사용한다.
  
  ![image](https://user-images.githubusercontent.com/84726924/197381826-fc80f6ea-91f2-4c48-9d3f-6908dd4d444b.png)
+ **send(server, name, sizeof name, 0);**
  + send 함수는 서버와 클라이언트 간 메시지를 전송한다.
  
  ![image](https://user-images.githubusercontent.com/84726924/197381851-2d091a48-a1d1-4ecf-84d0-d28594f91388.png)
***
# TEST
![image](https://user-images.githubusercontent.com/84726924/197382593-295ff536-af35-4d39-89d6-b831b8c53f9c.png)
+ 위 사진과 같이 서버와 클라이언트 2개의 통신을 확인할 수 있다.
