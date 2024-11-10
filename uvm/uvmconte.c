#include "uvmconte.h"

const uvm_context_status_t first_uvm_context_status =
UVM_CONTEXT_STATUS_OK;

const uvm_context_status_t last_uvm_context_status =
UVM_CONTEXT_STATUS_STACK_UNDERFLOW;

const char *uvm_context_status2str[] =
{
    [UVM_CONTEXT_STATUS_OK] = "OK",
    [UVM_CONTEXT_STATUS_ILLEGAL_INSTRUCTION] = "ILLEGAL INSTRUCTION",
    [UVM_CONTEXT_STATUS_STACK_OVERFLOW ] = "STACK OVERFLOW" ,
    [UVM_CONTEXT_STATUS_STACK_UNDERFLOW] = "STACK UNDERFLOW"
};

const char *uvm_context_status2string(uvm_context_status_t status)
{

    if (
        status < first_uvm_context_status ||
        status > last_uvm_context_status
        )
    {

        return NULL;

    }

    return uvm_context_status2str[status];

}

uvm_context_t *new_uvm_context(
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
)
{

    uvm_context_t *ctx = (uvm_context_t *)s_alloc(
        s_context,
        sizeof(uvm_context_t)
        );

    if (
        ctx == NULL
        )
    {

        return NULL;

    }

    if (
        init_uvm_context(
            ctx,
            create_mutex,
            lock_mutex,
            try_lock_mutex,
            unlock_mutex,
            destroy_mutex,
            memory_pointer,
            stack_size,
            stack_base,
            stack_pointer,
            individual_mode,
            halted,
            status
            )
        )
    {

        s_unalloc(s_context, ctx);

        return NULL;

    }

    return ctx;

}

static void *uvm_context_use_create_mutex(uvm_context_t *ctx)
{

    if (
        ctx == NULL ||
        ctx->destroy_mutex == NULL ||
        ctx->create_mutex == NULL
        )
    {

        return NULL;

    }

    return ctx->create_mutex(UMUTEX_MODE_NORMAL);

}

int init_uvm_context(
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
)
{

    if (
        ctx == NULL
        )
    {

        return EINVAL;

    }

    ctx->create_mutex = create_mutex;
    ctx->lock_mutex = lock_mutex;
    ctx->try_lock_mutex = try_lock_mutex;
    ctx->unlock_mutex = unlock_mutex;
    ctx->destroy_mutex = destroy_mutex;

    ctx->mutex = uvm_context_use_create_mutex(ctx);

    ctx->memory_pointer = memory_pointer;

    ctx->stack_size = stack_size;
    ctx->stack_base = stack_base;
    ctx->stack_pointer = stack_pointer;

    ctx->individual_mode = individual_mode;

    ctx->halted = halted;

    ctx->status = status;

    return 0;

}

int uvm_context_lock_mutex(uvm_context_t *ctx)
{

    if (
        ctx == NULL
        )
    {

        return EINVAL;

    }

    if (
        ctx->unlock_mutex ||
        ctx->lock_mutex
        )
    {

        return 0;

    }

    return ctx->lock_mutex(UMUTEX_MODE_NORMAL, ctx->mutex);

}

int uvm_context_try_lock_mutex(uvm_context_t *ctx)
{

    if (
        ctx == NULL
        )
    {

        return EINVAL;

    }

    if (
        ctx->unlock_mutex ||
        ctx->try_lock_mutex
        )
    {

        return 0;

    }

    return ctx->try_lock_mutex(UMUTEX_MODE_NORMAL, ctx->mutex);

}

int uvm_context_unlock_mutex(uvm_context_t *ctx)
{

    if (
        ctx == NULL
        )
    {

        return EINVAL;

    }

    if (ctx->unlock_mutex == NULL)
    {

        return 0;

    }

    return ctx->unlock_mutex(UMUTEX_MODE_NORMAL, ctx->mutex);

}

static void uvm_contex_use_destroy_mutex(uvm_context_t *ctx, void *mutex)
{

    if (
        ctx == NULL
        )
    {

        return;

    }

    if (ctx->destroy_mutex == NULL)
    {

        return;

    }

    ctx->destroy_mutex(UMUTEX_MODE_NORMAL, ctx->mutex);

}

int quit_uvm_context(uvm_context_t *ctx)
{

    if (
        ctx == NULL
        )
    {

        return EINVAL;

    }

    uvm_contex_use_destroy_mutex(ctx, ctx->mutex);

    return 0;

}

void free_uvm_context(
    uvm_context_t *ctx,
    void *s_context,
    uunalloc_t s_unalloc
    )
{

    if (
        ctx == NULL ||
        s_unalloc == NULL
        )
    {

        return;

    }

    quit_uvm_context(ctx);

    s_unalloc(s_context, ctx);

}
