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

  // list_t *lst_ = NULL;
  list_t *lst_ = list_init(destroy_data, compare_to);
  
  list_add(lst_, rval);

  printf("%ld\n", lst_->size);

  //free(rval);
  list_destroy(&lst_);
  return 0;
}
