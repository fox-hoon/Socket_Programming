# Simple Chat with Socket Programming
+ C++ 소켓 통신을 사용한 간단한 채팅 프로그램
+ **서버**
  + Socket 생성 -> Socket에 이름연결(bind) -> 클라이언트 연결 대기(listen) -> 클라이언트 연결 승인(accept) -> 클라이언트로부터 메시지 받음
+ **클라이언트**
  + Socket 생성 -> 서버에 연결 시도(connect) -> 서버에 메시지 전달
  ![image](https://user-images.githubusercontent.com/84726924/197379449-65519330-4974-4790-a763-9ae08022e53e.png)
