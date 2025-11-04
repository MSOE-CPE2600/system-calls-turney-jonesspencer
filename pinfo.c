/*
* File: pinfo.c
* Lab 9 - System calls
* Author: Spencer Jones
* CPE 2600 121
* Build using make
*/
// pinfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    pid_t pid = (argc > 1) ? atoi(argv[1]) : getpid();

    errno = 0;
    int prio = getpriority(PRIO_PROCESS, pid);
    if (prio == -1 && errno) {
        perror("getpriority");
        return 1;
    }

    int sched = sched_getscheduler(pid);
    if (sched == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    const char* name = "UNKNOWN";
    switch (sched) {
        case SCHED_OTHER: name = "SCHED_OTHER"; break;
        case SCHED_FIFO:  name = "SCHED_FIFO";  break;
        case SCHED_RR:    name = "SCHED_RR";    break;
        case SCHED_BATCH: name = "SCHED_BATCH"; break;
        case SCHED_IDLE:  name = "SCHED_IDLE";  break;
        case SCHED_DEADLINE: name = "SCHED_DEADLINE"; break;
    }

    printf("PID: %d\nPriority: %d\nScheduler: %s\n", pid, prio, name);
    return 0;
}
