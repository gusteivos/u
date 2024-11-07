
#ifndef UMUTEX_H
#define UMUTEX_H

#include <stddef.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum umutex_mode_e
{

    UMUTEX_MODE_NORMAL,
    UMUTEX_MODE_REAWIR,
    UMUTEX_MODE_REAWIR_SHARED,
    UMUTEX_MODE_REAWIR_EXCLUSIVE

} umutex_mode_t;

typedef void *(* umutex_create_t)(umutex_mode_t);

typedef int (* umutex_lock_t)(umutex_mode_t, void *);

typedef int (* umutex_try_lock_t)(umutex_mode_t, void *);

typedef int (* umutex_unlock_t)(umutex_mode_t, void *);

typedef void (* umutex_destroy_t)(umutex_mode_t, void *);

#ifdef __cplusplus
}
#endif

#endif/*UMUTEX_H*/
