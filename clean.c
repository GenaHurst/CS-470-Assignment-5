Get the ids of the two shared memory segments created;
Attach the shared memory segments;
Get the id of the semaphore set created in Load.c;

Wait(semaset, 0)// assuming semaset is the id of the semaphore set 
write the contents of the shared memory to file in the format of the input file;
delete the shared memory segments
sleep(10) // for debugging and testing
Signal(semaset, 0);

delete the semaphores.

#include "header.h"

main(){

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
  
    sema_set = GetSemaphs(SEMA_KEY, NUM_SEMAPHS); /* get a set of NUM_SEMAPHS
                 				   semaphores*/
    if ((sema_set < 0) ){
      perror("create: semget failed");
      exit(2);
    }
    Wait(sema_set, 0);
    
    FILE *myfile;
    myfile = fopen("updatedFile.txt", "w+");
    
    for(i = 0; i < 20; i++)
    {
      if(strcmp(infoPtr->sName, "end") != 0)
        fprintf(myfile, "%s%s%s%s", infoPtr->sName, infoPtr-> sID, infoPtr-> sAddress, infoPtr-> telNumber);
      infoPtr++;
    }
    
    shmdt((char *)infoPtr);
    shmctl(id, IPC_RMID, (struct shmid_ds *) (0));
    
    shmdt((char *)readptr);
    shmctl(readers, IPC_RMID, (struct shmid_ds *) (0));
    
    sleep(10);
    
    Signal(sema_set,0);
    
    semctl(sema_set, 0, IPC_RMID);
    
    exit(0);
  
  

}
