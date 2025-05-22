#include <stdio.h>
#include <time.h>

int main(void){
    time_t timer;
    
    time(&timer);

    printf("Current time: %s", ctime(&timer));

    return 0;

}