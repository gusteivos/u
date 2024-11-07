
#ifndef UVMVERSI_H
#define UVMVERSI_H

#include <limits.h>
#include <stddef.h>
#include "uvmcompi.h"

/**
 * @brief Major version of UVM.
 *
 * Value between 0 and UCHAR_MAX representing the major version.
 */
#define UVM_MAJOR_VERSION 0

/**
 * @brief Minor version of UVM.
 *
 * Value between 0 and UCHAR_MAX representing the minor version.
 */
#define UVM_MINOR_VERSION 0

#ifndef UVM_PATCH_LEVEL
/**
 * @brief Patch level for UVM.
 *
 * Value must be between 0 and UCHAR_MAX.
 */
#define UVM_PATCH_LEVEL   0
#endif/*UVM_PATCH_LEVEL*/
#if UVM_PATCH_LEVEL < 0 || UVM_PATCH_LEVEL > UCHAR_MAX
    #error "UVM_PATCH_LEVEL must be in the range 0 to UCHAR_MAX"
#endif

#ifndef UVM_OTHER_LEVEL
/**
 * @brief Additional version level for UVM.
 *
 * Value must be between 0 and UCHAR_MAX.
 */
#define UVM_OTHER_LEVEL   0
#endif/*UVM_OTHER_LEVEL*/
#if UVM_OTHER_LEVEL < 0 || UVM_OTHER_LEVEL > UCHAR_MAX
    #error "UVM_OTHER_LEVEL must be in the range 0 to UCHAR_MAX"
#endif

UVM_LINKAG void uvm_get_version(
    unsigned char *major,
    unsigned char *minor,
    unsigned char *patch,
    unsigned char *other
    );

#endif/*UVMVERSI_H*/
