#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef struct
{
  double a;
  double b;
  int i;
  float array[2];
  float *ptr;
} foo;

int main(int argc, char **argv)
{
  void *handle;
  double (*cosine)(double);
  void (*change_struct)(foo *);
  void (*use_malloc)(foo *);
  char *error;

  foo bar = {0.0, 0.0, 0};
  bar.ptr = NULL;
  printf("before: %6.2f %6.2f %3d %6.2f %6.2f", bar.a, bar.b, bar.i, bar.array[0], bar.array[1]);
  printf(" ptr: %p\n", bar.ptr);

  handle = dlopen("libnew_alpaca.dylib", RTLD_LAZY);
  if (!handle)
  {
    fputs(dlerror(), stderr);
    exit(1);
  }

  cosine = dlsym(handle, "cos");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }

  change_struct = dlsym(handle, "change_struct");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }

  use_malloc = dlsym(handle, "use_malloc");
  if ((error = dlerror()) != NULL)
  {
    fputs(error, stderr);
    exit(1);
  }

  (*change_struct)(&bar);
  (*use_malloc)(&bar);

  printf(" after: %6.2f %6.2f %3d %6.2f %6.2f", bar.a, bar.b, bar.i, bar.array[0], bar.array[1]);
  printf(" ptr: %p", bar.ptr);
  printf(" %6.2f %6.2f\n", bar.ptr[0], bar.ptr[1]);

  printf("cos(2.0) = %f\n", (*cosine)(2.0));
  dlclose(handle);
}
