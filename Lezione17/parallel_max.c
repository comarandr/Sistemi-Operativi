#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>

struct data_t {
  int *data;
  size_t len;
};

struct data_t read_nums(FILE *file);
int max_in_data(int *data, size_t len);
void *compute_max(void *ptr);

int main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stderr, "Specificare il nome di un file\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if(!file) {
    perror("fopen()");
    return 2;
  }

  struct data_t data = read_nums(file);
  printf("Letti %zu numeri interi.\n", data.len);

  struct data_t data1 = { .len = data.len / 2, .data = data.data };
  struct data_t data2 = {
    .len = data.len - data1.len,
    .data = data.data + data1.len
  };
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, compute_max, &data1);
  pthread_create(&thread2, NULL, compute_max, &data2);

  void *result1_ptr, *result2_ptr;
  pthread_join(thread1, &result1_ptr);
  pthread_join(thread2, &result2_ptr);

  int result1 = *(int*)result1_ptr;
  int result2 = *(int*)result2_ptr;
  int max = result1 > result2 ? result1 : result2;

  printf("Il massimo numero trovato è %d\n", max);

  return 0;
}

void *compute_max(void *ptr) {
  struct data_t data = *(struct data_t *)ptr;

  int *result = malloc(sizeof(int));
  *result = max_in_data(data.data, data.len);

  return result;
}

int max_in_data(int *data, size_t len) {
  int max = INT_MIN;
  for(int i = 0; i < len; ++i) {
    if(data[i] > max)
      max = data[i];
  }
  return max;
}

#define NITEMS 2000
struct data_t read_nums(FILE *file)
{
  size_t size = NITEMS;
  struct data_t data = {
    .len = 0,
    .data = malloc(sizeof(int) * size)
  };

  int r = 0;
  while((r = fread(data.data + data.len, sizeof(int), NITEMS, file)) == NITEMS)
  {
    data.len += r;
    size += NITEMS;
    data.data = realloc(data.data, sizeof(int) * size);
  }

  return data;
}
