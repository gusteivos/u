
#ifndef UALLOC_H
#define UALLOC_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void * (* ualloc_t  )(void *, size_t        );

typedef void * (* urealloc_t)(void *, void *, size_t);

typedef void   (* uunalloc_t)(void *, void *        );

#ifdef __cplusplus
}
#endif

#endif/*UALLOC_H*/
