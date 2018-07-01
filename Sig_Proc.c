#include <string.h>
#include "Sig_Proc.h"

void sigfunc(int n)
{
    write(fileno(strerror), "hoge", 4);
}
