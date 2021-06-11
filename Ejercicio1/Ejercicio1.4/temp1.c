#include <time.h>
#include <stdio.h>

int main() {

  clockid_t clocks[] = {
    CLOCK_REALTIME,
    CLOCK_MONOTONIC,
    CLOCK_PROCESS_CPUTIME_ID,
    CLOCK_THREAD_CPUTIME_ID,
    CLOCK_MONOTONIC_RAW,
    CLOCK_REALTIME_COARSE,
    (clockid_t) - 1 
  };

  int i;

  for (i = 0; clocks[i] != (clockid_t) - 1; i++) {
    struct timespec res;
    struct timespec res1;
    int ret;

    ret = clock_getres(clocks[i], &res);
    clock_gettime(clocks[i],&res1);
    if (ret)
      perror ("clock_getres");
    else
      printf ("clock=%d sec=%ld nsec=%ld\n",
              clocks[i], res.tv_sec, res.tv_nsec);

    printf ("clock=%d sec=%ld nsec=%ld\n",
              clocks[i], res1.tv_sec, res1.tv_nsec);
              
  }
  return 1;
}