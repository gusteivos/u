
#ifndef UMUTEX_H
#define UMUTEX_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void * (* umutex_create_t  )(void  );

typedef int    (* umutex_lock_t    )(void *);

typedef int    (* umutex_try_lock_t)(void *);

typedef int    (* umutex_unlock_t  )(void *);

typedef void   (* umutex_destroy_t )(void *);

#ifdef __cplusplus
}
#endif

#endif/*UMUTEX_H*/
