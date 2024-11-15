
#ifndef UVM_H
#define UVM_H

#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include "ualloc.h"
#include "umutex.h"
#include "uvmcompi.h"
#include "uvmendia.h"
#include "uvmtypes.h"
#include "uvmconte.h"
#include "uvminstr.h"
#include "uvmversi.h"

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
    size_t minimum_memory_size,
    size_t maximum_memory_size,
    size_t initial_memory_size,
    void *grow_argument,
    void *swap_argument,
    uvm_status_t initial_status,
    void *extra_argument
    );

UVM_LINKAG int uvm_set_status(uvm_t *vm, uvm_status_t  status);

UVM_LINKAG int uvm_get_status(uvm_t *vm, uvm_status_t *status);

UVM_LINKAG int uvm_get_minimum_memory_size(uvm_t *vm, size_t *size);

UVM_LINKAG int uvm_get_maximum_memory_size(uvm_t *vm, size_t *size);

UVM_LINKAG int uvm_get_memory_size(uvm_t *vm, size_t *size);

UVM_LINKAG int uvm_get_block_count(uvm_t *vm, size_t *count);

UVM_LINKAG int uvm_grow(uvm_t *vm, size_t  new_memory_size);

UVM_LINKAG int uvm_swap(uvm_t *vm, size_t block, uvm_byte *was);

UVM_LINKAG int uvm_store(
    uvm_t *vm,
    uvm_status_t *status,
    size_t *address,
    size_t buffer_size,
    unsigned char *buffer,
    bool increment_address
    );

UVM_LINKAG int uvm_fetch(
    uvm_t *vm,
    uvm_status_t *status,
    size_t *address,
    size_t buffer_size,
    unsigned char *buffer,
    bool increment_address
    );

UVM_LINKAG int uvm_context_stack_push(
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx,
    size_t buffer_size,
    unsigned char *buffer
    );

UVM_LINKAG int uvm_context_stack_pop (
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx,
    size_t buffer_size,
    unsigned char *buffer,
    bool decrement
    );

typedef void (* uvm_inout_handler_t)(
    uvm_t *,
    uvm_status_t *,
    uvm_context_t *,
    bool,
    size_t,
    size_t,
    unsigned char *
    );

UVM_LINKAG int uvm_execute(
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx,
    uvm_inout_handler_t io_handler
    );

UVM_LINKAG void  free_uvm(uvm_t *vm);

#ifdef __cplusplus
}
#endif

#endif/*UVM_H*/
