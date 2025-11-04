/*
* File: finfo.c
* Lab 9 - System calls
* Author: Spencer Jones
* CPE 2600 121
* Build using make
*/
// finfo.c
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    if (S_ISREG(st.st_mode)) printf("Type: regular file\n");
    else if (S_ISDIR(st.st_mode)) printf("Type: directory\n");
    else if (S_ISLNK(st.st_mode)) printf("Type: symlink\n");
    else if (S_ISCHR(st.st_mode)) printf("Type: char device\n");
    else if (S_ISBLK(st.st_mode)) printf("Type: block device\n");
    else if (S_ISFIFO(st.st_mode)) printf("Type: fifo\n");
    else if (S_ISSOCK(st.st_mode)) printf("Type: socket\n");

    char p[11];
    p[0] = S_ISDIR(st.st_mode) ? 'd' : '-';
    p[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    p[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    p[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    p[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    p[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    p[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
    p[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    p[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    p[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
    p[10] = '\0';

    printf("Permissions: %s\n", p);
    printf("Owner UID: %d\n", (int)st.st_uid);
    printf("Size: %ld bytes\n", (long)st.st_size);

    char t[64];
    struct tm *tm = localtime(&st.st_mtime);
    strftime(t, sizeof(t), "%b %d %Y %H:%M", tm); // short readable format like "Nov 03 2025 19:32"
    printf("Modified: %s\n", t);

    return 0;
}
