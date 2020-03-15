#define __GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <netdb.h>


//                           compile with:gcc - fPIC - pie - Wl, -E ldtime.c - o ldtime

long int now = 0;
long int ftime = 0;

int main(int argc, char *argv[])
{
  char env[64];

  if (argc < 3) {
    fprintf(stderr, "Usage:   %s unixtime command\n", basename(argv[0]));
    fprintf(stderr, "Example: %s 2147483647 date\n", basename(argv[0]));
    return -1;
  }

  ftime = atoi(argv[1]);

  long int tdelta = ftime-syscall(SYS_time, NULL);

  snprintf(env, 64, "TDELTA=%ld", tdelta);

  char selfpath[1024];
  memset(selfpath, 0, sizeof(selfpath));
  if (readlink("/proc/self/exe", selfpath, sizeof(selfpath) - 1) < 0) {
    perror("bah");
    exit(EXIT_FAILURE);
  };

#if 0
  int status = 0;
  int child = 0;

  child = fork();
  if (child == 0) {
    int r = setenv("LD_PRELOAD", selfpath, 1);
    r = putenv(env);

    execvp(argv[2], argv + 2);
    return 1;
  } else {
    while (1) {
      wait(&status);
      if (WIFEXITED(status) || WIFSIGNALED(status)) {
        break;
      }
    }
    return status >> 8;
  }

#else

  setenv("LD_PRELOAD", selfpath, 1);
  putenv(env);

  execvp(argv[2], argv + 2);
  fprintf(stderr, "%s: command not found\n", argv[2]);
  return 127;

#endif
}

//                               Down from here you can put your faked functions.
long int getfaketime()
{
  char *env;
  env = getenv("TDELTA");
  long int tdelta = strtol(env, NULL, 10);
  return syscall(SYS_time, NULL) + tdelta;
}

time_t time(time_t * tloc)
{
  if (tloc != NULL) {
    *tloc = getfaketime();
    return 0;
  } else
    return getfaketime();
}

int gettimeofday(struct timeval *tv, void *tz)
{
  tv->tv_sec = getfaketime();
  return 0;
}


int clock_gettime(clockid_t clk_id, struct timespec *ts)
{
  ts->tv_sec = getfaketime();
  return 0;
}


//int rtime(struct sockaddr_in *addrp, struct rpc_timeval *timep,
//                 struct rpc_timeval *timeout) {
int rtime(struct sockaddr_in *addrp, struct timeval *timep, struct timeval *timeout)
{
  timep->tv_sec = getfaketime();
  return 0;
}

struct ntptimeval {
  struct timeval time;          /* Current time */
  long int maxerror;            /* Maximum error */
  long int esterror;            /* Estimated error */
  long int tai;                 /* TAI offset */
};

int ntp_gettime(struct ntptimeval *ntv)
{
  ntv->time.tv_sec = getfaketime();
  return 0;
}
