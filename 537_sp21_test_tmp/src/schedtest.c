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
  
  int sliceA = atoi(argv[1]);
  char* sleepA = argv[2];
  int sliceB = atoi(argv[3]);
  char* sleepB = argv[4];
  int sleepParent = atoi(argv[5]);

  // schedtest spawns two children processes, each running the loop application
  // One child A is given initial timeslice length of sliceA and runs loop sleepA; the other B is given initial timeslice length of sliceB and runs loop sleepB.
  // Specifically, the parent process calls fork2() and exec() for the two children loop processes, A before B, with the specified initial timeslice;
  int pidA = fork2(sliceA);
  int pidB = fork2(sliceB);

  if (pidA == 0) {
    char *execA[] = {"loop", sleepA, 0};
    exec(execA[0], execA);
  } else if (pidA < 0) {
      exit();
  }

  if (pidB == 0) {
    char *execB[] = {"loop", sleepB, 0};
    exec(execB[0], execB);
  } else if (pidB < 0) {
      exit();
  }

  sleep(sleepParent);
  // After sleeping, the parent calls getpinfo(), and prints one line of two numbers separated by a space:
  struct pstat p;
  int result = getpinfo(&p);
  int procA = -1;
  int procB = -1;
  if (result == 0) {
      for( int i = 0; i < NPROC; i++) {
          if (p.inuse[i]) {
              if (p.pid[i] == pidA) {
                procA = i;
              }
              if (p.pid[i] == pidB) {
                procB = i;
              }
          }
      }
  } else {
      printf(1, "schedtest: getpinfo failed.");
  }
  printf(1, "%d %d\n", p.compticks[procA], p.compticks[procB]);
  // printf(1, "%d %d\n", compticksA, compticksB), where compticksA is the compticks of process A in the pstat structure and similarly for B.
  // The parent then waits for the two loop processes by calling wait() twice, and exits.
  wait();
  wait();
  exit();
}
