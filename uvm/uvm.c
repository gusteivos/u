#include "uvm.h"
#include <string.h>

const uvm_status_t first_uvm_status = UVM_STATUS_OK;

const uvm_status_t last_uvm_status = UVM_STATUS_NON_SEQUENTIAL_MEMORY;

const char *uvm_status2str[] =
{
    [UVM_STATUS_OK] = "OK",
    [UVM_STATUS_OUT_OF_MEMORY] = "OUT OF MEMORY",
    [UVM_STATUS_NON_SEQUENTIAL_MEMORY] = "NON SEQUENTIAL MEMORY"
};

const char *uvm_status2string(uvm_status_t status)
{

    if (status < first_uvm_status || status > last_uvm_status)
    {

        return NULL;

    }

    return uvm_status2str[status];

}

struct uvm_s
{

    void *s_context;
    ualloc_t s_alloc;
    urealloc_t s_realloc;
    uunalloc_t s_unalloc;

    void *m_context;
    ualloc_t m_alloc;
    urealloc_t m_realloc;
    uunalloc_t m_unalloc;

    umutex_create_t create_mutex;
    umutex_lock_t lock_mutex;
    umutex_try_lock_t try_lock_mutex;
    umutex_unlock_t unlock_mutex;
    umutex_destroy_t destroy_mutex;

    size_t minimum_memory_size;
    size_t maximum_memory_size;
    size_t memory_size;
    uvm_byte *memory;
    void *memory_mutex;

    void *individual_mode_mutex;
    uvm_context_t *individual_mode_owner;

    uvm_status_t status;

};

static void *uvm_use_create_mutex(uvm_t *, umutex_mode_t);
static int uvm_use_lock_mutex(uvm_t *, umutex_mode_t, void *);
static int uvm_use_try_lock_mutex(uvm_t *, umutex_mode_t, void *);
static int uvm_use_unlock_mutex(uvm_t *, umutex_mode_t, void *);
static void uvm_use_destroy_mutex(uvm_t *, umutex_mode_t, void *);

static int uvm_store_byte(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_byte  , bool
    );
static int uvm_fetch_byte(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_byte *, bool
    );
static int uvm_store_sbyte(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_sbyte  , bool
    );
static int uvm_fetch_sbyte(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_sbyte *, bool
    );
static int uvm_store_short(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_short  , bool
    );
static int uvm_fetch_short(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_short *, bool
    );
static int uvm_store_ushort(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_ushort  , bool
    );
static int uvm_fetch_ushort(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_ushort *, bool
    );
static int uvm_store_int(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_int  , bool
    );
static int uvm_fetch_int(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_int *, bool
    );
static int uvm_store_uint(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_uint  , bool
    );
static int uvm_fetch_uint(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_uint *, bool
    );
static int uvm_store_size(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_size  , bool
    );
static int uvm_fetch_size(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_size *, bool
    );
static int uvm_store_ssize(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_ssize  , bool
    );
static int uvm_fetch_ssize(
    uvm_t *, uvm_status_t *, size_t *,
    uvm_ssize *, bool
    );

static int uvm_context_stack_push_byte(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_byte
    );
static int uvm_context_stack_pop_byte(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_byte *, bool
    );
static int uvm_context_stack_push_sbyte(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_sbyte
    );
static int uvm_context_stack_pop_sbyte(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_sbyte *, bool
    );
static int uvm_context_stack_push_short(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_short
    );
static int uvm_context_stack_pop_short(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_short *, bool
    );
static int uvm_context_stack_push_ushort(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_ushort
    );
static int uvm_context_stack_pop_ushort(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_ushort *, bool
    );
static int uvm_context_stack_push_int(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_int
    );
static int uvm_context_stack_pop_int(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_int *, bool
    );
static int uvm_context_stack_push_uint(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_uint
    );
static int uvm_context_stack_pop_uint(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_uint *, bool
    );
static int uvm_context_stack_push_size(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_size
    );
