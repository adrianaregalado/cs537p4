#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include <stddef.h>

int
main(int argc, char **argv)
{
  if(argc != 6){
    printf(1, "schedtest: Incorrect number of arguments./n");
    exit();
  }
  //printf(1, "test1/n");
  int sliceA = atoi(argv[1]);
  //char* sleepA = argv[2];
  int sliceB = atoi(argv[3]);
  //char* sleepB = argv[4];
  int sleepParent = atoi(argv[5]);

  // schedtest spawns two children processes, each running the loop application
  // One child A is given initial timeslice length of sliceA and runs loop sleepA; the other B is given initial timeslice length of sliceB and runs loop sleepB.
  // Specifically, the parent process calls fork2() and exec() for the two children loop processes, A before B, with the specified initial timeslice;
  int pidA = fork2(sliceA);
  int pidB = fork2(sliceB);

  if (pidA == 0) {
    char *execA[] = {"loop", argv[2], NULL};
    exec(execA[0], execA);
  } 
//printf(1, "test2/n");
  if (pidB == 0) {
    char *execB[] = {"loop", argv[4], NULL};
    exec(execB[0], execB);
  } 
  // else if (pidB < 0) {
  //     exit();
  // }
//printf(1, "test3/n");
  sleep(sleepParent);
  // After sleeping, the parent calls getpinfo(), and prints one line of two numbers separated by a space:
  struct pstat  ps;
  //pstatPtr = &pstat;
  getpinfo(&ps);
  wait();
  wait();
  int procA = -1;
  int procB = -1;
  //if (result == 0) {
  for( int i = 0; i < NPROC; i++) {
      //if (ps.inuse[i]) {
          if (ps.pid[i] == pidA) {
            procA = ps.compticks[i];
            
          }
          if (ps.pid[i] == pidB) {
            procB = ps.compticks[i];
          }
      //}
  }
  // } else {
  //     printf(1, "schedtest: getpinfo failed.");
  // }
  printf(1, "%d %d\n", procA, procB);
  // printf(1, "%d %d\n", compticksA, compticksB), where compticksA is the compticks of process A in the pstat structure and similarly for B.
  // The parent then waits for the two loop processes by calling wait() twice, and exits.
 
  exit();
}
