/* File create.c */

#include "header.h"

main()
{
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
  readers = 0;

  /* store data in the shared memory segment */  
  
  //Removed because information will be read in from a file instead.
  /*
  strcpy(infoptr->fName,"Joe");
  strcpy(infoptr->lName, "Smith");
  strcpy(infoptr->telNumber, "606-111-2222");
  strcpy(infoptr->whoModified, " ");
  */
  
  //Open the file for reading, if possible.
  FILE *myfile;
  myfile = fopen("sampleinput.txt", "r");
  if (myfile == NULL)
  {
     perror("File Cannot Be Opened!"); 
     exit(2);
  }
  
  //Read through the file, where the file is set up in the following format for every four lines:
  /*
  	Line 1: Student Name
  	Line 2: Student ID
  	Line 3: Student Address
  	Line 4: Student Phone Number
  */
 
  char *lineRead = NULL;
  size_t length = 0;
  int entries = 0;

  while(!feof(myfile))
  {
    //Get the student's name
    getline(&lineRead, &length, myfile);
    strcpy(infoPtr->sName, line);
    //Get the student's id
    getline(&lineRead, &length, myfile);
    strcpy(infoPtr->sID, line);
    //Get the student's address
    getline(&lineRead, &length, myfile);
    strcpy(infoPtr->sAddress, line);
    //Get the student's phone number
    getline(&lineRead, &length, myfile);
    strcpy(infoPtr->telNumber, line);
    infoPtr++;
    entries++;
  }
 
  //Close the file when the reading is done. 
  fclose(myfile);
  
  for(i = entries; i < 19; i++)
  {
  	strcpy(infoPtr->name, "end");
  	infoPtr++;
  }
  
  sleep(10);
  signal(sema_set, 0);
  
  exit(0);
}