static int uvm_context_stack_pop_size(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_size *, bool
    );
static int uvm_context_stack_push_ssize(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_ssize
    );
static int uvm_context_stack_pop_ssize(
    uvm_t *, uvm_status_t *,
    uvm_context_t *, uvm_ssize *, bool
    );

uvm_t *new_uvm(
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
    )
{

    UVM_UNUSED(swap_argument);

    if (
        s_alloc == NULL ||
        s_realloc == NULL ||
        s_unalloc == NULL ||
        m_alloc == NULL ||
        m_realloc == NULL ||
        m_unalloc == NULL
        )
    {

        return NULL;

    }

    uvm_t *vm = (uvm_t *)s_alloc(s_context, sizeof(uvm_t));

    if (vm == NULL)
    {

        return NULL;

    }

    vm->memory = m_alloc(m_context, UVM_BYTE_SZ * initial_memory_size);

    if (vm->memory == NULL)
    {

        s_unalloc(s_context, vm);

        return NULL;

    }

    /* temp:  */
        if (grow_argument)
        {



        }

        vm->minimum_memory_size = minimum_memory_size;
        vm->maximum_memory_size = maximum_memory_size;
        vm->memory_size = initial_memory_size;

    vm->m_context = m_context;
    vm->m_alloc = m_alloc;
    vm->m_realloc = m_realloc;
    vm->m_unalloc = m_unalloc;

    vm->s_context = s_context;
    vm->s_alloc = s_alloc;
    vm->s_realloc = s_realloc;
    vm->s_unalloc = s_unalloc;

    vm->create_mutex = create_mutex;
    vm->lock_mutex = lock_mutex;
    vm->try_lock_mutex = try_lock_mutex;
    vm->unlock_mutex = unlock_mutex;
    vm->destroy_mutex = destroy_mutex;

    vm->memory_mutex = uvm_use_create_mutex(vm, UMUTEX_MODE_REAWRI);

    vm->individual_mode_mutex = uvm_use_create_mutex(vm, UMUTEX_MODE_NORMAL);
    vm->individual_mode_owner = NULL;

    vm->status = initial_status;

    UVM_UNUSED(extra_argument);

    return vm;

}

int uvm_set_status(uvm_t *vm, uvm_status_t  status)
{

    if (vm == NULL)
    {

        return EINVAL;

    }

    vm->status = status;

    return 0;

}

int uvm_get_status(uvm_t *vm, uvm_status_t *status)
{

    if (vm == NULL || status == NULL)
    {

        return EINVAL;

    }

    *status = vm->status;

    return 0;

}

int uvm_store(
    uvm_t *vm,
    uvm_status_t *status,
    size_t *address,
    size_t buffer_size,
    unsigned char *buffer,
    bool increment_address
    )
{

    if (
        vm == NULL ||
        address == NULL ||
        buffer_size == 0 ||
        buffer == NULL
        )
    {

        return EINVAL;

    }

    if (status)
    {

        *status = UVM_STATUS_OK;

    }

    uvm_use_lock_mutex(vm, UMUTEX_MODE_REAWRI_SHARED, vm->memory_mutex);

    size_t addr = *address;

    if (*address > vm->memory_size)
    {

        if (status)
        {

            *status = UVM_STATUS_OUT_OF_MEMORY;

        }

        return ERANGE;

    }
    else if (*address == vm->memory_size)
    {

        addr = 0;

    }

    size_t remaining_memory = vm->memory_size - addr;

    size_t bytes_written = 0;

    while (buffer_size > 0)
    {

        if (buffer_size <= remaining_memory)
        {

            memcpy(&vm->memory[addr], &buffer[bytes_written], buffer_size);

            break;

        }

        memcpy(&vm->memory[addr], &buffer[bytes_written], remaining_memory);

        bytes_written += remaining_memory;

        buffer_size -= remaining_memory;

        addr = 0;

        remaining_memory = vm->memory_size;

        if (status)
        {

            *status = UVM_STATUS_NON_SEQUENTIAL_MEMORY;

        }

    }

    if (increment_address)
    {

        *address = addr;

    }

    uvm_use_unlock_mutex(vm, UMUTEX_MODE_REAWRI_SHARED, vm->memory_mutex);

    return 0;

}

