#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int die(char *text){                
    printf("Die: %s\n", text);
    exit(-1);
} 

int hexdump(char *target, int size){                
    for (int i=0; i<size/8; i++){                 
        printf("0x%x: 0x%llx\n", i*8, *(unsigned long*)(target+(i*8)));                                  
    }                                                                                                
}

int main(){
    
    return 0;
}