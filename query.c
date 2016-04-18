#include "header.h"

main(int argc, char* argv[]){
    int i;
    int sema_set;
//-----------------------------------------------SHARED MEMORY FOR DATA------------------------------
  int id;
  struct StudentInfo *infoptr;
  id = shmget(KEY, SEGSIZE,IPC_CREAT|0666);/* get shared memory to store data*/
  if (id <0){
    perror("create: shmget failed");
    exit(1);
  }
  infoptr=(struct StudentInfo *)shmat(id,0,0);/*attach the shared memory segment to the process's address space */
  if (infoptr <= (struct StudentInfo *) (0)) {
    perror("create: shmat failed");
    exit(2);
  }
//-----------------------------------------------REPEAT PROCESS FOR READERS------------------------------
  int readers;
  int *readptr;

  readers = shmget(KEY2, SEGSIZE, IPC_CREAT|0666);/* get shared memory to store reader count*/
  if(readers <0){
     perror("create: shmget failed");
     exit(1);
  }
  readptr=(int *)shmat(readers,0,0);/*attach the shared memory segment to the process's address space */
  if (readprt <= (int *) (0)) {
     perror("creat: shmat failed");
     exit(2);
  }

//-------------------------------------------------------------------------------------------------------- 

sema_set = semget(SEMA_KEY, 0, 0);

char getID[20];
printf("Student ID to search for:");
fgets(getID, sizeof(getID), stdin);

Wait(sema_set, 1);

readers++;
if(readers == 1)
  Wait(sema_set, 0);

Signal(sema_set, 1);
sleep(10);

bool foundstudent = false;

for(i = 0; i < 20; i++){
  if(!strcmp(infoPtr->sID, getID)){
    printf("\nInformation found for student:\n")
    printf("\nName: %s," infoPtr-> sName);
    printf("Student ID: %s", infoPtr -> sID);
    printf("Address: %s", infoPtr -> sAddress);
    printf("Phone Number: %s", infoPtr -> telNumber);
    foundstudent = true;
  }
  infoPtr++;
}

if(!foundstudent)
{
  printf("Results for ID %s not found.\n", getID);
}

Wait(sema_set, 1);
readers--;

if(readers == 0)
  Signal(sema_set, 0);

Signal(sema_set, 1);

}