int uvm_fetch(
    uvm_t *vm,
    uvm_status_t *status,
    size_t *address,
    size_t buffer_size,
    unsigned char *buffer,
    bool increment_address
    )
{

    if (
        vm == NULL ||
        address == NULL ||
        buffer_size == 0 ||
        buffer == NULL
        )
    {

        return EINVAL;

    }

    if (status)
    {

        *status = UVM_STATUS_OK;

    }

    uvm_use_lock_mutex(vm, UMUTEX_MODE_REAWRI_SHARED, vm->memory_mutex);

    size_t addr = *address;

    if (*address > vm->memory_size)
    {

        if (status)
        {

            *status = UVM_STATUS_OUT_OF_MEMORY;

        }

        return ERANGE;

    }
    else if (*address == vm->memory_size)
    {

        addr = 0;

    }

    size_t remaining_memory = vm->memory_size - addr;

    size_t bytes_read = 0;

    while (buffer_size > 0)
    {

        if (buffer_size <= remaining_memory)
        {

            memcpy(&buffer[bytes_read], &vm->memory[addr], buffer_size);

            addr += buffer_size;

            break;

        }

        memcpy(&buffer[bytes_read], &vm->memory[addr], remaining_memory);

        bytes_read += remaining_memory;

        buffer_size -= remaining_memory;

        addr = 0;

        remaining_memory = vm->memory_size;

        if (status)
        {

            *status = UVM_STATUS_NON_SEQUENTIAL_MEMORY;

        }

    }

    if (increment_address)
    {

        *address = addr;

    }

    uvm_use_unlock_mutex(vm, UMUTEX_MODE_REAWRI_SHARED, vm->memory_mutex);

    return 0;

}

int uvm_context_stack_push(
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx,
    size_t buffer_size,
    unsigned char *buffer
    )
{

    if (
        vm == NULL ||
        vm == NULL||
        buffer_size == 0 ||
        buffer == NULL
        )
    {

        return EINVAL;

    }

    if (uvm_context_try_lock_mutex(ctx) != 0)
    {

        return EBUSY;

    }

    size_t remaining = ctx->stack_size - ctx->stack_pointer;

    if (buffer_size > remaining)
    {

        ctx->status = UVM_CONTEXT_STATUS_STACK_OVERFLOW;

        if (remaining == 0)
        {

            return ERANGE;

        }

        buffer_size = remaining;

    }

    if (buffer)
    {

        size_t a = ctx->stack_base + ctx->stack_pointer;

        uvm_store(vm, status, &a, buffer_size, buffer, false);

    }

    ctx->stack_pointer += buffer_size;

    return 0;

}

int uvm_context_stack_pop (
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx,
    size_t buffer_size,
    unsigned char *buffer,
    bool decrement
    )
{

    if (
        vm == NULL ||
        vm == NULL||
        buffer_size == 0 ||
        buffer == NULL
        )
    {

        return EINVAL;

    }

    if (uvm_context_try_lock_mutex(ctx) != 0)
    {

        return EBUSY;

    }

    size_t available = ctx->stack_pointer;

    if (buffer_size > available)
    {

        ctx->status = UVM_CONTEXT_STATUS_STACK_UNDERFLOW;

        if (available == 0)
        {

            return ERANGE;

        }

        buffer_size = available;

    }

    if (buffer)
    {

        size_t a = ctx->stack_base + ctx->stack_pointer - buffer_size;

        uvm_fetch(vm, status, &a, buffer_size, buffer, false);

    }

    if (decrement)
    {

        ctx->stack_pointer -= buffer_size;

    }

    return 0;

}

