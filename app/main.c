#include <stdio.h>
#include "../src/lab.h"

static void destroy_data(void *data)
{
  free(data);
}

static int compare_to(const void *a, const void *b)
{
  int fst = *(int *)a;
  int snd = *(int *)b;
  return fst - snd;
}

int main(void)
{
  printf("hello world\n");
  int *rval = (int *)malloc(sizeof(int));
  *rval = 1;
  int *rval2 = (int *)malloc(sizeof(int));
  *rval2 = 2;

  list_t *lst_ = NULL;
  lst_ = list_init(destroy_data, compare_to);
  
  list_add(lst_, rval);
  list_add(lst_, rval2);

  printf("%ld\n", lst_->size);

  list_destroy(&lst_);
  lst_ = NULL;
  rval = NULL;
  rval2 = NULL;
  return 0;
}
