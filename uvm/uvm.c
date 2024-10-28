#include "uvm.h"

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

    size_t memory_size;
    uvm_byte *memory;
    void *memory_mutex;

    uvm_status_t status;

};

static void *uvm_use_create_mutex(uvm_t *);
static int uvm_use_lock_mutex(uvm_t *, void *);
static int uvm_use_try_lock_mutex(uvm_t *, void *);
static int uvm_use_unlock_mutex(uvm_t *, void *);
static void uvm_use_destroy_mutex(uvm_t *, void *);

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
    size_t initial_memory_size,
    uvm_status_t initial_status
    )
{

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

    vm->memory_mutex = uvm_use_create_mutex(vm);

    vm->status = initial_status;

    return vm;

}

void  free_uvm(uvm_t *vm)
{

    if (vm == NULL)
    {

        return;

    }

    uvm_use_destroy_mutex(vm, vm->memory_mutex);

    vm->s_unalloc(vm->m_context, vm->memory);

    vm->s_unalloc(vm->s_context, vm);

}

static void *uvm_use_create_mutex(uvm_t *vm)
{

    if (
        vm == NULL ||
        vm-> create_mutex == NULL||
        vm->destroy_mutex == NULL
        )
    {

        return NULL;

    }

    return vm->create_mutex();

}
static int uvm_use_lock_mutex(uvm_t *vm, void *mutex)
{

    if (vm == NULL)
    {

        return -1;

    }

    if (
        !vm->unlock_mutex ||
        !vm->  lock_mutex
        )
    {

        return  1;

    }

    return vm->lock_mutex(mutex);

}
static int uvm_use_try_lock_mutex(uvm_t *vm, void *mutex)
{

    if (vm == NULL)
    {

        return -1;

    }

    if (
        !vm->  unlock_mutex ||
        !vm->try_lock_mutex
        )
    {

        return  1;

    }

    return vm->try_lock_mutex(mutex);

}
static int uvm_use_unlock_mutex(uvm_t *vm, void *mutex)
{

    if (vm == NULL)
    {

        return -1;

    }

    if (
        !vm->unlock_mutex
        )
    {

        return  1;

    }

    return vm->unlock_mutex(mutex);

}
static void uvm_use_destroy_mutex(uvm_t *vm, void *mutex)
{

    if (
        vm == NULL ||
        vm->destroy_mutex == NULL
        )
    {

        return;

    }

    vm->destroy_mutex(mutex);

}