#define UVM_PUSH(vm, status, ctx, type)                                 \
do                                                                      \
{                                                                       \
uvm_##type value;                                                       \
if (                                                                    \
    uvm_fetch_##type(vm, status, &ctx->memory_pointer, &value, true)    \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
uvm_context_stack_push_##type(vm, status, ctx, value);                  \
} while (0)                                                             \


#define UVM_DROP(vm, status, ctx, type)                                 \
do                                                                      \
{                                                                       \
uvm_context_stack_pop_##type(vm, status, ctx, NULL, true);              \
} while (0)                                                             \

#define UVM_REV(vm, status, ctx, type)                                  \
do                                                                      \
{                                                                       \
uvm_##type value0;                                                      \
if (                                                                    \
    uvm_context_stack_pop_##type(vm, status, ctx, &value0, true)        \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
uvm_##type value1;                                                      \
if (                                                                    \
    uvm_context_stack_pop_##type(vm, status, ctx, &value1, true)        \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
uvm_context_stack_push_##type(vm, status, ctx, value0);                 \
uvm_context_stack_push_##type(vm, status, ctx, value1);                 \
} while (0)                                                             \

#define UVM_DUP(vm, status, ctx, type)                                  \
do                                                                      \
{                                                                       \
uvm_##type value;                                                       \
if (                                                                    \
    uvm_context_stack_pop_##type(vm, status, ctx, &value, false)        \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
uvm_context_stack_push_##type(vm, status, ctx, value);                  \
} while (0)                                                             \

#define UVM_BINARY_OP(vm, status, ctx, type, op)                        \
do                                                                      \
{                                                                       \
uvm_##type value0;                                                      \
if (                                                                    \
    uvm_context_stack_pop_##type(vm, status, ctx, &value0, true)        \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
uvm_##type value1;                                                      \
if (                                                                    \
    uvm_context_stack_pop_##type(vm, status, ctx, &value1, true)        \
    )                                                                   \
{                                                                       \
    break;                                                              \
}                                                                       \
value0=uvm2pla##type(value0);                                           \
value1=uvm2pla##type(value1);                                           \
uvm_##type value2=value0 op value1;                                     \
value2=pla2uvm##type(value2);                                           \
uvm_context_stack_push_##type(vm, status, ctx, value2);                 \
} while (0)                                                             \

int uvm_execute(
    uvm_t *vm,
    uvm_status_t *status,
    uvm_context_t *ctx
    )
{

    if (
        vm == NULL ||
        ctx == NULL
        )
    {

        return EINVAL;

    }

    if (
        uvm_context_try_lock_mutex(ctx) != 0
        )
    {

        return EBUSY;

    }

    if (
        ctx->halted
        )
    {

        return 0;

    }

    if (
        ctx->individual_mode
        )
    {

        if (
            uvm_use_try_lock_mutex(
                vm,
                UMUTEX_MODE_NORMAL,
                vm->individual_mode_mutex
                ) != 0
            )
        {

            return EACCES;

        }

        vm->individual_mode_owner = ctx;

    }

    uvm_status_t vm_status = vm->status;

    if (status == NULL)
    {

        status = &vm_status;

    }

    uvm_status_t old_vm_status = *status;

    uvm_byte instruction_buffer;

    int fetch_instruction_buffer_return =
    uvm_fetch(
        vm, status, &ctx->memory_pointer,
        UVM_BYTE_SZ, &instruction_buffer, true
        );

    if (fetch_instruction_buffer_return != 0)
    {

        vm->status = vm_status;

        uvm_context_unlock_mutex(ctx);

        return fetch_instruction_buffer_return;

    }

    uvm_instruction_t instruction = (uvm_instruction_t)instruction_buffer;

    switch (instruction)
    {

    case UVM_INSTRUCTION_NOOP:
        /* 0o000240 */; /* <- maybe a nop ? */
        break;

    case UVM_INSTRUCTION_HALT:
        ctx->halted = true;
        break;

    /* BY: */

    case UVM_INSTRUCTION_BYPUSH: UVM_PUSH(vm, status, ctx, byte); break;
    case UVM_INSTRUCTION_BYDROP: UVM_DROP(vm, status, ctx, byte); break;
    case UVM_INSTRUCTION_BYREV : UVM_REV (vm, status, ctx, byte); break;
    case UVM_INSTRUCTION_BYDUP : UVM_DUP (vm, status, ctx, byte); break;

    case UVM_INSTRUCTION_BYADD : UVM_BINARY_OP(vm, status, ctx, byte , +); break;
    case UVM_INSTRUCTION_BYSUB : UVM_BINARY_OP(vm, status, ctx, byte , -); break;
    case UVM_INSTRUCTION_BYMUL : UVM_BINARY_OP(vm, status, ctx, byte , *); break;
    case UVM_INSTRUCTION_BYDIV : UVM_BINARY_OP(vm, status, ctx, byte , /); break;
    case UVM_INSTRUCTION_BYMOD : UVM_BINARY_OP(vm, status, ctx, byte , %); break;
    case UVM_INSTRUCTION_BYADDS: UVM_BINARY_OP(vm, status, ctx, sbyte, +); break;
    case UVM_INSTRUCTION_BYSUBS: UVM_BINARY_OP(vm, status, ctx, sbyte, -); break;
    case UVM_INSTRUCTION_BYMULS: UVM_BINARY_OP(vm, status, ctx, sbyte, *); break;
    case UVM_INSTRUCTION_BYDIVS: UVM_BINARY_OP(vm, status, ctx, sbyte, /); break;
    case UVM_INSTRUCTION_BYMODS: UVM_BINARY_OP(vm, status, ctx, sbyte, %); break;

    case UVM_INSTRUCTION_BYAND : UVM_BINARY_OP(vm, status, ctx, byte , &); break;
    case UVM_INSTRUCTION_BYOR  : UVM_BINARY_OP(vm, status, ctx, byte , |); break;
    case UVM_INSTRUCTION_BYXOR : UVM_BINARY_OP(vm, status, ctx, byte , ^); break;

    /* BY end. */

    /* SH: */

    case UVM_INSTRUCTION_SHPUSH: UVM_PUSH(vm, status, ctx, short); break;
    case UVM_INSTRUCTION_SHDROP: UVM_DROP(vm, status, ctx, short); break;
    case UVM_INSTRUCTION_SHREV : UVM_REV (vm, status, ctx, short); break;
    case UVM_INSTRUCTION_SHDUP : UVM_DUP (vm, status, ctx, short); break;

    case UVM_INSTRUCTION_SHADD : UVM_BINARY_OP(vm, status, ctx, ushort, +); break;
    case UVM_INSTRUCTION_SHSUB : UVM_BINARY_OP(vm, status, ctx, ushort, -); break;
    case UVM_INSTRUCTION_SHMUL : UVM_BINARY_OP(vm, status, ctx, ushort, *); break;
    case UVM_INSTRUCTION_SHDIV : UVM_BINARY_OP(vm, status, ctx, ushort, /); break;
    case UVM_INSTRUCTION_SHMOD : UVM_BINARY_OP(vm, status, ctx, ushort, %); break;
    case UVM_INSTRUCTION_SHADDS: UVM_BINARY_OP(vm, status, ctx, short , +); break;
    case UVM_INSTRUCTION_SHSUBS: UVM_BINARY_OP(vm, status, ctx, short , -); break;
    case UVM_INSTRUCTION_SHMULS: UVM_BINARY_OP(vm, status, ctx, short , *); break;
    case UVM_INSTRUCTION_SHDIVS: UVM_BINARY_OP(vm, status, ctx, short , /); break;
    case UVM_INSTRUCTION_SHMODS: UVM_BINARY_OP(vm, status, ctx, short , %); break;

    case UVM_INSTRUCTION_SHAND : UVM_BINARY_OP(vm, status, ctx, ushort, &); break;
    case UVM_INSTRUCTION_SHOR  : UVM_BINARY_OP(vm, status, ctx, ushort, |); break;
    case UVM_INSTRUCTION_SHXOR : UVM_BINARY_OP(vm, status, ctx, ushort, ^); break;

    /* SH end. */

    /* IN: */

    case UVM_INSTRUCTION_INPUSH: UVM_PUSH(vm, status, ctx, int); break;
    case UVM_INSTRUCTION_INDROP: UVM_DROP(vm, status, ctx, int); break;
    case UVM_INSTRUCTION_INREV : UVM_REV (vm, status, ctx, int); break;
    case UVM_INSTRUCTION_INDUP : UVM_DUP (vm, status, ctx, int); break;

    case UVM_INSTRUCTION_INADD : UVM_BINARY_OP(vm, status, ctx, uint, +); break;
    case UVM_INSTRUCTION_INSUB : UVM_BINARY_OP(vm, status, ctx, uint, -); break;
    case UVM_INSTRUCTION_INMUL : UVM_BINARY_OP(vm, status, ctx, uint, *); break;
    case UVM_INSTRUCTION_INDIV : UVM_BINARY_OP(vm, status, ctx, uint, /); break;
    case UVM_INSTRUCTION_INMOD : UVM_BINARY_OP(vm, status, ctx, uint, %); break;
    case UVM_INSTRUCTION_INADDS: UVM_BINARY_OP(vm, status, ctx, int , +); break;
    case UVM_INSTRUCTION_INSUBS: UVM_BINARY_OP(vm, status, ctx, int , -); break;
    case UVM_INSTRUCTION_INMULS: UVM_BINARY_OP(vm, status, ctx, int , *); break;
    case UVM_INSTRUCTION_INDIVS: UVM_BINARY_OP(vm, status, ctx, int , /); break;
    case UVM_INSTRUCTION_INMODS: UVM_BINARY_OP(vm, status, ctx, int , %); break;

    case UVM_INSTRUCTION_INAND : UVM_BINARY_OP(vm, status, ctx, uint, &); break;
    case UVM_INSTRUCTION_INOR  : UVM_BINARY_OP(vm, status, ctx, uint, |); break;
    case UVM_INSTRUCTION_INXOR : UVM_BINARY_OP(vm, status, ctx, uint, ^); break;

    /* IN end. */

    /* SZ: */

    case UVM_INSTRUCTION_SZPUSH: UVM_PUSH(vm, status, ctx, size); break;
    case UVM_INSTRUCTION_SZDROP: UVM_DROP(vm, status, ctx, size); break;
    case UVM_INSTRUCTION_SZREV : UVM_REV (vm, status, ctx, size); break;
    case UVM_INSTRUCTION_SZDUP : UVM_DUP (vm, status, ctx, size); break;

    case UVM_INSTRUCTION_SZADD : UVM_BINARY_OP(vm, status, ctx, size , +); break;
    case UVM_INSTRUCTION_SZSUB : UVM_BINARY_OP(vm, status, ctx, size , -); break;
    case UVM_INSTRUCTION_SZMUL : UVM_BINARY_OP(vm, status, ctx, size , *); break;
    case UVM_INSTRUCTION_SZDIV : UVM_BINARY_OP(vm, status, ctx, size , /); break;
    case UVM_INSTRUCTION_SZMOD : UVM_BINARY_OP(vm, status, ctx, size , %); break;
    case UVM_INSTRUCTION_SZADDS: UVM_BINARY_OP(vm, status, ctx, ssize, +); break;
    case UVM_INSTRUCTION_SZSUBS: UVM_BINARY_OP(vm, status, ctx, ssize, -); break;
    case UVM_INSTRUCTION_SZMULS: UVM_BINARY_OP(vm, status, ctx, ssize, *); break;
    case UVM_INSTRUCTION_SZDIVS: UVM_BINARY_OP(vm, status, ctx, ssize, /); break;
    case UVM_INSTRUCTION_SZMODS: UVM_BINARY_OP(vm, status, ctx, ssize, %); break;

    case UVM_INSTRUCTION_SZAND : UVM_BINARY_OP(vm, status, ctx, size , &); break;
    case UVM_INSTRUCTION_SZOR  : UVM_BINARY_OP(vm, status, ctx, size , |); break;
    case UVM_INSTRUCTION_SZXOR : UVM_BINARY_OP(vm, status, ctx, size , ^); break;

    /* SZ end. */

    default:
        ctx->status = UVM_CONTEXT_STATUS_ILLEGAL_INSTRUCTION;
        break;

    }

    vm->status = vm_status;

    if (
        !ctx->individual_mode ||
        vm->individual_mode_owner == ctx
        )
    {

        vm->individual_mode_owner = NULL;

        uvm_use_unlock_mutex(
            vm,
            UMUTEX_MODE_NORMAL,
            vm->individual_mode_mutex
            );

    }

    uvm_context_unlock_mutex(ctx);

    return 0;

}

void  free_uvm(uvm_t *vm)
{

    if (vm == NULL)
    {

        return;

    }

    uvm_use_destroy_mutex(vm, UMUTEX_MODE_REAWRI, vm->memory_mutex);

    uvm_use_destroy_mutex(vm, UMUTEX_MODE_NORMAL, vm->individual_mode_mutex);

    vm->m_unalloc(vm->m_context, vm->memory);

    vm->s_unalloc(vm->s_context, vm);

}

static void *uvm_use_create_mutex(uvm_t *vm, umutex_mode_t mode)
{

    if (
        vm == NULL ||
        vm->destroy_mutex == NULL ||
        vm->create_mutex == NULL
        )
    {

        return NULL;

    }

    return vm->create_mutex(mode);

}
static int uvm_use_lock_mutex(uvm_t *vm, umutex_mode_t mode, void *mutex)
{

    if (
        vm == NULL
        )
    {

        return EINVAL;

    }

    if (
        vm->unlock_mutex ||
        vm->lock_mutex
        )
    {

        return 0;

    }

    return vm->lock_mutex(mode, mutex);

}
static int uvm_use_try_lock_mutex(uvm_t *vm, umutex_mode_t mode, void *mutex)
{

    if (
        vm == NULL
        )
    {

        return EINVAL;

    }

    if (
        vm->unlock_mutex ||
        vm->try_lock_mutex
        )
    {

        return 0;

    }

    return vm->try_lock_mutex(mode, mutex);

}
static int uvm_use_unlock_mutex(uvm_t *vm, umutex_mode_t mode, void *mutex)
{

    if (
        vm == NULL
        )
    {

        return EINVAL;

    }

    if (vm->unlock_mutex == NULL)
    {

        return 0;

    }

    return vm->unlock_mutex(mode, mutex);

}
static void uvm_use_destroy_mutex(uvm_t *vm, umutex_mode_t mode, void *mutex)
{

    if (
        vm == NULL ||
        vm->destroy_mutex == NULL
        )
    {

        return;

    }

    vm->destroy_mutex(mode, mutex);

}

static int uvm_store_byte(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_byte  byte, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_BYTE_SZ, (unsigned char *)&byte, increment_address
        );
}
static int uvm_fetch_byte(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_byte *byte, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_BYTE_SZ, (unsigned char *) byte, increment_address
        );
}
static int uvm_store_sbyte(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_sbyte  sbyte, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_SBYTE_SZ, (unsigned char *)&sbyte, increment_address
        );
}
static int uvm_fetch_sbyte(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_sbyte *sbyte, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_SBYTE_SZ, (unsigned char *) sbyte, increment_address
        );
}
static int uvm_store_short(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_short sshort, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_SHORT_SZ, (unsigned char *)&sshort, increment_address
        );
}
static int uvm_fetch_short(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_short *sshort, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_SHORT_SZ, (unsigned char *) sshort, increment_address
        );
}
static int uvm_store_ushort(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_ushort ushort, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_USHORT_SZ, (unsigned char *)&ushort, increment_address
       );
}
static int uvm_fetch_ushort(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_ushort *ushort, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_USHORT_SZ, (unsigned char *) ushort, increment_address
        );
}
static int uvm_store_int(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_int sint, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_INT_SZ, (unsigned char *)&sint, increment_address
        );
}
static int uvm_fetch_int(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_int *sint, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_INT_SZ, (unsigned char *) sint, increment_address
        );
}
static int uvm_store_uint(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_uint uint, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_UINT_SZ, (unsigned char *)&uint, increment_address
        );
}
static int uvm_fetch_uint(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_uint *uint, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_UINT_SZ, (unsigned char *) uint, increment_address
    );
}
static int uvm_store_size(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_size size, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_SIZE_SZ, (unsigned char *)&size, increment_address
        );
}
static int uvm_fetch_size(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_size *size, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_SIZE_SZ, (unsigned char *) size, increment_address
        );
}
static int uvm_store_ssize(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_ssize ssize, bool increment_address
    )
{
    return uvm_store(
        vm, status, address,
        UVM_SSIZE_SZ, (unsigned char *)&ssize, increment_address
        );
}
static int uvm_fetch_ssize(
    uvm_t *vm, uvm_status_t *status, size_t *address,
    uvm_ssize *ssize, bool increment_address
    )
{
    return uvm_fetch(
        vm, status, address,
        UVM_SSIZE_SZ, (unsigned char *) ssize, increment_address
        );
}

