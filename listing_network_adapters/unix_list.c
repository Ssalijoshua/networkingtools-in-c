#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>

/*unix_list.c continued*/
int main() {
    struct ifaddrs *addresses;
    if (getifaddrs(&addresses) == -1) {
        printf("getifaddrs call failed\n");
        return -1;
    }

    struct ifaddrs *address = addresses;
    while (address) {
        int family = address->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            printf("%s\t", address->ifa_name);  // Interface name (e.g., "eth0")
            printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");  // IP family

            char ap[100];  // Buffer for storing readable IP
            const int family_size = family == AF_INET ?
                sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

            // Convert binary IP to human-readable
            getnameinfo(address->ifa_addr,
                        family_size, ap, sizeof(ap),
                        0, 0, NI_NUMERICHOST);
            printf("\t%s\n", ap);  // Print IP address
        }
        address = address->ifa_next;  // Go to next interface
    }
    freeifaddrs(addresses);  // Free memory allocated by getifaddrs
    return 0;
}
