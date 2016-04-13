/* header.h */

//Moved include files to header.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

#define KEY  ((key_t)(19191))
#define SEGSIZE  sizeof(struct StudentInfo)

#define NUM_SEMAPHS 2
#define SEMA_KEY   ((key_t)(1919))

struct StudentInfo{
  char sName[30];
  char sID[10];
  char sAddress[30];
  char telNumber[15];
};

void Wait(int semaph, int n);
void Signal(int semaph, int n);
int GetSemaphs(key_t k, int n);
