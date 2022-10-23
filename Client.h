#pragma once
#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define PORT 8080
#define PACKET_SIZE 1024

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <thread> //thread
#include <cstdlib> //strcpy_s
#include <string> //getline