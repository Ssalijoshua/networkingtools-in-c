#include header.h

#if define
#include <conio.h>
#endif


int main(int argc, char *argv[]){
    
#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

}