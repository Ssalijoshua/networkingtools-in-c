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

int main(void){
    #if defined(_WIN32)
        WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
    #endif
    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    printf("Size of hints: %zu\n", sizeof(hints));
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP
    hints.ai_flags = AI_PASSIVE;  // Use wildcard IP address
    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);

    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);

    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
        }
// Binding the socket to the local address
    printf("Binding socket...\n");
    if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)){
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);  // Free the address info structure

    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
    }

        printf("Waiting for connection...\n");
        struct sockaddr_storage client_address;
        socklen_t client_len = sizeof(client_address);
        SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
    if (!ISVALIDSOCKET(socket_client)) {
        fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
    }

    printf("Client is connected... ");
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    printf("%s\n", address_buffer);
    

    printf("Reading request...\n");
    char request[1024];
    int bytes_received = recv(socket_client, request, 1024, 0);
    printf("Received %d bytes.\n", bytes_received);

    printf("%.*s", bytes_received, request);

    printf("Sending response...\n");
    const char *response =
    "HTTP/1.1 200 OK\r\n"
    "Connection: close\r\n"
    "Content-Type: text/plain\r\n\r\n"
    "Local time is: ";
    int bytes_sent = send(socket_client, response, strlen(response), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(response));

    time_t timer;
    time(&timer);
    char *time_string = ctime(&timer);
    bytes_sent = send(socket_client, time_string, strlen(time_string), 0);
    printf("Sent %d of %d bytes.\n", bytes_sent, (int)strlen(time_string));
    printf("Closing socket...\n");
    CLOSE_SOCKET(socket_client);

    #if defined(_WIN32)
        WSACleanup();
    #endif
        printf("Finished.\n");
    return 0;
}