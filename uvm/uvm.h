
#ifndef UVM_H
#define UVM_H

#include <stddef.h>
#include "ualloc.h"
#include "umutex.h"
#include "uvmcompi.h"
#include "uvmendia.h"
#include "uvmtypes.h"
#include "uvminstr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum uvm_status_e
{
    UVM_STATUS_OK = 0,
    UVM_STATUS_OUT_OF_MEMORY,
    UVM_STATUS_NON_SEQUENTIAL_MEMORY
} uvm_status_t;

UVM_LINKAG extern const uvm_status_t first_uvm_status;

UVM_LINKAG extern const uvm_status_t last_uvm_status;

UVM_LINKAG extern const char *uvm_status2str[];

UVM_LINKAG const char *uvm_status2string(uvm_status_t status);

struct uvm_s;

typedef struct uvm_s uvm_t;

UVM_LINKAG uvm_t *new_uvm(
    void *s_context,
    ualloc_t s_alloc,
    urealloc_t s_realloc,
    uunalloc_t s_unalloc,
    void *m_context,
    ualloc_t m_alloc,
    urealloc_t m_realloc,
    uunalloc_t m_unalloc,
    umutex_create_t create_mutex,
    umutex_lock_t lock_mutex,
    umutex_try_lock_t try_lock_mutex,
    umutex_unlock_t unlock_mutex,
    umutex_destroy_t destroy_mutex,
    size_t initial_memory_size,
    uvm_status_t initial_status
    );

UVM_LINKAG void  free_uvm(uvm_t *vm);

#ifdef __cplusplus
}
#endif

#endif/*UVM_H*/
