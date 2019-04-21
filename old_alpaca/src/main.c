#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef struct
{
  double a;
  double b;
  int i;
  float array[2];
} foo;

int main(int argc, char **argv)
{
  void *handle;
  double (*cosine)(double);
  void (*change_struct)(foo *);
  char *error;

  foo bar = {0.0, 0.0, 0};
  printf("before: %6.2f %6.2f %3d %6.2f %6.2f\n", bar.a, bar.b, bar.i, bar.array[0], bar.array[1]);

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

  (*change_struct)(&bar);

  printf(" after: %6.2f %6.2f %3d %6.2f %6.2f\n", bar.a, bar.b, bar.i, bar.array[0], bar.array[1]);

  printf("cos(2.0) = %f\n", (*cosine)(2.0));
  dlclose(handle);
}
