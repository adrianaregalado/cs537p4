#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  if(argc != 6){
    printf(2, "arg error");
    exit();
  }
  
//   int sliceA = atoi(argv[1]);
//   int sleepA = atoi(argv[2]);
//   int sliceB = atoi(argv[3]);
//   int sleepB = atoi(argv[4]);
//   int sleepParent = atoi(argv[5]);

// schedtest spawns two children processes, each running the loop application
// One child A is given initial timeslice length of sliceA and runs loop sleepA; the other B is given initial timeslice length of sliceB and runs loop sleepB.
// Specifically, the parent process calls fork2() and exec() for the two children loop processes, A before B, with the specified initial timeslice;
// The parent schedtest process then sleeps for sleepParent ticks by calling sleep(sleepParent) (you may assume that sleepParent is much larger than sliceA+2*sleepA+sliceB+2*sleepB);
// After sleeping, the parent calls getpinfo(), and prints one line of two numbers separated by a space:
// printf(1, "%d %d\n", compticksA, compticksB), where compticksA is the compticks of process A in the pstat structure and similarly for B.
// The parent then waits for the two loop processes by calling wait() twice, and exits.

  exit();
}
