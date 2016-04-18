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
Wait(sema_set, 1);

readers++;
if(readers == 1)
  Wait(sema_set, 0);

Signal(sema_set, 1);
sleep(10);

for(i = 0; i < 20; i++){
  if(strcmp(intoPtr->sName, "end") != 0){
    printf("Name: %s," infoPtr-> sName);
    printf("Student ID: %s", infoPtr -> sID);
    printf("Address: %s", infoPtr -> sAddress);
    printf("Phone Number: %s", infoPtr -> telNumber);
  }
  infoPtr++;
}

Wait(sema_set, 1);
readers--;

if(readers == 0)
  Signal(sema_set, 0);

Signal(sema_set, 1);

}