static int uvm_context_stack_push_byte(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_byte  byte
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_BYTE_SZ, (unsigned char *)&byte
        );
}
static int uvm_context_stack_pop_byte(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_byte *byte, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_BYTE_SZ, (unsigned char *) byte,
        decrement
    );
}
static int uvm_context_stack_push_sbyte(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_sbyte  sbyte
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_SBYTE_SZ, (unsigned char *)&sbyte
        );
}
static int uvm_context_stack_pop_sbyte(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_sbyte *sbyte, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_SBYTE_SZ, (unsigned char *) sbyte,
        decrement
    );
}
static int uvm_context_stack_push_short(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_short  sshort
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_SHORT_SZ, (unsigned char *)&sshort
        );
}
static int uvm_context_stack_pop_short(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_short *sshort, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_SHORT_SZ, (unsigned char *) sshort,
        decrement
    );
}
static int uvm_context_stack_push_ushort(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_ushort  ushort
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_USHORT_SZ, (unsigned char *)&ushort
        );
}
static int uvm_context_stack_pop_ushort(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_ushort *ushort, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_USHORT_SZ, (unsigned char *) ushort,
        decrement
    );
}
static int uvm_context_stack_push_int(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_int  sint
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_INT_SZ, (unsigned char *)&sint
        );
}
static int uvm_context_stack_pop_int(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_int *sint, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_INT_SZ, (unsigned char *) sint,
        decrement
    );
}
static int uvm_context_stack_push_uint(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_uint  uint
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_UINT_SZ, (unsigned char *)&uint
        );
}
static int uvm_context_stack_pop_uint(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_uint *uint, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_UINT_SZ, (unsigned char *) uint,
        decrement
    );
}
static int uvm_context_stack_push_size(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_size  size
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_SIZE_SZ, (unsigned char *)&size
        );
}
static int uvm_context_stack_pop_size(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_size *size, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_SIZE_SZ, (unsigned char *) size,
        decrement
    );
}
static int uvm_context_stack_push_ssize(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_ssize  ssize
    )
{
    return uvm_context_stack_push(
        vm, status,
        ctx,
        UVM_SSIZE_SZ, (unsigned char *)&ssize
        );
}
static int uvm_context_stack_pop_ssize(
    uvm_t *vm, uvm_status_t *status,
    uvm_context_t *ctx, uvm_ssize *ssize, bool decrement
    )
{
    return uvm_context_stack_pop(
        vm, status,
        ctx,
        UVM_SSIZE_SZ, (unsigned char *) ssize,
        decrement
    );
}
