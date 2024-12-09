#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct arg_t {
  int n;
  pthread_mutex_t mutex;
};

void *count(void *);

int main()
{
  struct arg_t arg = { 0, PTHREAD_MUTEX_INITIALIZER };

  pthread_t th1, th2;
  pthread_create(&th1, NULL, count, &arg);
  pthread_create(&th2, NULL, count, &arg);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  printf("n: %d\n", arg.n);

  return 0;
}

void *count(void *argptr) {
  struct arg_t *arg = (struct arg_t *)argptr; //riconverte

  int n = 0;
  do {
    usleep(500000);
    pthread_mutex_lock(&arg->mutex);
    arg->n += 1; //differenza
    n = arg->n;
    pthread_mutex_unlock(&arg->mutex);
    printf("n: %d\n", n);
  } while(n < 42);

  return NULL;
}
