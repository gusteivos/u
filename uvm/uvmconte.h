
#ifndef UVMCONTE_H
#define UVMCONTE_H

#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include "ualloc.h"
#include "umutex.h"
#include "uvmcompi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum uvm_context_status_e
{

    UVM_CONTEXT_STATUS_OK = 0,
    UVM_CONTEXT_STATUS_ILLEGAL_INSTRUCTION,
    UVM_CONTEXT_STATUS_STACK_OVERFLOW ,
    UVM_CONTEXT_STATUS_STACK_UNDERFLOW,
    UVM_CONTEXT_STATUS_BY_ZERO

} uvm_context_status_t;

UVM_LINKAG extern const uvm_context_status_t first_uvm_context_status;

UVM_LINKAG extern const uvm_context_status_t last_uvm_context_status;

UVM_LINKAG extern const char *uvm_context_status2str[];

UVM_LINKAG const char *uvm_context_status2string(uvm_context_status_t status);

typedef struct uvm_context_s
{

    umutex_create_t create_mutex;
    umutex_lock_t lock_mutex;
    umutex_try_lock_t try_lock_mutex;
    umutex_unlock_t unlock_mutex;
    umutex_destroy_t destroy_mutex;

    void *mutex;

    size_t memory_pointer;

    size_t stack_size;
    size_t stack_base;
    size_t stack_pointer;

    bool individual_mode;

    bool halted;

    uvm_context_status_t status;

} uvm_context_t;

UVM_LINKAG uvm_context_t *new_uvm_context(
    void *s_context,
    ualloc_t s_alloc,
    uunalloc_t s_unalloc,
    umutex_create_t create_mutex,
    umutex_lock_t lock_mutex,
    umutex_try_lock_t try_lock_mutex,
    umutex_unlock_t unlock_mutex,
    umutex_destroy_t destroy_mutex,
    size_t memory_pointer,
    size_t stack_size,
    size_t stack_base,
    size_t stack_pointer,
    bool individual_mode,
    bool halted,
    uvm_context_status_t status
    );

UVM_LINKAG int init_uvm_context(
    uvm_context_t *ctx,
    umutex_create_t create_mutex,
    umutex_lock_t lock_mutex,
    umutex_try_lock_t try_lock_mutex,
    umutex_unlock_t unlock_mutex,
    umutex_destroy_t destroy_mutex,
    size_t memory_pointer,
    size_t stack_size,
    size_t stack_base,
    size_t stack_pointer,
    bool individual_mode,
    bool halted,
    uvm_context_status_t status
    );

UVM_LINKAG int uvm_context_lock_mutex(uvm_context_t *ctx);

UVM_LINKAG int uvm_context_try_lock_mutex(uvm_context_t *ctx);

UVM_LINKAG int uvm_context_unlock_mutex(uvm_context_t *ctx);

UVM_LINKAG int quit_uvm_context(uvm_context_t *ctx);

UVM_LINKAG void free_uvm_context(
    uvm_context_t *ctx,
    void *s_context,
    uunalloc_t s_unalloc
    );

#ifdef __cplusplus
}
#endif

#endif/*UVMCONTE_H*/
