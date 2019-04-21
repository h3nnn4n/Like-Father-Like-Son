#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef struct
{
  double a;
  double b;
  int i;
} foo;

int main(int argc, char **argv)
{
  void *handle;
  double (*cosine)(double);
  void (*change_struct)(foo *);
  char *error;

  foo bar;
  printf("before: %6.2f %6.2f %3d\n", bar.a, bar.b, bar.i);

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

  printf(" after: %6.2f %6.2f %3d\n", bar.a, bar.b, bar.i);

  printf("cos(2.0) = %f\n", (*cosine)(2.0));
  dlclose(handle);
}
