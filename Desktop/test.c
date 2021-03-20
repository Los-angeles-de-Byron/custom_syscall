#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <string.h>

int main(void){
	
    char st[256];

    printf("Enter an arithmetic operation: ");
    gets(st);

    printf("Memory address of input (outside syscall): %p\n", &st);
    
    long sta = syscall(333, st);  

    printf("return value from syscall: %ld\n", sta);    
    return 0;
}
