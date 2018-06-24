#include <string.h>
#include "Sig_Proc.h"

void sigfunc(int n)
{
    write(fileno(stderr), "hoge", 4);
}
