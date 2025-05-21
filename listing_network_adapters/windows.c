/*win_init.c*/
#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
int main() {
    WSADATA d;  // more info about this data structure for windows socket programming on https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata

    if (WSAStartup(MAKEWORD(2, 2), &d)) { //WSAStartup is called with the requested version, Winsock 2.2 in this case
        printf("Failed to initialize.\n");
    return -1;
    }
        WSACleanup();
        printf("Ok.\n");

return 0;
}