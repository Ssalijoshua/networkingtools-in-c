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
#define ISVALIDSOCKET(s) (s != INVALID_SOCKET)
#define CLOSE_SOCKET(s) closesocket(s)
#define GETSOCKETERRNO() WSAGETERROR()
#else
#define ISVALIDSOCKET(s) (s >= 0)
#define CLOSE_SOCKET(s) close(s)
#define GETSOCKETERRNO() errno
#endif

#if !defined(_WIN32)
#define SOCKET int
#endif
 
int main (void){


}
