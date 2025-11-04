/*
* File: info.c
* Lab 9 - System calls
* Author: Spencer Jones
* CPE 2600 121
* Build using make
*/
// info.c

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>

/*
    Part 1: Information Maintenance System Calls

    Prints:
    - current time of day in nanoseconds
    - system network name
    - operating system name
    - OS release and version
    - system hardware type
    - number of CPUs
    - total physical memory in bytes
    - total free memory in bytes
*/

int main(int argc, char* argv[])
{
    /*
    struct timespec {
        time_t tv_sec;  // seconds
        long  tv_nsec;  // nanoseconds [0, 999999999]
    };
    */
    // Make timespec struct to pass with system call and print returned result.
    // CLOCK_REALTIME to get the current real clock time.
    struct timespec t;
    if (clock_gettime(CLOCK_REALTIME, &t) == 0) {
        printf("Current clock time in seconds: %ld\n", t.tv_sec);
        printf("Current clock time in nanoseconds: %ld\n", t.tv_nsec);
    }

    // uname() fills in system information like OS name, version, hardware, etc.
    struct utsname info;
    if (uname(&info) == 0) {
        // Only print strings that are not empty
        if (info.nodename[0] != '\0') {
            printf("System Network Name: %s\n", info.nodename);
        }
        if (info.sysname[0] != '\0') {
            printf("System Name:   %s\n", info.sysname);
        }
        if (info.release[0] != '\0') {
            printf("Release:       %s\n", info.release);
        }
        if (info.version[0] != '\0') {
            printf("Version:       %s\n", info.version);
        }
        if (info.machine[0] != '\0') {
            printf("Machine:       %s\n", info.machine);
        }
        if (info.domainname[0] != '\0') {
            printf("Domain Name:   %s\n", info.domainname);
        }
    }

    // gethostname() returns the host name. This is another "network name" of the system.
    char buff[128];
    if (gethostname(buff, sizeof(buff)) == 0 && buff[0] != '\0') {
        printf("Hostname: %s\n", buff);
    }

    // sysconf(_SC_NPROCESSORS_ONLN) returns the number of processors currently online.
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs > 0) {
        printf("The system has %ld processors\n", nprocs);
    }

    // sysinfo() returns memory information for the whole system.
    // The values are reported in units of "mem_unit", so multiply to get bytes.
    struct sysinfo s;
    if (sysinfo(&s) == 0) {
        unsigned long long total_bytes =
            (unsigned long long) s.totalram * (unsigned long long) s.mem_unit;
        unsigned long long free_bytes =
            (unsigned long long) s.freeram * (unsigned long long) s.mem_unit;

        printf("Total physical memory (bytes): %llu\n", total_bytes);
        printf("Total free memory (bytes):     %llu\n", free_bytes);
    }

    return 0;
}
