#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#if defined(_WIN32)
#define ISVALID_SOCKET(s) (s != INVALID_SOCKET)
#define CLOSE_SOCKET(s) closesocket(s)
#define GETSOCKERRNO() WSAGETERROR()
#else
#define ISVALID_SOCKET(s) (s >= 0)
#define CLOSE_SOCKET(s) close(s)
#define GETSOCKERRNO() errno
#endif

int main(void){
    time_t timer;
    time(&timer);
    printf("Current time: %s", ctime(&timer));
    return 0;

}