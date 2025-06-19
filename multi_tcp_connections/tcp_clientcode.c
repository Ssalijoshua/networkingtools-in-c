#include header.h

#if define
#include <conio.h>
#endif


int main(int argc, char *argv[]){
    // Initialize Winsock just incase it is what the user is using.
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

// checking to see if we have the required number of arguments
if (argc < 3){
    fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
    return 1;
}


}