/*win_list.c*/
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

/*Required when compiling with Microsoft Visual C. No effect when compiling with MinGW*/
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

int main() {
    WSADATA d;  // more info about this data structure for windows socket programming on https://learn.microsoft.com/en-us/windows/win32/api/winsock/ns-winsock-wsadata

    if (WSAStartup(MAKEWORD(2, 2), &d)) { //WSAStartup is called with the requested version, Winsock 2.2 in this case
        printf("Failed to initialize.\n");
    return -1;
    }
        WSACleanup();
        printf("Ok.\n");

        DWORD asize = 20000;
        PIP_ADAPTER_ADDRESSES adapters;
    do {
        adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);
    if (!adapters) {
        printf("Couldn't allocate %ld bytes for adapters.\n", asize);
        WSACleanup();
    return -1;
    }
        int r = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0,adapters, &asize);
    if (r == ERROR_BUFFER_OVERFLOW) {
        printf("GetAdaptersAddresses wants %ld bytes.\n", asize);
        free(adapters);
    } else if (r == ERROR_SUCCESS) {
    break;
    } else {
        printf("Error from GetAdaptersAddresses: %d\n", r);
        free(adapters);
        WSACleanup();
    return -1;
    }
    } while (!adapters);

    PIP_ADAPTER_ADDRESSES adapter = adapters;
    while (adapter) {
        printf("\nAdapter name: %S\n", adapter->FriendlyName);
        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
    while (address) {
        printf("\t%s",
        address->Address.lpSockaddr->sa_family == AF_INET ?
        "IPv4" : "IPv6");
        char ap[100];
        getnameinfo(address->Address.lpSockaddr,
        address->Address.iSockaddrLength,
        ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
        printf("\t%s\n", ap);
        address = address->Next;
    }
        adapter = adapter->Next;
    }
return 0;
}