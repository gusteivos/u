#include "shiargcv.h"

char *shiargcv(int *argc, char **argv[])
{

    assert(argc && argv);

    assert(*argc > 0 && *argv);

    char *v = (*argv)[0];

    --(*argc);

    ++(*argv);

    return v;

}
