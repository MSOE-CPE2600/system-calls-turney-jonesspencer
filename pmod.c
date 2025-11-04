/*
* File: pmod.c
* Lab 9 - System calls
* Author: Spencer Jones
* CPE 2600 121
* Build using make
*/
// pmod.c
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    int n = nice(10);
    printf("New nice: %d\n", n);

    struct timespec ts = {1, 837272638};
    nanosleep(&ts, NULL);

    printf("Goodbye from pmod.\n");
    return 0;
}
