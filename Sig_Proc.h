#include <signal.h>

void sigfunc(int n)
{
    write(fileno(stderr), "hoge", 4);
}
