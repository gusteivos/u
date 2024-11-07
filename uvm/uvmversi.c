#include "uvmversi.h"

void uvm_get_version(
    unsigned char *major,
    unsigned char *minor,
    unsigned char *patch,
    unsigned char *other
    )
{

    if (major != NULL)
    {
        *major = UVM_MAJOR_VERSION;
    }

    if (minor != NULL)
    {
        *minor = UVM_MINOR_VERSION;
    }

    if (patch != NULL)
    {
        *patch = UVM_PATCH_LEVEL;
    }

    if (other != NULL)
    {
        *other = UVM_OTHER_LEVEL;
    }

}
