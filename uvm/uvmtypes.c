#include "uvmtypes.h"

uvm_byte pla2uvmbyte(uvm_byte b)
{
#if UVM_BYTE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_BYTE_SZ, &b);
#endif
    return b;
}

uvm_byte uvm2plabyte(uvm_byte b)
{
#if UVM_BYTE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_BYTE_SZ, &b);
#endif
    return b;
}


uvm_sbyte pla2uvmsbyte(uvm_sbyte s)
{
#if UVM_SBYTE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_SBYTE_SZ, &s);
#endif
    return s;
}

uvm_sbyte uvm2plasbyte(uvm_sbyte s)
{
#if UVM_SBYTE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_SBYTE_SZ, &s);
#endif
    return s;
}


uvm_short pla2uvmshort(uvm_short s)
{
#if UVM_SHORT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_SHORT_SZ, &s);
#endif
    return s;
}

uvm_short uvm2plashort(uvm_short s)
{
#if UVM_SHORT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_SHORT_SZ, &s);
#endif
    return s;
}


uvm_ushort pla2uvmushort(uvm_ushort u)
{
#if UVM_USHORT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_USHORT_SZ, &u);
#endif
    return u;
}

uvm_ushort uvm2plaushort(uvm_ushort u)
{
#if UVM_USHORT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_USHORT_SZ, &u);
#endif
    return u;
}


uvm_int pla2uvmint(uvm_int i)
{
#if UVM_INT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_INT_SZ, &i);
#endif
    return i;
}

uvm_int uvm2plaint(uvm_int i)
{
#if UVM_INT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_INT_SZ, &i);
#endif
    return i;
}


uvm_uint pla2uvmuint(uvm_uint u)
{
#if UVM_UINT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_UINT_SZ, &u);
#endif
    return u;
}

uvm_uint uvm2plauint(uvm_uint u)
{
#if UVM_UINT_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_UINT_SZ, &u);
#endif
    return u;
}


uvm_size pla2uvmsize(uvm_size sz)
{
#if UVM_SIZE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_SIZE_SZ, &sz);
#endif
    return sz;
}

uvm_size uvm2plasize(uvm_size sz)
{
#if UVM_SIZE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_SIZE_SZ, &sz);
#endif
    return sz;
}

/* TEMP: */

uvm_size plasz2uvmsz(size_t sz)
{
    return (uvm_size)sz;
}

size_t uvmsz2plasz(uvm_size sz)
{
    return (size_t)sz;
}

/* TEMP end. */


uvm_ssize pla2uvmssize(uvm_ssize ss)
{
#if UVM_SSIZE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(pla, uvm, UVM_SSIZE_SZ, &ss);
#endif
    return ss;
}

uvm_ssize uvm2plassize(uvm_ssize ss)
{
#if UVM_SSIZE_SZ > 1
    UVM_SWAP_FROM2TONUM_CALL(uvm, pla, UVM_SSIZE_SZ, &ss);
#endif
    return ss;
}
